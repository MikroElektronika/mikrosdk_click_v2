/*!
 * @file main.c
 * @brief EZO Carrier DO Click Example.
 *
 * # Description
 * This example demonstrates the use of EZO Carrier DO Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default factory reset, and high point calibration.
 *
 * ## Application Task
 * Reads and processes all incoming dissolved oxygen data from the probe, and displays them on the USB UART in mg/L.
 *
 * ## Additional Function
 * - static void ezocarrierdo_clear_app_buf ( void )
 * - static void ezocarrierdo_log_app_buf ( void )
 * - static err_t ezocarrierdo_process ( ezocarrierdo_t *ctx )
 * - static err_t ezocarrierdo_rsp_check ( ezocarrierdo_t *ctx, uint8_t *rsp )
 * - static void ezocarrierdo_error_check ( err_t error_flag )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ezocarrierdo.h"

// Application buffer size
#define APP_BUFFER_SIZE             200
#define PROCESS_BUFFER_SIZE         200

static ezocarrierdo_t ezocarrierdo;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;

/**
 * @brief EZO Carrier DO clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ezocarrierdo_clear_app_buf ( void );

/**
 * @brief EZO Carrier DO log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ezocarrierdo_log_app_buf ( void );

/**
 * @brief EZO Carrier DO data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ezocarrierdo_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ezocarrierdo_process ( ezocarrierdo_t *ctx );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Error response.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 */
static err_t ezocarrierdo_rsp_check ( ezocarrierdo_t *ctx, uint8_t *rsp );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void ezocarrierdo_error_check ( err_t error_flag );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierdo_cfg_t ezocarrierdo_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ezocarrierdo_cfg_setup( &ezocarrierdo_cfg );
    EZOCARRIERDO_MAP_MIKROBUS( ezocarrierdo_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierdo_init( &ezocarrierdo, &ezocarrierdo_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Device status \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_STATUS );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_FACTORY );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_READY );
    ezocarrierdo_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_DEV_INFO );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierdo_clear_app_buf( );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_SINGLE_READ );
    ezocarrierdo_process ( &ezocarrierdo );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "High point calibration \r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIERDO_OK == ezocarrierdo_process ( &ezocarrierdo ) )
        {  
            if ( 0 == strstr( app_buf, last_reading ) )
            {
                n_cnt++;
            }
            else
            {
                strcpy( last_reading, app_buf );
                n_cnt = 0;
            }
        }
        log_printf( &logger, "- " );
        Delay_ms ( 1000 );
        ezocarrierdo_clear_app_buf( );
    }
    
    log_printf( &logger, "\r\n Calibration \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_CAL );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    #define DISABLE_CONT_READ   "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierdo_send_cmd_with_par( &ezocarrierdo, EZOCARRIERDO_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierdo_send_cmd( &ezocarrierdo, EZOCARRIERDO_CMD_SINGLE_READ );
    error_flag = ezocarrierdo_rsp_check( &ezocarrierdo, EZOCARRIERDO_RSP_OK );
    ezocarrierdo_error_check( error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void ezocarrierdo_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ezocarrierdo_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ezocarrierdo_process ( ezocarrierdo_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ezocarrierdo_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            memmove ( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset ( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return EZOCARRIERDO_OK;
    }
    return EZOCARRIERDO_ERROR;
}

static err_t ezocarrierdo_rsp_check ( ezocarrierdo_t *ctx, uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 10000;
    err_t error_flag = EZOCARRIERDO_OK;
    ezocarrierdo_clear_app_buf( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
    ( 0 == strstr( app_buf, EZOCARRIERDO_RSP_ERROR ) ) )
    {
        error_flag |= ezocarrierdo_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            ezocarrierdo_clear_app_buf( );
            return EZOCARRIERDO_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    error_flag |= ezocarrierdo_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        return EZOCARRIERDO_OK;
     }
    else if ( strstr( app_buf, EZOCARRIERDO_RSP_ERROR ) )
    {
        return EZOCARRIERDO_ERROR;
    }
    else
    {
        return EZOCARRIERDO_ERROR;
    }
}

static void ezocarrierdo_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case EZOCARRIERDO_OK:
        {
            ezocarrierdo_log_app_buf( );
            break;
        }
        case EZOCARRIERDO_ERROR:
        {
            log_error( &logger, " Error!" );
            break;
        }
        case EZOCARRIERDO_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 500 );
}

// ------------------------------------------------------------------------ END
