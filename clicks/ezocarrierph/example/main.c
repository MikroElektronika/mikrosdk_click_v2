/*!
 * @file main.c
 * @brief EZO Carrier pH Click Example.
 *
 * # Description
 * This example demonstrates the use of EZO Carrier pH Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default factory reset, and mid point calibration.
 *
 * ## Application Task
 * Reads and processes all incoming pH value data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void ezocarrierph_clear_app_buf ( void )
 * - static void ezocarrierph_log_app_buf ( void )
 * - static err_t ezocarrierph_process ( ezocarrierph_t *ctx )
 * - static err_t ezocarrierdo_rsp_check ( ezocarrierdo_t *ctx, uint8_t *rsp )
 * - static void ezocarrierdo_error_check ( err_t error_flag )  
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ezocarrierph.h"

// Application buffer size
#define APP_BUFFER_SIZE             200
#define PROCESS_BUFFER_SIZE         200

static ezocarrierph_t ezocarrierph;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;

/**
 * @brief EZO Carrier pH clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ezocarrierph_clear_app_buf ( void );

/**
 * @brief EZO Carrier pH log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ezocarrierph_log_app_buf ( void );

/**
 * @brief EZO Carrier pH data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ezocarrierph_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ezocarrierph_process ( ezocarrierph_t *ctx );

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
static err_t ezocarrierph_rsp_check ( ezocarrierph_t *ctx, uint8_t *rsp );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void ezocarrierph_error_check ( err_t error_flag );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierph_cfg_t ezocarrierph_cfg;  /**< Click config object. */

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
    ezocarrierph_cfg_setup( &ezocarrierph_cfg );
    EZOCARRIERPH_MAP_MIKROBUS( ezocarrierph_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierph_init( &ezocarrierph, &ezocarrierph_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Device status \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_STATUS );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_FACTORY );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_READY );
    ezocarrierph_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_DEV_INFO );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierph_clear_app_buf( );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_SINGLE_READ );
    ezocarrierph_process ( &ezocarrierph );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "Mid point calibration \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "Place probe into pH neutral solution \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Starting calibration \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIERPH_OK == ezocarrierph_process ( &ezocarrierph ) )
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
        ezocarrierph_clear_app_buf( );
    }
    
    #define MID_POINT_CALIB         "mid,7.00"
    log_printf( &logger, "\r\n Calibration \r\n" );
    ezocarrierph_send_cmd_with_par( &ezocarrierph, EZOCARRIERPH_CMD_CAL, MID_POINT_CALIB );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    #define DISABLE_CONT_READ       "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierph_send_cmd_with_par( &ezocarrierph, EZOCARRIERPH_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierph_send_cmd( &ezocarrierph, EZOCARRIERPH_CMD_SINGLE_READ );
    error_flag = ezocarrierph_rsp_check( &ezocarrierph, EZOCARRIERPH_RSP_OK );
    ezocarrierph_error_check( error_flag );
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

static void ezocarrierph_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ezocarrierph_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ezocarrierph_process ( ezocarrierph_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ezocarrierph_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return EZOCARRIERPH_OK;
    }
    return EZOCARRIERPH_ERROR;
}

static err_t ezocarrierph_rsp_check ( ezocarrierph_t *ctx, uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 10000;
    err_t error_flag = EZOCARRIERPH_OK;
    ezocarrierph_clear_app_buf( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
    ( 0 == strstr( app_buf, EZOCARRIERPH_RSP_ERROR ) ) )
    {
        error_flag |= ezocarrierph_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            ezocarrierph_clear_app_buf( );
            return EZOCARRIERPH_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    error_flag |= ezocarrierph_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        return EZOCARRIERPH_OK;
     }
    else if ( strstr( app_buf, EZOCARRIERPH_RSP_ERROR ) )
    {
        return EZOCARRIERPH_ERROR;
    }
    else
    {
        return EZOCARRIERPH_ERROR;
    }
}

static void ezocarrierph_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case EZOCARRIERPH_OK:
        {
            ezocarrierph_log_app_buf( );
            break;
        }
        case EZOCARRIERPH_ERROR:
        {
            log_error( &logger, " Error!" );
            break;
        }
        case EZOCARRIERPH_ERROR_TIMEOUT:
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
