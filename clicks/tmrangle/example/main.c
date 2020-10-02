/*!
 * \file 
 * \brief TMRAngle Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates it, and then logs
 * the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, and also write log.
 * 
 * ## Application Task  
 * Reads angle value in degrees.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "tmrangle.h"

// ------------------------------------------------------------------ VARIABLES

static tmrangle_t tmrangle;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    tmrangle_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    tmrangle_cfg_setup( &cfg );
    TMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    tmrangle_init( &tmrangle, &cfg );

}

void application_task ( void )
{
    float angle;
    trigonometry_t trig_set;
    tmrangle_calib_data_t calibration_store_params;
    tmrangle_init_sensor_data( &tmrangle );

    trig_set.max_diff_sin = TMRANGLE_MAX_DIFF_SIN;
    trig_set.max_diff_cos = TMRANGLE_MAX_DIFF_COS;
    trig_set.min_diff_sin = TMRANGLE_MIN_DIFF_SIN;
    trig_set.min_diff_cos = TMRANGLE_MIN_DIFF_COS;
    trig_set.sin_45 = TMRANGLE_SIN_45;
    trig_set.cos_45 = TMRANGLE_COS_45;
    trig_set.sin_135 = TMRANGLE_SIN_135;
    trig_set.cos_135 = TMRANGLE_COS_135;

    tmrangle_init_calib_data( &tmrangle, &calibration_store_params, &trig_set );
    tmrangle_calibration_find_param( &tmrangle, &calibration_store_params );

    angle = tmrangle_get_calib_angle( &tmrangle, &calibration_store_params );

    log_printf( &logger, "Angle is %f deg\r\n", angle );

    Delay_ms( 1000 );
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
