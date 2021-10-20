/*!
 * \file 
 * \brief Thermo12 Click example
 * 
 * # Description
 * This application demonstrates the use of Thermo 12 Click to measure temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver, click board and sets thresholds.
 * 
 * ## Application Task  
 * Checks status register value, logs messages and temperature value.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo12.h"

// ------------------------------------------------------------------ VARIABLES

static thermo12_t thermo12;
static log_t logger;
uint8_t status_register;
float temperature;
char celsius[ 4 ] = { ' ', 176, 'C', 0x00 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo12_cfg_t cfg;
    uint8_t init_check;

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

    thermo12_cfg_setup( &cfg );
    THERMO12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo12_init( &thermo12, &cfg );
    Delay_ms( 500 );
    
    init_check = thermo12_default_cfg ( &thermo12 );
    thermo12_set_high_threshold( &thermo12, 40.00 );
    thermo12_set_low_threshold( &thermo12, 10.00 );
    thermo12_set_critical_threshold( &thermo12, 70.00 );
    thermo12_set_hysteresis ( &thermo12, 0 );


    if ( init_check == 0 )
    {
        log_printf( &logger, "App init successful\r\n" );
    }
    else 
    {
        log_printf( &logger, "App init failed\r\n" );
    }

}

void application_task ( void )
{
    status_register = thermo12_get_status( &thermo12 );

    if ( ( status_register & THERMO12_RDY_MASK ) == THERMO12_RDY_MASK )
    {
        log_printf( &logger, "Temperature: normal\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }

    if ( ( status_register & THERMO12_T_LOW_MASK ) == THERMO12_T_LOW_MASK )
    {
        log_printf( &logger, "Temperature: low\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }
    if ( ( status_register & THERMO12_T_CRIT_MASK ) == THERMO12_T_CRIT_MASK )
    {
        log_printf( &logger, "Temperature: critical\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }
     if ( ( status_register & THERMO12_T_HIGH_MASK ) == THERMO12_T_HIGH_MASK )
    {
        log_printf( &logger, "Temperature: high\r\n" );
        log_printf( &logger, "Temperature: %.2f %s\r\n", thermo12_get_temperature( &thermo12 ), celsius );
        Delay_ms( 500 );
    }
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
