/*!
 * @file main.c
 * @brief OBDII Click Example.
 *
 * # Description
 * This example demonstrates the use of OBDII click board by reading the engine RPM
 * and vehicle speed and displaying results on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and processes the engine RPM and vehicle speed and displays the results
 * on the USB UART once per second.
 *
 * ## Additional Function
 * - static void obdii_clear_app_buf ( void )
 * - static err_t obdii_process ( obdii_t *ctx )
 * - static void obdii_log_app_buf ( void )
 * - static err_t obdii_rsp_check ( obdii_t *ctx, uint8_t *rsp )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "obdii.h"
#include "conversions.h"

#define PROCESS_BUFFER_SIZE 200

static obdii_t obdii;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief OBDII clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void obdii_clear_app_buf ( void );

/**
 * @brief OBDII data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t obdii_process ( obdii_t *ctx );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void obdii_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] ctx : Click context object.
 * See #obdii_t object definition for detailed explanation.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Unknown command.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 */
static err_t obdii_rsp_check ( obdii_t *ctx, uint8_t *rsp );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    obdii_cfg_t obdii_cfg;  /**< Click config object. */

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
    obdii_cfg_setup( &obdii_cfg );
    OBDII_MAP_MIKROBUS( obdii_cfg, MIKROBUS_1 );
    if ( UART_ERROR == obdii_init( &obdii, &obdii_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    obdii_reset_device ( &obdii );
    
    obdii_process ( &obdii );
    obdii_clear_app_buf ( );
    
    log_printf( &logger, "> Reset device\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_RESET_DEVICE );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Disable echo\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_DISABLE_ECHO );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
    
    log_printf( &logger, " Remove spaces\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_SPACES_OFF );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    obdii_log_app_buf ( );
}

void application_task ( void ) 
{
    uint8_t * __generic_ptr start_ptr = NULL;
    uint8_t data_buf[ 5 ] = { 0 };
    uint16_t rpm = 0;
    uint8_t speed = 0;
    
    log_printf( &logger, " Get current RPM\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_GET_CURRENT_RPM );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    start_ptr = strstr( app_buf, OBDII_RSP_CURRENT_RPM );
    if ( start_ptr )
    {
        memcpy ( data_buf, ( start_ptr + 4 ), 4 );
        data_buf[ 4 ] = 0;
        rpm = hex_to_uint16( data_buf ) / 4;
        log_printf( &logger, "RPM: %u\r\n\n>", rpm );
    }
    else
    {
        obdii_log_app_buf ( );
    }
    
    log_printf( &logger, " Get current speed\r\n" );
    obdii_send_command ( &obdii, OBDII_CMD_GET_CURRENT_SPEED );
    obdii_rsp_check ( &obdii, OBDII_RSP_PROMPT );
    start_ptr = strstr( app_buf, OBDII_RSP_CURRENT_SPEED );
    if ( start_ptr )
    {
        memcpy ( data_buf, ( start_ptr + 4 ), 2 );
        data_buf[ 2 ] = 0;
        speed = hex_to_uint8( data_buf );
        log_printf( &logger, "Speed: %u km/h\r\n\n>", ( uint16_t ) speed );
    }
    else
    {
        obdii_log_app_buf ( );
    }
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

static void obdii_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t obdii_process ( obdii_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = obdii_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = PROCESS_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ PROCESS_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < PROCESS_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return OBDII_OK;
    }
    return OBDII_ERROR;
}

static void obdii_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t obdii_rsp_check ( obdii_t *ctx, uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 60000;
    obdii_clear_app_buf( );
    obdii_process( ctx );
    while ( 0 == strstr( app_buf, rsp ) )
    {
        obdii_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            obdii_clear_app_buf( );
            return OBDII_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    obdii_process( ctx );
    if ( strstr( app_buf, rsp ) )
    {
        return OBDII_OK;
    }
    return OBDII_ERROR;
}

// ------------------------------------------------------------------------ END
