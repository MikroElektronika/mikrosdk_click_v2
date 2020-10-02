/*!
 * \file 
 * \brief QiReceiver Click example
 * 
 * # Description
 * This application reads voltage, current and frequency.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 *  Initalizes I2C driver, enables the device and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the most important
 * functions that Qi Receiver click has, it mesures current voltage, amperage and frequency.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "qireceiver.h"

// ------------------------------------------------------------------ VARIABLES

static qireceiver_t qireceiver;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    qireceiver_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    qireceiver_cfg_setup( &cfg );
    QIRECEIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    qireceiver_init( &qireceiver, &cfg );
    
    Delay_ms( 100 );
    qireceiver_dev_enable( &qireceiver );
    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, "Qi Receiver Click\r\n" );
    log_printf( &logger, "-----------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    float voltage;
    float current;
    float freq;
    
    voltage = qireceiver_read_voltage( &qireceiver );
    log_printf( &logger, "Voltage : %.2f V\r\n", voltage );

    current = qireceiver_read_current( &qireceiver );
    log_printf( &logger, "Current : %.2f A\r\n", current );

    freq = qireceiver_read_freq( &qireceiver );
    log_printf( &logger, "Frequency : %.2f Hz\r\n", freq );
    
    log_printf( &logger, "-----------------\r\n" );
    Delay_ms( 1000 );
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
