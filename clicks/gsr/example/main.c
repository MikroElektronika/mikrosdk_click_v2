/*!
 * \file 
 * \brief Gsr Click example
 * 
 * # Description
 * This app measure the electrodermal activity.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GSR driver.
 * 
 * ## Application Task  
 * Sequential reading of ADC and logging data 
 * to UART. Operation is repeated each 500 ms.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gsr.h"

// ------------------------------------------------------------------ VARIABLES

static gsr_t gsr;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsr_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    gsr_cfg_setup( &cfg );
    GSR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsr_init( &gsr, &cfg );
}

void application_task ( void )
{
    uint16_t adc_value;

    adc_value = gsr_read_value( &gsr );

    log_printf( &logger, "ADC Measurements: %u \r\n", adc_value );
    Delay_ms( 500 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
