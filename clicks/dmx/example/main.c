/*!
 * \file 
 * \brief DMX Click example
 * 
 * # Description
 * This example demonstrates the use of the DMX click board by showcasing
 * the control for a 6-channel DMX RGB LED reflector connected to it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and performs the click default configuration.
 * 
 * ## Application Task  
 * Performs the LEDs dimming control on a 6-channel DMX RGB LED reflector.
 * 
 * \author MikroE Team
 *
 */
#include "board.h"
#include "log.h"
#include "dmx.h"
#include "string.h"

// Application buffer size
#define APP_BUFFER_SIZE         256
#define PROCESS_BUFFER_SIZE     256

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static dmx_t dmx;
static log_t logger;

/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application
 * buffer and reset its length.
 */
static void dmx_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and
 * appends it to the application buffer.
 * @return @li @c  0 - Some data is read.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 */
static err_t dmx_process ( void );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void dmx_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Unknown error.
 *         @li @c -2 - Timeout error.
 * See #err_t definition for detailed explanation.
 */
static err_t dmx_rsp_check ( uint8_t *rsp );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dmx_cfg_t cfg;

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
    dmx_cfg_setup( &cfg );
    DMX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dmx_init( &dmx, &cfg );

    dmx_set_auto_baud_rate( &dmx, 1 );
    Delay_ms( 100 );

    dmx_reset( &dmx, DMX_MASTER );
    dmx_run( &dmx, DMX_CONFIG_MODE );
    Delay_ms( 100 );
    
    dmx_process( );
    dmx_clear_app_buf( );

    // Clear the internal buffers
    dmx_send_cmd( &dmx, DMX_CMD_PURGEBFR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set start address
    dmx_send_cmd( &dmx, DMX_CMD_SADR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set input data buffer length
    dmx_send_cmd( &dmx, DMX_CMD_BLEN );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set DMX frame length
    dmx_send_cmd( &dmx, DMX_CMD_FLEN_MASTER );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set interrupt pulse duration
    dmx_send_cmd( &dmx, DMX_CMD_ITMR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Set a time delay between two frames
    dmx_send_cmd( &dmx, DMX_CMD_FTMR );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );

    // Display configuration
    dmx_send_cmd( &dmx, DMX_CMD_DISPLCFG );
    dmx_rsp_check( DMX_RSP_OK );
    dmx_log_app_buf( );
    dmx_clear_app_buf( );
    
    dmx_run( &dmx, DMX_RUN_MODE );

    log_info( &logger, " Application Task " );
    Delay_ms( 500 );
}

void application_task ( void )
{
    uint8_t dmx_6_ch_buf[ 6 ] = { 0 };
    int16_t cnt = 0;
    
    dmx_6_ch_buf[ 0 ] = 255; // Dimmer
    dmx_6_ch_buf[ 1 ] = 0;   // Red
    dmx_6_ch_buf[ 2 ] = 0;   // Green
    dmx_6_ch_buf[ 3 ] = 0;   // Blue
    dmx_6_ch_buf[ 4 ] = 0;   // Strobe
    dmx_6_ch_buf[ 5 ] = 0;   // Macro
    
    log_printf( &logger, "\r\nDimming RED LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 1 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 1 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    log_printf( &logger, "Dimming GREEN LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 2 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 2 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    log_printf( &logger, "Dimming BLUE LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 3 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 3 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    
    dmx_6_ch_buf[ 1 ] = 255;
    dmx_6_ch_buf[ 2 ] = 255;
    dmx_6_ch_buf[ 3 ] = 255;
    log_printf( &logger, "Dimming all LEDs\r\n" );
    for ( cnt = 0; cnt <= 255; cnt++ )
    {
        dmx_6_ch_buf[ 0 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
    for ( cnt = 255; cnt >= 0; cnt-- )
    {
        dmx_6_ch_buf[ 0 ] = cnt;
        dmx_generic_write( &dmx, dmx_6_ch_buf, 6 );
        Delay_ms ( 1 );
    }
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

static void dmx_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t dmx_process ( void )
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = dmx_generic_read( &dmx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return DMX_OK;
    }
    return DMX_ERROR;
}

static void dmx_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t dmx_rsp_check ( uint8_t *rsp )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 60000;
    dmx_clear_app_buf( );
    dmx_process( );    
    while ( ( 0 == strstr( app_buf, rsp ) ) &&
            ( 0 == strstr( app_buf, DMX_RSP_ERROR ) ) )
    {
        dmx_process( );
        if ( timeout_cnt++ > timeout )
        {
            dmx_clear_app_buf( );
            return DMX_ERROR_TIMEOUT;
        }
        Delay_ms( 1 );
    }
    Delay_ms( 100 );
    dmx_process( );
    if ( strstr( app_buf, rsp ) )
    {
        return DMX_OK;
    }
    return DMX_ERROR;
}

// ------------------------------------------------------------------------ END
