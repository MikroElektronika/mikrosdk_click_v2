/*!
 * \file 
 * \brief LightRanger4 Click example
 * 
 * # Description
 * Demo application is used to shows basic controls LightRanger 4 click
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Settings the click in the default configuration,
 * adjusts the LONG mode (distance measurement up to 4 meters),
 * sets the time budget and start measurement with the adjustment of inter measurements period.
 * 
 * ## Application Task  
 * Reads the distance of the object in front of the sensor and logs 
 * distance to USBUART every 500 ms.
 * 
 * \author Katarina Perendic
 *
 */

// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lightranger4.h"

// ------------------------------------------------------------------ VARIABLES

static lightranger4_t lightranger4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lightranger4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lightranger4_cfg_setup( &cfg );
    LIGHTRANGER4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lightranger4_init( &lightranger4, &cfg );

    lightranger4_power_on( &lightranger4 );
    log_info( &logger, "--- Wait until the configuration of the chip is completed ---" );

    lightranger4_default_cfg( &lightranger4 );
    lightranger4_set_distance_mode( &lightranger4, LR4_DISTANCE_MODE_LONG );
    lightranger4_set_measurement_timing_budget( &lightranger4, 1000 );
    lightranger4_start_measurement( &lightranger4, 20 );

    log_info( &logger, "--- Sensor start measurement ---" );
    Delay_100ms( );
}

void application_task ( void )
{
    uint16_t distance;
    uint8_t m_status;

    //  Task implementation.

    while ( lightranger4_new_data_ready( &lightranger4 ) != 0 )
    {
        Delay_1ms();
    }

    distance = lightranger4_get_distance( &lightranger4 );
    log_printf( &logger, "** Distance: %d mm \r\n", distance );

    m_status = lightranger4_get_range_status( &lightranger4 );
    switch ( m_status )
    {
        case LR4_MRESP_SIGNAL_FAIL:
        {
            log_info( &logger, "Signal fail." );
            break;
        }
        case LR4_MRESP_PHASE_OUT_OF_VALID_LIMITS:
        {
            log_info( &logger, "Phase out of valid limits" );
            break;
        }
        case LR4_MRESP_SIGMA_FAIL:
        {
            log_info( &logger, "Sigma Fail. " );
            break;
        }
        case LR4_MRESP_WRAP_TARGET_FAIL:
        {
            log_info( &logger, "Wrap target fail." );
            break;
        }
        case LR4_MRESP_MINIMUM_DETECTION_THRESHOLD:
        {
            log_info( &logger, "Target is below minimum detection threshold. " );
            break;
        }
    }
    Delay_ms( 500 );
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
