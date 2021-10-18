/*!
 * \file 
 * \brief StepUp Click example
 * 
 * # Description
 * This application enables usage of DC-DC step-up (boost) regulator.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI driver, sets config word, initializes and configures the device
 * 
 * ## Application Task  
 * Sets 3 different boost precentage value to device, value changes every 10 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stepup.h"

// ------------------------------------------------------------------ VARIABLES

static stepup_t stepup;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stepup_cfg_t cfg;
    
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
    log_info( &logger, "Application Init" );

    //  Click initialization.

    stepup_cfg_setup( &cfg );
    STEPUP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepup_init( &stepup, &cfg );
    
    stepup_default_cfg( &stepup );

    Delay_ms( 100 );
    log_info( &logger, "Application Task" );
}

void application_task ( void )
{
    log_info( &logger, "Setting DAC boost to 10%%" );
    stepup_set_percentage( &stepup, 10 );
    Delay_ms( 10000 );

    log_info( &logger, "Setting DAC boost to 60%%" );
    stepup_set_percentage( &stepup, 60 );
    Delay_ms( 10000 );
    
    log_info( &logger, "Setting DAC boost to 30%%" );
    stepup_set_percentage( &stepup, 30 );
    Delay_ms( 10000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
