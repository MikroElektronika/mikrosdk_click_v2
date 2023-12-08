/*!
 * @file main.c
 * @brief LED Driver 15 Click example
 *
 * # Description
 * This example demonstrates the use of LED Driver 15 click board by changing
 * the LEDs dimming level.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the LEDs dimming level in I2C mode every 500ms. The dimming level will be
 * displayed on the USB UART.
 *
 * @note
 * It is recommended to connect 8 LEDs in series (40mA) to the output connector.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver15.h"

static leddriver15_t leddriver15;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver15_cfg_t leddriver15_cfg;  /**< Click config object. */

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
    leddriver15_cfg_setup( &leddriver15_cfg );
    LEDDRIVER15_MAP_MIKROBUS( leddriver15_cfg, MIKROBUS_1 );
    if ( LEDDRIVER15_OK != leddriver15_init( &leddriver15, &leddriver15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER15_OK != leddriver15_default_cfg ( &leddriver15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t dimming = LEDDRIVER15_I2C_DIMMING_MIN;
    if ( LEDDRIVER15_OK == leddriver15_set_i2c_dimming ( &leddriver15, dimming ) )
    {
        log_printf( &logger, " Dimming level: %u\r\n\n", ( uint16_t ) dimming );
    }
    if ( ++dimming > LEDDRIVER15_I2C_DIMMING_MAX )
    {
        dimming = LEDDRIVER15_I2C_DIMMING_MIN;
    }
    Delay_ms( 500 );
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

// ------------------------------------------------------------------------ END
