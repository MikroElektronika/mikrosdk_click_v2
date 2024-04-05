/*!
 * \file 
 * \brief IR distance Click example
 * 
 * # Description
 * The click board outputs an analog voltage corresponding to the distance of the object 
 * (through the mikroBUS AN pin). An Enable (EN) pin is also utilized.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO, enable IR sensor, initialization ADC, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of IR Distance click board.
 * IR Distance click reads and displays ADC value.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on USB uart change for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irdistance.h"

// ------------------------------------------------------------------ VARIABLES

static irdistance_t irdistance;
static log_t logger;

static uint16_t adc_val;
static float voltage_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irdistance_cfg_t cfg;

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

    irdistance_cfg_setup( &cfg );
    IRDISTANCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( irdistance_init( &irdistance, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    irdistance_enable_device( &irdistance );
    log_info( &logger, "---- Application Init Done ----\r\n" );

    voltage_val = 0;
    adc_val = 0;
}

void application_task ( void )
{
    if ( irdistance_read_adc( &irdistance, &adc_val ) != ADC_ERROR )
    {
        log_printf( &logger, " ADC value on the pin : %u\r\n", adc_val );
    }

    if ( irdistance_get_pin_voltage( &irdistance, &voltage_val ) != ADC_ERROR )
    {
        log_printf( &logger, " Voltage value on the pin : %.2f\r\n", voltage_val );
    }

    log_printf( &logger, "------------------------------\r\n" );
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
