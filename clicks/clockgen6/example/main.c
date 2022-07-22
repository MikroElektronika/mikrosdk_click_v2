/*!
 * @file main.c
 * @brief Clock Gen 6 Click Example.
 *
 * # Description
 * This example demonstrates the use of Clock Gen 6 click board which acts as 
 * an astable oscillator.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which sets the digital
 * potentiometer to max position and enables the clock output.
 *
 * ## Application Task
 * Changes the clock output frequency by changing the digital potentiometer position every second.
 * The potentiometer position value will be displayed on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "clockgen6.h"

static clockgen6_t clockgen6;   /**< Clock Gen 6 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    clockgen6_cfg_t clockgen6_cfg;  /**< Click config object. */

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
    clockgen6_cfg_setup( &clockgen6_cfg );
    CLOCKGEN6_MAP_MIKROBUS( clockgen6_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == clockgen6_init( &clockgen6, &clockgen6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CLOCKGEN6_ERROR == clockgen6_default_cfg ( &clockgen6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( int16_t pos = CLOCKGEN6_DIGIPOT_POSITION_MAX; pos >= CLOCKGEN6_DIGIPOT_POSITION_MIN; )
    {
        if ( CLOCKGEN6_OK == clockgen6_set_digipot ( &clockgen6, pos ) )
        {
            log_printf( &logger, " DIGIPOT position: %u\r\n", pos );
            Delay_ms ( 1000 );
            pos -= 5;
        }
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
