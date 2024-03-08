/*!
 * @file main.c
 * @brief EZO Carrier EC Click Example.
 *
 * # Description
 * This example demonstrates the use of EZO Carrier EC click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the click default factory reset, and single point calibration.
 *
 * ## Application Task
 * Reads and processes all incoming conductivity data from the probe, and displays them on the USB UART in uS.
 *
 * ## Additional Function
 * - static void ezocarrierec_clear_app_buf ( void )
 * - static void ezocarrierec_log_app_buf ( void )
 * - static err_t ezocarrierec_process ( ezocarrierec_t *ctx )
 * - static err_t ezocarrierec_rsp_check ( ezocarrierec_t *ctx, uint8_t *rsp )
 * - static void ezocarrierec_error_check ( err_t error_flag )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ezocarrierec.h"

// Application buffer size
#define APP_BUFFER_SIZE             200
#define PROCESS_BUFFER_SIZE         200

static ezocarrierec_t ezocarrierec;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;

/**
 * @brief EZO Carrier EC clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ezocarrierec_clear_app_buf ( void );

/**
 * @brief EZO Carrier EC log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void ezocarrierec_log_app_buf ( void );

/**
 * @brief EZO Carrier EC data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ezocarrierec_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ezocarrierec_process ( ezocarrierec_t *ctx );

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
static err_t ezocarrierec_rsp_check ( ezocarrierec_t *ctx, uint8_t *rsp );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void ezocarrierec_error_check ( err_t error_flag );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ezocarrierec_cfg_t ezocarrierec_cfg;  /**< Click config object. */

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
    ezocarrierec_cfg_setup( &ezocarrierec_cfg );
    EZOCARRIEREC_MAP_MIKROBUS( ezocarrierec_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ezocarrierec_init( &ezocarrierec, &ezocarrierec_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, "Device status \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_STATUS );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_printf( &logger, "Factory reset \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_FACTORY );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_READY );
    ezocarrierec_error_check( error_flag );

    #define PROBE_TYPE   "1.0"
    log_printf( &logger, "Seting Probe type \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_SET_PROBE_TYPE, PROBE_TYPE );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_printf( &logger, "Device info \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_DEV_INFO );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    #define DRY_CALIBRATION   "dry"
    log_printf( &logger, "Dry calibration \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CAL, DRY_CALIBRATION );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    uint8_t n_cnt = 0;
    uint8_t last_reading[ APP_BUFFER_SIZE ] = { 0 };
    ezocarrierec_clear_app_buf( );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_SINGLE_READ );
    ezocarrierec_process ( &ezocarrierec );
    strcpy( last_reading, app_buf );
    log_printf( &logger, "Single point calibration \r\n" );
    log_printf( &logger, "Waiting for stable readings \r\n" );
    while ( n_cnt <= 5 )
    {
        if ( EZOCARRIEREC_OK == ezocarrierec_process ( &ezocarrierec ) )
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
        Delay_ms( 1000 );
        ezocarrierec_clear_app_buf( );
    }
    #define CALIBRATION_VALUE   "80"
    log_printf( &logger, "Calibration \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CAL, CALIBRATION_VALUE );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    #define DISABLE_CONT_READ   "0"
    log_printf( &logger, "Disable continuous reading mode \r\n" );
    ezocarrierec_send_cmd_with_par( &ezocarrierec, EZOCARRIEREC_CMD_CONT_READ, DISABLE_CONT_READ );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "Reading... \r\n" );
    ezocarrierec_send_cmd( &ezocarrierec, EZOCARRIEREC_CMD_SINGLE_READ );
    error_flag = ezocarrierec_rsp_check( &ezocarrierec, EZOCARRIEREC_RSP_OK );
    ezocarrierec_error_check( error_flag );
    Delay_ms( 5000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void ezocarrierec_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void ezocarrierec_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t ezocarrierec_process ( ezocarrierec_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = ezocarrierec_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return EZOCARRIEREC_OK;
    }
    return EZOCARRIEREC_ERROR;
}

static err_t ezocarrierec_rsp_check ( ezocarrierec_t *ctx, uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 10000;
    err_t error_flag = EZOCARRIEREC_OK;
    ezocarrierec_clear_app_buf( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
    ( 0 == strstr( app_buf, EZOCARRIEREC_RSP_ERROR ) ) )
    {
        error_flag |= ezocarrierec_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            ezocarrierec_clear_app_buf( );
            return EZOCARRIEREC_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 100 );
    error_flag |= ezocarrierec_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        return EZOCARRIEREC_OK;
     }
    else if ( strstr( app_buf, EZOCARRIEREC_RSP_ERROR ) )
    {
        return EZOCARRIEREC_ERROR;
    }
    else
    {
        return EZOCARRIEREC_ERROR;
    }
}

static void ezocarrierec_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case EZOCARRIEREC_OK:
        {
            ezocarrierec_log_app_buf( );
            break;
        }
        case EZOCARRIEREC_ERROR:
        {
            log_error( &logger, " Error!" );
            break;
        }
        case EZOCARRIEREC_ERROR_TIMEOUT:
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
    Delay_ms( 500 );
}

// ------------------------------------------------------------------------ END
