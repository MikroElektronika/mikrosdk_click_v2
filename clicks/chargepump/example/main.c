/*!
 * @file main.c
 * @brief Charge Pump Click Example.
 *
 * # Description
 * This example demonstrates the use of the Charge Pump Click board by cycling the
 * LT7826 switched capacitor converter between switching and standby mode,
 * while monitoring the fault indication pin.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device.
 *
 * ## Application Task
 * Enables switching and waits for the fault pin to be released, keeps the converter
 * running for 5 seconds, then returns it to standby mode for one second. The
 * state of the converter is displayed on the USB UART.
 *
 * @note
 * The load current must stay below 30mA while the device is in the pre-balance phase,
 * otherwise the device never enters full-power switching.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "chargepump.h"

#ifndef MIKROBUS_POSITION_CHARGEPUMP
    #define MIKROBUS_POSITION_CHARGEPUMP MIKROBUS_1
#endif

static chargepump_t chargepump;   /**< Charge Pump Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    chargepump_cfg_t chargepump_cfg;  /**< Click config object. */

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
    chargepump_cfg_setup( &chargepump_cfg );
    CHARGEPUMP_MAP_MIKROBUS( chargepump_cfg, MIKROBUS_POSITION_CHARGEPUMP );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == chargepump_init( &chargepump, &chargepump_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    chargepump_enable_device( &chargepump );
    Delay_10ms( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    /* Enable switching capacitors and wait for the output to become ready. */
    chargepump_enable_switching( &chargepump );
    if ( CHARGEPUMP_OK == chargepump_wait_output_ready( &chargepump ) )
    {
        log_printf( &logger, " Switching - output ready\r\n" );
    }
    else
    {
        log_printf( &logger, " Switching - output not ready\r\n" );
    }
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );
    Delay_ms( 1000 );

    /* Enter standby mode */
    chargepump_disable_switching( &chargepump );
    log_printf( &logger, " Standby\r\n\n" );
    Delay_ms( 1000 );
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
