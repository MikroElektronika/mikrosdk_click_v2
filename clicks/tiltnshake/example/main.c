/*!
 * \file 
 * \brief TiltNshake Click example
 * 
 * # Description
 * This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device init
 * 
 * ## Application Task  
 * Reads every tilt and shake and logs to USBUART_A.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tiltnshake.h"

// ------------------------------------------------------------------ VARIABLES

static tiltnshake_t tiltnshake;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    tiltnshake_cfg_setup( &cfg );
    TILTNSHAKE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tiltnshake_init( &tiltnshake, &cfg );
    
}

void application_task ( )
{
    uint8_t tiltnshake_status;
    float tiltnshake_out_x_float;
    float tiltnshake_out_y_float;
    float tiltnshake_out_z_float;
    uint16_t tiltnshake_out_x;
    uint16_t tiltnshake_out_y;
    uint16_t tiltnshake_out_z;

    tiltnshake_enable( &tiltnshake, TILTNSHAKE_ENABLE );
    tiltnshake_read_status_and_axis( &tiltnshake, &tiltnshake_status, &tiltnshake_out_x, &tiltnshake_out_y, &tiltnshake_out_z );
    tiltnshake_enable( &tiltnshake, TILTNSHAKE_DISABLE );

    if ( tiltnshake_status == TILTNSHAKE_DATA_READY )
    {
        tiltnshake_conversion
        ( 
             &tiltnshake_out_x, 
             &tiltnshake_out_y, 
             &tiltnshake_out_z,
             &tiltnshake_out_x_float, 
             &tiltnshake_out_y_float, 
             &tiltnshake_out_z_float 
        ); 
        
        log_printf( &logger, " \r\n" );
        log_printf( &logger, "X_out = %.2f \r\n", tiltnshake_out_x_float );
        log_printf( &logger, "Y_out = %.2f\r\n", tiltnshake_out_y_float );
        log_printf( &logger, "Z_out = %.2f\r\n", tiltnshake_out_z_float );
        log_printf( &logger, "-----------------------------------------------\r\n");
        Delay_ms( 500 );
    }
    Delay_ms( 1700 );
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
