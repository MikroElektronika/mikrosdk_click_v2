/*!
 * \file 
 * \brief Thermo9 Click example
 * 
 * # Description
 * This demoapp measures temperature every 3 seconds.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Logger initialization, click initialization and calibration.
 * 
 * ## Application Task  
 * This example shows capabilities of Thermo 9 click by measuring
 * temperature every 3 seconds and displaying temperature in degrres Celsius 
 * via USART terminal.
 * 
 * *note:* 
 * Calibration function must be used once in order to get calibrations!
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo9.h"

// ------------------------------------------------------------------ VARIABLES

static thermo9_t thermo9;
static log_t logger;
static float temp_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo9_cfg_t cfg;

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

    thermo9_cfg_setup( &cfg );
    THERMO9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo9_init( &thermo9, &cfg );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Thermo 9 click   \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    thermo9_calibation( &thermo9 );
    Delay_ms( 100 );
    log_printf( &logger, "      Calibrated     \r\n" );
    log_printf( &logger, "---------------------\r\n" );
}

void application_task ( void )
{
    //  Task implementation.
    temp_val = thermo9_read_temp( &thermo9 );
    log_printf( &logger, "-- Temperature : %.2f C\r\n", temp_val );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 2000 );
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
