/*!
 * @file main.c
 * @brief LED Flash 4 Click example
 *
 * # Description
 * This example demonstrates the use of LED Flash 4 click board by toggling
 * the LEDs output.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets
 * the click in flash mode with the LED current of 50mA for both LEDs. The strobe
 * pin is set to active high level type.

 * ## Application Task
 * Toggles the LEDs output every 2 seconds using the strobe pin, and displays the LEDs
 * state on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ledflash4.h"

static ledflash4_t ledflash4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledflash4_cfg_t ledflash4_cfg;  /**< Click config object. */

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
    ledflash4_cfg_setup( &ledflash4_cfg );
    LEDFLASH4_MAP_MIKROBUS( ledflash4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledflash4_init( &ledflash4, &ledflash4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDFLASH4_ERROR == ledflash4_default_cfg ( &ledflash4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " LEDs ON\r\n\n" );
    ledflash4_set_stb_pin ( &ledflash4, LEDFLASH4_STROBE_PIN_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " LEDs OFF\r\n\n" );
    ledflash4_set_stb_pin ( &ledflash4, LEDFLASH4_STROBE_PIN_LOW );
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

// ------------------------------------------------------------------------ END
