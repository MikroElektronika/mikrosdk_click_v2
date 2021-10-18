/*!
 * \file 
 * \brief Thermostat3 Click example
 * 
 * # Description
 * This application enables usage of the general puprose Thermostat click to be used with temperature sensors.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init
 * 
 * ## Application Task  
 * Waits for valid user input and executes functions based on set of valid commands
 * 
 * *note:* 
 * - Additional Functions :
 *      -void _displayFault( uint8_t f_error )  - Display fault
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermostat3.h"

// ------------------------------------------------------------------ VARIABLES

static thermostat3_t thermostat3;
static temp_vals_t temp_val;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void display_fault ( uint8_t f_error )
{
    switch ( f_error )
    {
        case 3:
        {
            log_printf( &logger, "# Active - Fault flag " );
            break;
        }
        case 2:
        {
            log_printf( &logger, "# SCV - Fault flag " );
            break;
        }
        case 1:
        {
            log_printf( &logger,"# SCG - Fault flag " );
            break;
        }
        case 0:
        {
            log_printf( &logger,"# OC - Fault flag " );
            break;
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat3_cfg_t cfg;

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

    Delay_ms( 100 );

    //  Click initialization.

    thermostat3_cfg_setup( &cfg );
    THERMOSTAT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermostat3_init( &thermostat3, &cfg );

    // Power on delay
    Delay_ms( 200 );
    log_printf( &logger, "---- Start Thermostat 3 ----\r\n" );
}

void application_task ( void )
{
    //  Task implementation.

    float internal_temp;
    float thermocouple_temp;

    thermostat3_process( &thermostat3, &temp_val );

    internal_temp = thermostat3_get_internal_temperature( &temp_val, THERMOSTAT3_TEMP_IN_CELSIUS );
    log_printf( &logger, "# Internal Temperature: %.2f", internal_temp );
    Delay_ms( 200 );
   
    thermocouple_temp = thermostat3_get_thermocouple_temperature( &temp_val, THERMOSTAT3_TEMP_IN_CELSIUS );
    log_printf( &logger, "# Thermocouple Temperature: %.2f", thermocouple_temp );
    Delay_ms( 200 );
    
    if( thermostat3.relay_flag == 1)
    {
        thermostat3.relay_flag = 0;
        thermostat3_relay_control( &thermostat3, THERMOSTAT3_RELAY_OFF );
        log_printf( &logger, "# Relay OFF\r\n" );
    }
    else
    {
        thermostat3.relay_flag = 1;
        thermostat3_relay_control( &thermostat3, THERMOSTAT3_RELAY_ON );
        log_printf( &logger, "# Relay ON\r\n" );
    }
    Delay_ms( 200 );

    if( thermostat3.fault_flag == 1 )
    {
        thermostat3.fault_flag = 0;
        log_printf( &logger, "# Fault status -- OFF\r\n" );
    }
    else
    {
        thermostat3.fault_flag = 1;
        log_printf( &logger, "# Fault status -- ON\r\n" );
    }
    Delay_ms( 200 );

    if( thermostat3.fault_flag == 1 )
        {
            thermostat3.f_error++;
            if( thermostat3.f_error > 3 )
            {
                thermostat3.f_error = 0;
            }
            display_fault( thermostat3.f_error );
            
            thermostat3.fault_status = thermostat3_get_fault_data( &temp_val, 0x01 << thermostat3.f_error );
            
            if ( thermostat3.fault_status == 1 )
            {
                log_printf( &logger, " -- ERROR\r\n" );
            }
            else
            {
                log_printf( &logger, " -- OK\r\n" );
            }
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
