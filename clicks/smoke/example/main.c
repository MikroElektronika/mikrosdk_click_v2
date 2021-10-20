/*!
 * \file 
 * \brief Smoke Click example
 * 
 * # Description
 * This click includes internal LEDs, photodetectors, optical elements, and low-noise electronics 
 * with ambient light rejection. The sensor can detect a wide variety of smoke particle sizes. 
 * It also has an on-chip temperature sensor for calibrating the temperature dependence of the 
 * particle sensing subsystem. The temperature sensor has an inherent resolution 0.0625°C.
 *
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies "set registers check green values" settings, 
 * "enable FIFO data ready interrupt" and makes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of Smoke Click board. It reads reflected green values and
 * temperature from an internal sensor and displays the results on USART terminal.
 * It usualy takes two or three readings in order to get corect readings. Expect big values when you do.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "smoke.h"

// ------------------------------------------------------------------ VARIABLES

static smoke_t smoke;
static log_t logger;

static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    smoke_cfg_t cfg;

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

    smoke_cfg_setup( &cfg );
    SMOKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    smoke_init( &smoke, &cfg );

    smoke_reset( &smoke );
    smoke_default_cfg ( &smoke );

    log_info( &logger, "---- Application Task ----" );
    Delay_ms( 100 );
    if ( smoke_read_leds( &smoke ) != SMOKE_OK )
    {
        log_info( &logger, "---- Init Error ----" );
        for( ; ; );
    }
}

void application_task ( void )
{
    smoke_read_leds( &smoke );
    
    log_printf( &logger, "Red : %llu\r\n", smoke.red_value );
    log_printf( &logger, "IR : %llu\r\n", smoke.ir_value );
    log_printf( &logger, "Green : %llu\r\n", smoke.green_value );
    log_printf( &logger, "------------------------------\r\n" );
    
    temperature = smoke_read_temp( &smoke );
    
    log_printf( &logger, "Read Temperature[ degC ]: %.2f\r\n",  temperature );
    log_printf( &logger, "------------------------------\r\n" );

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
