/*!
 * \file 
 * \brief Buck5 Click example
 * 
 * # Description
 * Buck 5 Click is a high-efficiency buck DC/DC converter, which can provide digitally 
 * adjusted step-down voltage on its output while delivering a considerable amount of current. 
 * Buck 5 click accepts a wide voltage range on its input - from 5V to 30V. The output voltage 
 * may be adjusted via the SPI interface, in the range from 0.9V to approximately 5.5V.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, and enables the click board.
 * 
 * ## Application Task  
 * Increases the output voltage by 500mV every 3 seconds from MIN to MAX VOUT.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck5.h"

// ------------------------------------------------------------------ VARIABLES

static buck5_t buck5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck5_cfg_t cfg;

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

    buck5_cfg_setup( &cfg );
    BUCK5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck5_init( &buck5, &cfg );

    buck5_power_on( &buck5 );
    buck5_reset( &buck5 );
}

void application_task ( void )
{
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_MIN );
    log_printf( &logger, "VOUT: MIN\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1000mV );
    log_printf( &logger, "VOUT: ~1V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_1500mV );
    log_printf( &logger, "VOUT: ~1.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_2000mV );
    log_printf( &logger, "VOUT: ~2V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_2500mV );
    log_printf( &logger, "VOUT: ~2.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3000mV );
    log_printf( &logger, "VOUT: ~3V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_3500mV );
    log_printf( &logger, "VOUT: ~3.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4000mV );
    log_printf( &logger, "VOUT: ~4V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_4500mV );
    log_printf( &logger, "VOUT: ~4.5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_5000mV );
    log_printf( &logger, "VOUT: ~5V\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    buck5_set_output_voltage( &buck5, BUCK5_VOLTAGE_MAX );
    log_printf( &logger, "VOUT: MAX\r\n" );
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
