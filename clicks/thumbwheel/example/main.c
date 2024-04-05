/*!
 * @file main.c
 * @brief Thumbwheel Click Example.
 *
 * # Description
 * This example demonstrates the use of Thumbwheel click board 
 * by displaying the exact position of the rotary sprocket. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and checks the communication.
 *
 * ## Application Task
 * Demonstrates the usage of thumbwheel_get_position function
 * which gives the exact position of the rotary sprocket. 
 * The position will be displayed on the UART Terminal. 
 *
 * @author Aleksandra Cvjeticanin
 *
 */

#include "board.h"
#include "log.h"
#include "thumbwheel.h"

static thumbwheel_t thumbwheel;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thumbwheel_cfg_t thumbwheel_cfg;  /**< Click config object. */

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
    thumbwheel_cfg_setup( &thumbwheel_cfg );
    THUMBWHEEL_MAP_MIKROBUS( thumbwheel_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == thumbwheel_init( &thumbwheel, &thumbwheel_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( THUMBWHEEL_ERROR == thumbwheel_check_communication ( &thumbwheel ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t old_position = 0xFF;
    uint8_t position; 
    
    if ( ( THUMBWHEEL_OK == thumbwheel_get_position ( &thumbwheel, &position ) ) && 
         ( old_position != position ) )
    {
        log_printf( &logger, " Position: %u \r\n\n", ( uint16_t ) position );
        old_position = position; 
    }
    Delay_ms ( 100 );
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

// ------------------------------------------------------------------------ END
