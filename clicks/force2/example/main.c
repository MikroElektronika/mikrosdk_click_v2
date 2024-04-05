/*!
 * \file 
 * \brief Force 2 Click example
 * 
 * # Description
 * This example demonstrates the use of Force 2 click board by reading and displaying
 * the voltage from AN pin and the calculated force (N) value.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes the driver and logger and makes an initial log.
 * 
 * ## Application Task  
 * Reads and displays the voltage from AN pin, then calculates and displays the force in N.
 * 
 * @note
 * Adjust the gain and range onboard potentiometers in order to get zero N when there's no
 * force applied to the sensor.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force2.h"

// ------------------------------------------------------------------ VARIABLES

static force2_t force2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    force2_cfg_t cfg;

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
    force2_cfg_setup( &cfg );
    FORCE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force2_init( &force2, &cfg );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force 2 click   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 500 );
}

void application_task ( void )
{
    float voltage = 0;
    if ( FORCE2_OK == force2_read_an_pin_voltage ( &force2, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage: %.3f V\r\n", voltage );
        log_printf( &logger, " Force: %.1f N\r\n", 
                    FORCE2_FORCE_MAX - voltage * FORCE2_FORCE_MAX / FORCE2_VREF );
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
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
