/*!
 * \file 
 * \brief HzToV Click example
 * 
 * # Description
 * This example demonstrates the use of Hz to V click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the click board.
 * 
 * ## Application Task  
 * Sets the PWM frequency then reads the voltage from VO pin and logs all data on USB UART.
 * 
 * @note
 * In order to set PWM frequency down to 1 kHz, the user will probably need to 
 * lower the main MCU clock frequency.
 * The output voltage may vary, depending on the offset potentiometer setting on the click.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hztov.h"

// ------------------------------------------------------------------ VARIABLES

static hztov_t hztov;
static log_t logger;
static float voltage;
static uint16_t fin;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hztov_cfg_t cfg;

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

    hztov_cfg_setup( &cfg );
    HZTOV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hztov_init( &hztov, &cfg );
    
    hztov_set_enable ( &hztov, HZTOV_ENABLE );
    
    fin = HZTOV_MIN_FREQ;
    
    Delay_ms ( 100 );
}

void application_task ( void )
{
    if ( fin > HZTOV_MAX_FREQ )
        fin = HZTOV_MIN_FREQ;
    hztov_set_input_frequency( &hztov, fin );
    Delay_ms ( 1000 );
    log_printf( &logger, "Frequency: %u Hz \r\n", fin );
    voltage = 0;
    for ( uint8_t cnt = 0; cnt < 100; cnt++ )
    {
        voltage += hztov_read_voltage( &hztov );
    }
    log_printf( &logger, "Voltage: %.2f V \r\n", voltage / 100.0 );
    log_printf( &logger, "-------------------\r\n" );
    
    fin += 1000;
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
