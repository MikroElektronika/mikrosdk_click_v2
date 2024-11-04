/*!
 * \file 
 * \brief Dac2 Click example
 * 
 * # Description
 * DAC 2 Click represents a 16-bit digital-to-analog converter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This example of the DAC 2 communicates with MCU through the SPI communication, 
 * send digital input ( form 0 to 100 with step 1 ) and transforms it 
 * to the output voltage, ranging from 0 to Vref [mV].
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac2.h"

// ------------------------------------------------------------------ VARIABLES

static dac2_t dac2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac2_cfg_t cfg;

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
    Delay_ms ( 1000 );

    //  Click initialization.

    dac2_cfg_setup( &cfg );
    DAC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac2_init( &dac2, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----- DAC 2  Click ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    dac2_default_cfg( &dac2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    uint16_t voltage_out;
    uint8_t value_pct;

    for ( value_pct = 0; value_pct <= 100; value_pct += 10 )
    {
        dac2_write_output_voltage_procentage( &dac2, value_pct );
        voltage_out = value_pct * 50;
        log_printf( &logger, "Voltage Output: %d mV\r\n", voltage_out );
        
        voltage_out = value_pct;
        log_printf( &logger, "Percentage Output: %d %%\r\n", voltage_out );
        
        log_printf( &logger, "--------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "###############################\r\n" );
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
