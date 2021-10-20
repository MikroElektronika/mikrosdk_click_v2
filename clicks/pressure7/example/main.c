/*!
 * \file 
 * \brief Pressure7 Click example
 * 
 * # Description
 * This example reads sensor temperature and pressure output on every 3 seconds and 
 * prints it on UART Terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialize Logger and Click object and call pressure7_read_PROM() function.
 * 
 * ## Application Task  
 * Get sensor data on every 3 seconds and send measured temperature and pressure to logger.
 * 
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure7.h"

// ------------------------------------------------------------------ VARIABLES

static pressure7_t pressure7;
static log_t logger;

static float Temperature = 0;
static float Pressure = 0;
static uint8_t prom_exit_value;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure7_cfg_t cfg;

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

    pressure7_cfg_setup( &cfg );
    PRESSURE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure7_init( &pressure7, &cfg );
    pressure7_default_cfg ( &pressure7 );
    Delay_ms( 200 );

    //  Read calibrated data from the PROM

    prom_exit_value = pressure7_read_prom( &pressure7 );
    if ( prom_exit_value == PRESSURE7_PROM_READ_OK )
    {
        log_info( &logger, "Read PROM - OK !\r\n" );
    }
    else
    {
        log_info( &logger, "Read PROM - ERROR!\r\n" );
    }
    Delay_ms( 100 );

}

void application_task ( void )
{
    pressure7_start_measurement( &pressure7 );
    pressure7_get_sensor_data( &pressure7, &Temperature, &Pressure );

    log_printf( &logger, "Temperature: %f C\r\n", Temperature );
    log_printf( &logger, "Pressure: %f\r\n", Pressure );

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
