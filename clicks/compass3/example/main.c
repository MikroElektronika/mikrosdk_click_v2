/*!
 * \file 
 * \brief Compass3 Click example
 * 
 * # Description
 * This demoapp measures the magnetic field surrounding the device.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and click driver, performs check, applies default 
 * setup and writes an initial log.
 * 
 * ## Application Task  
 *  This example demonstrates the use of 
 * Compass 3 Click board by measuring the magnetic field surrounding the device.
 * 
 * \author Jovan Stajkovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "compass3.h"

// ------------------------------------------------------------------ VARIABLES

static compass3_t compass3;
static log_t logger;
static float x_val;
static float y_val;
static float z_val;
static uint8_t test_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    compass3_cfg_t cfg;

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

    compass3_cfg_setup( &cfg );
    COMPASS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass3_init( &compass3, &cfg );
    Delay_ms ( 100 );
    
    compass3_generic_read( &compass3, COMPASS3_DEVICE_ID, &test_val, 1 );

    if ( test_val == COMPASS3_DEVICE_ID_NUM )
    {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "   Compass 3 click  \r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "   Fatal error!!!   \r\n" );
        for ( ; ; );
    }

    compass3_default_cfg ( &compass3 );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    if ( compass3_check_int( &compass3 ) == COMPASS3_INTERRUPT )
    {
        compass3_full_measurement ( &compass3, &x_val, &y_val, &z_val );

        log_printf( &logger,"  X-axis : %.2f mG\r\n", x_val );
        log_printf( &logger,"  Y-axis : %.2f mG\r\n", y_val );
        log_printf( &logger,"  Z-axis : %.2f mG\r\n", z_val );

        Delay_ms ( 1000 );
        log_printf( &logger, "--------------------\r\n" );
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
