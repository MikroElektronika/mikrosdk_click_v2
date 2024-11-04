/*!
 * \file 
 * \brief Buck 2 Click example
 * 
 * # Description
 * This application demonstrates the use of Buck 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the Click board.
 * 
 * ## Application Task  
 * Sets a different output voltage every 5 seconds then checks if the voltage on 
 * the output (OUTSNS) drops under 90% of the regulated voltage 
 * and displays an appropriate message on USB UART.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck2.h"

// ------------------------------------------------------------------ VARIABLES

static buck2_t buck2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck2_cfg_t cfg;

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

    buck2_cfg_setup( &cfg );
    BUCK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck2_init( &buck2, &cfg );

    buck2_default_cfg( &buck2 );
}

void application_task ( void )
{
    uint8_t pg_state;

    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_3300mV );
    log_printf( &logger, "---- Output voltage is 3300 mV ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_2500mV );
    log_printf( &logger, "---- Output voltage is 2500 mV ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1800mV );
    log_printf( &logger, "---- Output voltage is 1800 mV ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
    buck2_set_output_voltage( &buck2, BUCK2_SET_VOLTAGE_1500mV );
    log_printf( &logger, "---- Output voltage is 1500 mV ----\r\n" );
    log_printf( &logger, "-----------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    pg_state = buck2_get_power_good( &buck2 );
    if ( pg_state == 0 )
    {
        log_info( &logger, "---- Voltage of the output dropped under 90%% of the regulated voltage ----" );
    }
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
