/*!
 * \file 
 * \brief Accel12 Click example
 * 
 * # Description
 * This application allows acceleration measurement in three perpendicular axes.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and configuration Accel 
 * measuremen and Tap detection interrupt
 * 
 * ## Application Task  
 * Reads the acceleration data in 3 axis and detects the tap on the axes. 
 * All data logs on the USBUART every 1.5sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel12.h"

// ------------------------------------------------------------------ VARIABLES

static accel12_t accel12;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel12_cfg_t cfg;
    uint8_t temp;

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

    accel12_cfg_setup( &cfg );
    ACCEL12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel12_init( &accel12, &cfg );

    accel12_default_cfg( &accel12 );
    
    log_printf( &logger, "--- Start measurement --- \r\n" );
}

void application_task ( void )
{
    int16_t x_Axis;
    int16_t y_Axis;
    int16_t z_Axis;
    uint8_t tap;

    // Accelerometer measurement 
    
    accel12_get_axis_data( &accel12, &x_Axis, &y_Axis, &z_Axis );

    log_printf( &logger, " X axis : %d \r\n", x_Axis );
    log_printf( &logger, " Y axis : %d \r\n", y_Axis );
    log_printf( &logger, " Z axis : %d \r\n", z_Axis );

    // TAP interrupt 
    
    tap = accel12_get_tap_detection( &accel12 );
    switch ( tap )
    {
        case 1:
        {
            log_printf( &logger, " X positive \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, " Y positive \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, " Z positive \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, " X negative \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, " Y negative \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, " Z negative \r\n" );
            break;
        }
    }
    log_printf( &logger, " -------------------------------- \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
