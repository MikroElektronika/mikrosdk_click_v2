/*!
 * @file main.c
 * @brief Headphone Amp 2 Click Example.
 *
 * # Description
 * This library contains API for the Headphone AMP 2 click driver.
 * This demo application shows use of a Headphone AMP 2 click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization the app set default settings, 
 * performs power-up sequence, sets a the sound volume of 6 dB.
 *
 * ## Application Task
 * This example demonstrates the use of the Headphone AMP 2 click board™.
 * The app performs circles the volume switch between two gain settings,
 * 6 dB or 12 dB via a logic signal on the gain select pin.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "headphoneamp2.h"

static headphoneamp2_t headphoneamp2;   /**< Headphone Amp 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp2_cfg_t headphoneamp2_cfg;  /**< Click config object. */

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
    headphoneamp2_cfg_setup( &headphoneamp2_cfg );
    HEADPHONEAMP2_MAP_MIKROBUS( headphoneamp2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == headphoneamp2_init( &headphoneamp2, &headphoneamp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    headphoneamp2_default_cfg ( &headphoneamp2 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    headphoneamp2_change_gain( &headphoneamp2 );
    log_printf( &logger, " The gain level has been changed.\r\n" );
    Delay_ms( 5000 );
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
