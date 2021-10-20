/*!
 * \file 
 * \brief IrThermo3 Click example
 * 
 * # Description
 * The demo application displays ambient and object temperature measurementss
 * using IrThermo 3 click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes Driver ,resets the devic and performs calibration.
 *
 * ## Application Task
 * The device measures ambient and object temperatures and displays data in
 * degree centigrade every second.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irthermo3.h"

// ------------------------------------------------------------------ VARIABLES

static irthermo3_t irthermo3;
static log_t logger;

static float amb_temp;
static float obj_temp;
uint8_t adr_rst[ 4 ] = { 0x30, 0x05, 0x00, 0x06 };
uint8_t eeprom_unlock[ 4 ] = { 0x30, 0x05, 0x55, 0x4C };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo3_cfg_t cfg;

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

    irthermo3_cfg_setup( &cfg );
    IRTHERMO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo3_init( &irthermo3, &cfg );

    irthermo3_global_write ( &irthermo3, adr_rst, 4 );
    irthermo3_cal ( &irthermo3 );
    Delay_ms( 500 );
}

void application_task ( void )
{
    amb_temp = irthermo3_get_ambient_temperature( &irthermo3 );
    log_printf( &logger, "Ambient temperature: %.2f °C \r\n", amb_temp );

    obj_temp = irthermo3_get_object_temperature( &irthermo3 );
    log_printf( &logger, "Object temperature: %.2f °C \r\n", obj_temp );

    log_printf( &logger, "----------------------------\r\n" );
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
