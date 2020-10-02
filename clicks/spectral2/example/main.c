/*!
 * \file 
 * \brief Spectral2 Click example
 * 
 * # Description
 * This application enables usage of multispectral color sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initialize, reset module and configuration measurement
 * 
 * ## Application Task  
 * Reads the brightness value with R, G, B, I, O and V filter, every 1 second, and logs on to USBUART.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spectral2.h"

// ------------------------------------------------------------------ VARIABLES

static spectral2_t spectral2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral2_cfg_t cfg;
    uint8_t cfg_data;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    spectral2_cfg_setup( &cfg );
    SPECTRAL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral2_init( &spectral2, &cfg );

    spectral2_reset( &spectral2 );

    Delay_100ms( );
    log_printf( &logger, "--- System init ---\r\n" );

    cfg_data = ( SPECTRAL2_NORMAL_OPERATION | SPECTRAL2_INT_DISABLE |
                                   SPECTRAL2_GAIN_16X |
                                   SPECTRAL2_MODE_2 );

    spectral2_default_cfg( &spectral2, cfg_data );

    Delay_1sec( );
}

void application_task ( void )
{
    float f_data;

    //  Task implementation.

    log_printf( &logger, "-------------------\r\n" );

    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_R );
    log_printf( &logger, "-- R ( Red data ) : %.2f \r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_G );
    log_printf( &logger, "-- G ( Green data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_B );
    log_printf( &logger, "-- B ( Blue data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_Y );
    log_printf( &logger, "-- Y ( Yellow data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_O );
    log_printf( &logger, "-- O ( Orange data ) : %.2f\r\n", f_data );
    
    f_data = spectral2_get_calibrated_data( &spectral2, SPECTRAL2_CALIBRATED_DATA_V );
    log_printf( &logger, "-- V ( Violet data ) : %.2f\r\n", f_data );
    
    Delay_1sec( );
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
