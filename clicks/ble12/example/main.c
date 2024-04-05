/*!
 * @file main.c
 * @brief BLE 12 Click Example.
 *
 * # Description
 * This example reads and processes data from BLE 12 Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART driver and logs UART. 
 * After driver initialization, the app performs a wake-up module, 
 * enters command mode, sets the device name and advertising time interval, 
 * and disconnects all connections. 
 * After that, the blinking of the yellow LED Indicates
 * that the BLE 12 Click board™ is ready for connection. 
 * After establishing the connection, the yellow LED is turned on.
 *
 * ## Application Task
 * This example demonstrates the use of the BLE 12 Click board™. 
 * Reads the received data and parses it. 
 * Results are being sent to the Usart Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static void ble12_clear_app_buf ( void )
 * - static err_t ble12_process ( void )
 *
 * @note
 * We have used the Serial Bluetooth Terminal Android application for the test
 * and you can find it at the link:
 * https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal
 * 
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ble12.h"

#define PROCESS_BUFFER_SIZE 200
#define RSP_TIMEOUT         100

static ble12_t ble12;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief BLE 12 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void ble12_clear_app_buf ( void );

/**
 * @brief BLE 12 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble12_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ble12_cfg_t ble12_cfg;  /**< Click config object. */

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
    ble12_cfg_setup( &ble12_cfg );
    BLE12_MAP_MIKROBUS( ble12_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ble12_init( &ble12, &ble12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BLE12_ERROR == ble12_default_cfg ( &ble12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t  BLE 12 Click\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t  Command mode\r\n" );
    ble12_set_op_mode( &ble12, BLE12_OP_MODE_CMD );
    Delay_ms ( 100 );
    
    ble12_event_startup( &ble12 );
    Delay_ms ( 100 );
     
    ble12_set_led_state( &ble12, BLE12_LED_RED, BLE12_LED_OFF );
    ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_OFF );
    Delay_ms ( 100 );
    
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "> Set device name:" );
    log_printf( &logger, " BLE 12 Click\r\n" );
    ble12_set_device_name( &ble12, "BLE 12 Click" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "> Set Adv. Interval: 99 ms\r\n" );
    ble12_set_adv_interval( &ble12, "0099" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "> Disconnect all connections\r\n" );
    ble12_disconnect( &ble12 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "  Please connect your device\r\n" );
    
    do
    {
        ble12_process(); 
        ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_ON );
        Delay_ms ( 50 );
        ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_OFF );
        Delay_ms ( 50 );
    }
    while ( !strstr( app_buf, BLE12_EVT_CONNECTED ) );
    Delay_ms ( 100 );

    ble12_set_led_state( &ble12, BLE12_LED_RED, BLE12_LED_OFF );
    ble12_set_led_state( &ble12, BLE12_LED_YELLOW, BLE12_LED_ON );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "\tDevice connected\r\n" );
    Delay_ms ( 100 );
    
    ble12_set_op_mode( &ble12, BLE12_OP_MODE_DATA );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "\t    Data mode\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - - - -\r\n" );
    Delay_ms ( 100 );
    
    ble12_process();
    ble12_clear_app_buf( );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{      
    ble12_process();
    
    if ( app_buf_len > 0 ) 
    { 
        log_printf( &logger, "%s", app_buf );
        ble12_clear_app_buf(  );    
    }
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

static void ble12_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t ble12_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = ble12_generic_read( &ble12, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
            ble12_clear_app_buf(  );
            return BLE12_ERROR;
        } 
        else
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( ( rx_buff[ rx_cnt ] != 0 ) && ( rx_buff[ rx_cnt ] != 0x2B ) ) 
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];   
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        
        
        
        return BLE12_OK;
    }
    return BLE12_ERROR;
}



// ------------------------------------------------------------------------ END
