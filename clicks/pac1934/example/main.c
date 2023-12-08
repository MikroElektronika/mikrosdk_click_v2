/*!
 * \file 
 * \brief Pac1934 Click example
 * 
 * # Description
 * This application measures the voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device, enables the device and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the most important
 * functions that PAC1934 click has, it mesures voltage, current, power and energy.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pac1934.h"

// ------------------------------------------------------------------ VARIABLES

static pac1934_t pac1934;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    pac1934_cfg_t cfg;

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

    pac1934_cfg_setup( &cfg );
    PAC1934_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1934_init( &pac1934, &cfg );
}

void application_task ( void )
{
    float read_value;
    
    pac1934_dev_reset( &pac1934 );
    pac1934_write_byte( &pac1934, PAC1934_CHANNEL_DIS, PAC1934_CHANNEL_DIS_ALL_CHA );
    pac1934_write_byte( &pac1934, PAC1934_CTRL_REG, PAC1934_CTRL_SAMPLE_RATE_8 | PAC1934_CTRL_SINGLE_SHOT_MODE );
    Delay_ms( 100 );
    pac1934_send_command( &pac1934, PAC1934_REFRESH_CMD );
    
    read_value = pac1934_measure_voltage( &pac1934, 1 );
    log_printf( &logger, "Voltage : %.2f V\r\n", read_value );

    read_value = pac1934_measure_current( &pac1934, 1 );
    log_printf( &logger, "Amperage :  %.2f mA\r\n", read_value );

    read_value = pac1934_measure_power( &pac1934, 1 );
    log_printf( &logger, "Power : %.2f W\r\n", read_value );
    
    read_value = pac1934_measure_energy( &pac1934, 1, 8 );
    log_printf( &logger, "Energy :  %.2f J \r\n", read_value );
    log_printf( &logger, "--------------------- \r\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
