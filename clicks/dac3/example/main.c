/*!
 * \file 
 * \brief DAC3 Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the DAC 3 Click module. The Click
 * performs digital to analog conversion and the output voltage can be read on the output termi-
 * nal using a multimeter. An oscilloscope is required to read the analog signal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function configures and initializes the Click and logger modules. The write_all_mem(...)
 * function configures DAC settings.
 * 
 * ## Application Task  
 * This function resets and wakes up the Click module and then changes the output voltage on the
 * output terminal a few times in a loop with a 5 second delay. It does so every 1 second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac3.h"

// ------------------------------------------------------------------ VARIABLES

static dac3_t dac3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    dac3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dac3_cfg_setup( &cfg );
    DAC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac3_init( &dac3, &cfg );

    dac3.dac_cfg.vrl = 0;
    dac3.dac_cfg.power = 0;
    dac3.dac_cfg.gain = 0;

    dac3_write_all_mem( &dac3, 0 );
    Delay_100ms( );
}

void application_task ( )
{
    uint8_t cnt;
    uint32_t output_value;

    output_value = 500;

    dac3_send_command( &dac3, DAC3_RESET );
    Delay_100ms( );

    dac3_send_command( &dac3, DAC3_WAKE_UP );
    Delay_100ms( );

    for ( cnt = 1; cnt < 9; cnt ++ )
    {
        dac3_set_out_voltage( &dac3, output_value * cnt );

        log_printf( &logger, " .current DAC value: %d\r\n", output_value * cnt );
        log_printf( &logger, " .output voltage: %d mV\r\n", ( ( output_value * cnt ) * 79 ) / 64 );
        log_printf( &logger, "-------------------------------\r\n" );

        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "###############################\r\n" );
    Delay_1sec( );
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
