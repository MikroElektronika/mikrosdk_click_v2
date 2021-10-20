/*!
 * \file 
 * \brief Thermo14 Click example
 * 
 * # Description
 * Thermo 14 Click provides an accuracy of ±0.5°C in the range from -10°C to 60°C.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, sets up the device.
 * 
 * ## Application Task  
 * This example shows capabilities of Thermo 14 click by measuring
   temperature every 3 seconds and displaying temperature in degrres Celsius via USART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo14.h"

// ------------------------------------------------------------------ VARIABLES

static thermo14_t thermo14;
static log_t logger;

static float temp_val;
static char deg_cel[ 3 ] = { 176, 67, 0 };
static uint16_t disp_temp;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_display( float value )
{
    disp_temp = ( uint16_t ) value;

    disp_temp = ( uint16_t ) ( value * 100.0 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo14_cfg_t cfg;
    
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

    thermo14_cfg_setup( &cfg );
    THERMO14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo14_init( &thermo14, &cfg );

    Delay_ms( 100 );
    thermo14_default_cfg( &thermo14 );
}

void application_task ( void )
{
    temp_val = thermo14_get_temperature( &thermo14 );

    log_printf( &logger, " Temperature: %.2f C \r\n ", temp_val );
    Delay_ms( 3000 );
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
