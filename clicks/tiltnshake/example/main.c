/*!
 * \file 
 * \brief TiltNshake Click example
 * 
 * # Description
 * This application is multifunctional 3-axis digital accelerometer
 * that can also be configured as a 45-degree Tilt sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Reads 3-axis accelerometer measurement and logs results on the USB UART.
 * 
 * \author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "tiltnshake.h"

static tiltnshake_t tiltnshake;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    tiltnshake_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    tiltnshake_cfg_setup( &cfg );
    TILTNSHAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tiltnshake_init( &tiltnshake, &cfg );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t status = 0;
    float out_x = 0;
    float out_y = 0;
    float out_z = 0;

    tiltnshake_enable( &tiltnshake );
    tiltnshake_read_status_and_axis( &tiltnshake, &status, &out_x, &out_y, &out_z );
    tiltnshake_disable( &tiltnshake );

    if ( TILTNSHAKE_DATA_READY == status )
    {
        log_printf( &logger, " X: %.2f\r\n", out_x );
        log_printf( &logger, " Y: %.2f\r\n", out_y );
        log_printf( &logger, " Z: %.2f\r\n", out_z );
        log_printf( &logger, "----------\r\n");
        Delay_ms( 500 );
    }
    Delay_ms( 500 );
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
