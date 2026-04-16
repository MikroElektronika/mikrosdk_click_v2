/*!
 * @file main.c
 * @brief RF Switch 2 Click example
 *
 * # Description
 * This example demonstrates the use of the RF Switch 2 Click board to control
 * RF signal routing by switching between available RF paths. The application
 * cycles through all available switching modes, enabling each RF channel one
 * at a time and also demonstrating the all-off state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and RF Switch 2 Click driver, sets up mikroBUS mapping,
 * and prepares digital output pins for controlling the RF switch.
 *
 * ## Application Task
 * Cycles through all switch modes, selecting each RF output sequentially
 * (RF1?RF4) followed by the ALL OFF mode, with delay between changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rfswitch2.h"

#ifndef MIKROBUS_POSITION_RFSWITCH2
    #define MIKROBUS_POSITION_RFSWITCH2 MIKROBUS_1
#endif

static rfswitch2_t rfswitch2;   /**< RF Switch 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfswitch2_cfg_t rfswitch2_cfg;  /**< Click config object. */

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
    rfswitch2_cfg_setup( &rfswitch2_cfg );
    RFSWITCH2_MAP_MIKROBUS( rfswitch2_cfg, MIKROBUS_POSITION_RFSWITCH2 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == rfswitch2_init( &rfswitch2, &rfswitch2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t mode = RFSWITCH2_MODE_ALL_OFF;

    rfswitch2_set_mode( &rfswitch2, mode );
    if ( RFSWITCH2_MODE_ALL_OFF == mode )
    {
        log_printf( &logger, " Mode: ALL OFF\r\n\n" );
    }
    else
    {
        log_printf( &logger, " Mode: RF%u ON\r\n\n", ( uint16_t ) mode );
    }

    if ( ++mode > RFSWITCH2_MODE_RF4_ON )
    {
        mode = RFSWITCH2_MODE_ALL_OFF;
    }

    Delay_ms ( 1000 );
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
