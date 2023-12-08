/*!
 * \file 
 * \brief Angle3 Click example
 * 
 * # Description
 * This application reads data from the angle sensor, calculates it to degrees 
 * and writes it to the terminal.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - SPI,
 * set normal mode and start write log.
 * 
 * ## Application Task  
 * Angle 3 Click communicates with registers via SPI, reads data from the angle
 * sensor, calculates it to degrees and writes it to the terminal.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "angle3.h"

// ------------------------------------------------------------------ VARIABLES

static angle3_t angle3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    angle3_cfg_t angle3_cfg;

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
    angle3_cfg_setup( &angle3_cfg );
    ANGLE3_MAP_MIKROBUS( angle3_cfg, MIKROBUS_1 );
    if ( ANGLE3_ERROR == angle3_init( &angle3, &angle3_cfg ) )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again... ----" );
        for ( ; ; );
    }
    angle3_default_cfg ( &angle3 );
    
    log_info( &logger, "---- Application Task ----\n" );
}

void application_task ( void )
{
    static uint16_t angle_value_old = 0;

    if ( angle3_read_error( &angle3 ) )
    {
        uint16_t angle_value = angle3_read_angle_data( &angle3 );

        if ( angle_value_old != angle_value )
        {
            float angle_data_degrees = angle3_calculate_degrees( &angle3, angle_value );

            log_printf( &logger, " Angle : %.1f deg\r\n", angle_data_degrees );

            angle_value_old = angle_value;

            Delay_ms( 300 );
        }
    }
    else
    {
        log_printf( &logger, " Magnetic Field Too Weak\r\n" );

        angle_value_old = 0;
        Delay_ms( 1000 );
    }
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
