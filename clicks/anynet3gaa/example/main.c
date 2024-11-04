/*!
 * @file main.c
 * @brief AnyNet 3G-AA Click Example.
 *
 * # Description
 * This example demonstrates the use of AnyNet 3G-AA Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sends a few AT commands to test the communication
 * and configure the Click board.
 *
 * ## Application Task
 * Reads all the received data and logs them to the USB UART.
 *
 * ## Additional Function
 * - static void anynet3gaa_clear_app_buf ( void )
 * - static err_t anynet3gaa_process ( void )
 * - static void anynet3gaa_error_check( err_t error_flag )
 * - static void anynet3gaa_log_app_buf ( void )
 * - static err_t anynet3gaa_rsp_check ( uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "anynet3gaa.h"

// Application buffer size
#define APP_BUFFER_SIZE                     256
#define PROCESS_BUFFER_SIZE                 256

static anynet3gaa_t anynet3gaa;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag = ANYNET3GAA_OK;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length.
 */
static void anynet3gaa_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t anynet3gaa_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void anynet3gaa_error_check ( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void anynet3gaa_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 *         @li @c -4 - Unknown error.
 * See #err_t definition for detailed explanation.
 */
static err_t anynet3gaa_rsp_check ( uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    anynet3gaa_cfg_t anynet3gaa_cfg;  /**< Click config object. */

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
    anynet3gaa_cfg_setup( &anynet3gaa_cfg );
    ANYNET3GAA_MAP_MIKROBUS( anynet3gaa_cfg, MIKROBUS_1 );
    if ( UART_ERROR == anynet3gaa_init( &anynet3gaa, &anynet3gaa_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    anynet3gaa_process( );
    anynet3gaa_clear_app_buf( );

    // Check communication
    anynet3gaa_send_cmd( &anynet3gaa, ANYNET3GAA_CMD_AT );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    
    // Query VERSION info for the AnyNet AWS IoT code
    anynet3gaa_send_cmd( &anynet3gaa, ANYNET3GAA_CMD_AWSVER );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    
    // Query IMEI of the modem on the board
    anynet3gaa_send_cmd( &anynet3gaa, ANYNET3GAA_CMD_GSN );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    
    // Query ICCID of the SIM
    anynet3gaa_send_cmd( &anynet3gaa, ANYNET3GAA_CMD_QCCID );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    
    // Check AWS State
    anynet3gaa_send_cmd_check( &anynet3gaa, ANYNET3GAA_CMD_AWSSTATE );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    
    // Open AWS topic
    #define AWS_TOPIC_OPEN "0,\"MY_TOPIC_OPEN\""
    anynet3gaa_send_cmd_with_par( &anynet3gaa, ANYNET3GAA_CMD_AWSPUBOPEN, AWS_TOPIC_OPEN );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    
    // Subscribe to AWS topic
    #define AWS_TOPIC_SUBSCRIBE "0,\"MY_TOPIC_SUBSCRIBE\""
    anynet3gaa_send_cmd_with_par( &anynet3gaa, ANYNET3GAA_CMD_AWSSUBOPEN, AWS_TOPIC_SUBSCRIBE );
    error_flag = anynet3gaa_rsp_check( ANYNET3GAA_RSP_OK );
    anynet3gaa_error_check( error_flag );
    anynet3gaa_clear_app_buf( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    anynet3gaa_process( );
    anynet3gaa_log_app_buf( );
    anynet3gaa_clear_app_buf( );
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

static void anynet3gaa_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t anynet3gaa_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = anynet3gaa_generic_read( &anynet3gaa, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = APP_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - APP_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ APP_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < APP_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return ANYNET3GAA_OK;
    }
    return ANYNET3GAA_ERROR;
}

static err_t anynet3gaa_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    anynet3gaa_clear_app_buf( );
    anynet3gaa_process( );
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, ANYNET3GAA_RSP_ERROR ) ) &&
            ( 0 == strstr( app_buf, ANYNET3GAA_RSP_SEND_FAIL ) ) )
    {
        anynet3gaa_process( );
        if ( timeout_cnt++ > timeout )
        {
            anynet3gaa_clear_app_buf( );
            return ANYNET3GAA_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    anynet3gaa_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return ANYNET3GAA_OK;
    }
    else if ( strstr( app_buf, ANYNET3GAA_RSP_ERROR ) )
    {
        return ANYNET3GAA_ERROR_CMD;
    }
    else if ( strstr( app_buf, ANYNET3GAA_RSP_SEND_FAIL ) )
    {
        return ANYNET3GAA_ERROR_SEND;
    }
    else
    {
        return ANYNET3GAA_ERROR_UNKNOWN;
    }
}

static void anynet3gaa_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case ANYNET3GAA_OK:
        {
            anynet3gaa_log_app_buf( );
            break;
        }
        case ANYNET3GAA_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case ANYNET3GAA_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case ANYNET3GAA_ERROR_SEND:
        {
            log_error( &logger, " SEND FAIL!" );
            break;
        }
        case ANYNET3GAA_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    Delay_ms ( 500 );
}

static void anynet3gaa_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

// ------------------------------------------------------------------------ END
