/*!
 * \file 
 * \brief Pot2 Click example
 * 
 * # Description
 * This demo-app shows the ADC values using POT 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configures Clicks and log objects.
 * 
 * ## Application Task  
 * Demo app reads ADC data and displays them as dec and hex values every second
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pot2.h"

// ------------------------------------------------------------------ VARIABLES

static pot2_t pot2;
static log_t logger;

static uint16_t adc_val;
static float voltage_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pot2_cfg_t cfg;

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

    pot2_cfg_setup( &cfg );
    POT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( pot2_init( &pot2, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----\r\n" );

    voltage_val = 0;
    adc_val = 0;
}

void application_task ( void )
{
    if ( pot2_read_adc ( &pot2, &adc_val ) != ADC_ERROR )
    {
        log_printf( &logger, " ADC value : [DEC] %u, [HEX] 0x%x\r\n", adc_val, adc_val );
    }

    if ( pot2_read_pin_voltage ( &pot2, &voltage_val ) != ADC_ERROR )
    {
        log_printf( &logger, " Voltage value : %.2f\r\n", voltage_val );
    }

    log_printf( &logger, "------------------------------------------\r\n" );
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
