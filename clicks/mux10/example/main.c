/*!
 * @file main.c
 * @brief MUX 10 Click Example.
 *
 * # Description
 * This example demonstrates the use of the MUX 10 Click board by selecting
 * analog channels one by one within the active bank(S1-S4, S5-28), routing each selected
 * channel ( Sx ) to the common drain ( D ) pin of the MUX808-Q1 multiplexer.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and selects the first channel of the active bank.
 *
 * ## Application Task
 * Selects channels 1 to 4 within the active bank(S1-S4, S5-28) in a loop, routing each
 * selected channel to the common D pin, and logs the selected channel via USB UART.
 *
 * @note
 * The A2 address line is not set by the driver but by the SW1 onboard
 * switch and selects the channel bank ( A2 low: S1-S4, A2 high: S5-S8 ).
 * 
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "mux10.h"

#ifndef MIKROBUS_POSITION_MUX10
    #define MIKROBUS_POSITION_MUX10 MIKROBUS_1
#endif

static mux10_t mux10;   /**< MUX 10 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mux10_cfg_t mux10_cfg;  /**< Click config object. */

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
    mux10_cfg_setup( &mux10_cfg );
    MUX10_MAP_MIKROBUS( mux10_cfg, MIKROBUS_POSITION_MUX10 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == mux10_init( &mux10, &mux10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    mux10_active_channel_sel( &mux10, MUX10_SELECT_CH_1 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t cnt = MUX10_SELECT_CH_1; cnt <= MUX10_SELECT_CH_4; cnt++ ) 
    {
        if ( MUX10_OK == mux10_active_channel_sel( &mux10, cnt ) ) 
        {
            log_printf( &logger, " Channel %u selected\r\n", ( uint16_t ) cnt );
            Delay_ms ( 1000 );
        }
    }
    log_printf( &logger, " -----------\r\n" );
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
