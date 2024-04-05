/*!
 * @file main.c
 * @brief RS485 7 Click Example.
 *
 * # Description
 * This example reads and processes data from RS485 7 clicks.
 * The library also includes a function for enabling/disabling 
 * the receiver or driver and data writing or reading.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver performs wake-up module and enables the selected mode.
 *
 * ## Application Task
 * This example demonstrates the use of the RS485 7 Click board™.
 * The app sends a "MikroE" message, reads the received data and parses it.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void rs4857_clear_app_buf ( void )
 * - static err_t rs4857_process ( void )
 *
 * @note
 * Operation Mode: Full duplex. 
 * Transmitter: Y and Z.
 * Receiver: A and B.
 * Wire connection: Y-A, Z-B.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rs4857.h"

#define DEMO_MESSAGE "\r\nMikroE\r\n"
#define PROCESS_BUFFER_SIZE 200

static rs4857_t rs4857;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief RS485 7 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void rs4857_clear_app_buf ( void );

/**
 * @brief RS485 7 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rs4857_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs4857_cfg_t rs4857_cfg;  /**< Click config object. */

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
    rs4857_cfg_setup( &rs4857_cfg );
    RS4857_MAP_MIKROBUS( rs4857_cfg, MIKROBUS_1 );
    if ( UART_ERROR == rs4857_init( &rs4857, &rs4857_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    app_buf_len = 0;
    
    rs4857_termination_xy_enable( &rs4857 );
    rs4857_termination_ab_enable( &rs4857 );
    
    rs4857_receiver_enable( &rs4857 );
    rs4857_driver_enable( &rs4857 );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{  
    if ( rs4857_generic_write( &rs4857, DEMO_MESSAGE, 10 ) )
    {
        rs4857_process( );
        if ( app_buf_len > 0 )
        {
            log_printf( &logger, "%s", app_buf );
            rs4857_clear_app_buf( );
        }
    }
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

static void rs4857_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t rs4857_process ( void ) 
{
    int32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = rs4857_generic_read( &rs4857, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;
        if ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) 
        {
            rs4857_clear_app_buf( );
            return RS4857_ERROR;
        } 
        else 
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] != 0 ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buf[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return RS4857_OK;
    }
    return RS4857_ERROR;
}

// ------------------------------------------------------------------------ END
