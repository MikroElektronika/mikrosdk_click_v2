/*!
 * @file main.c
 * @brief Opto 8 Click example
 *
 * # Description
 * This example demonstrates the use of the Opto 8 Click board by monitoring
 * the state of opto-isolated inputs and controlling the corresponding outputs.
 * When an input state changes, the application updates the related output and
 * logs the new state to the serial terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Opto 8 Click driver and configures the digital
 * input and output pins through the mikroBUS socket.
 *
 * ## Application Task
 * Continuously reads the states of the opto-isolated inputs and updates the
 * corresponding outputs when a change is detected, logging the output state
 * to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */
#include "board.h"
#include "log.h"
#include "opto8.h"

#ifndef MIKROBUS_POSITION_OPTO8
    #define MIKROBUS_POSITION_OPTO8 MIKROBUS_1
#endif

static opto8_t opto8;   /**< Opto 8 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    opto8_cfg_t opto8_cfg;  /**< Click config object. */

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
    opto8_cfg_setup( &opto8_cfg );
    OPTO8_MAP_MIKROBUS( opto8_cfg, MIKROBUS_POSITION_OPTO8 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == opto8_init( &opto8, &opto8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t out1_state = 255;
    static uint8_t out2_state = 255;
    uint8_t in1_state = 0;
    uint8_t in2_state = 0;

    in1_state = opto8_get_in1( &opto8 );
    in2_state = opto8_get_in2( &opto8 );
    
    if ( ( in1_state != out1_state ) || ( in2_state != out2_state ) )
    {
        out1_state = in1_state;
        if ( out1_state )
        {
            opto8_clear_out1( &opto8 );
            log_printf( &logger, " OUT1 state: Disabled\r\n" );
        }
        else
        {
            opto8_set_out1( &opto8 );
            log_printf( &logger, " OUT1 state: Enabled\r\n" );
        }

        out2_state = in2_state;
        if ( out2_state )
        {
            opto8_clear_out2( &opto8 );
            log_printf( &logger, " OUT2 state: Disabled\r\n\n" );
        }
        else
        {
            opto8_set_out2( &opto8 );
            log_printf( &logger, " OUT2 state: Enabled\r\n\n" );
        }
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

// ------------------------------------------------------------------------ END
