/*!
 * \file 
 * \brief Motion 2 Click example
 * 
 * # Description
 * Demo example shows the detection of object movement near the sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes all necessary GPIO pins and activates the motion sensor
 * 
 * ## Application Task  
 *  Checks if an object is detected. 
 *  Prints a message about the object detection and
 *  whether the sensor has stabilized after object detection.
 * 
 * *note:* 
 * The sensor needs a maximum of 30s to stabilize. 
 * See the sensor technical documentation for more information.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "motion2.h"

// ------------------------------------------------------------------ VARIABLES

static motion2_t motion2;
static log_t logger;

static uint8_t motion_detect_flag = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    motion2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    motion2_cfg_setup( &cfg );
    MOTION2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    motion2_init( &motion2, &cfg );

    motion2_active( &motion2, MOTION2_MODULE_ENABLE );
    log_info( &logger, "--- Motion sensor is enabled... ----\r\n" );
    Delay_100ms( );
}

void application_task ( void )
{
    uint8_t motion_state;
    
    motion_state = motion2_detect_state( &motion2 );
    
    if ( ( motion_detect_flag == 0 ) &&
         ( motion_state == MOTION2_DETECT_OBJECT ) )
    {
        log_info( &logger, ">>> Object is detected...\r\n" );
        motion_detect_flag = 1;
        Delay_ms( 500 );
    }
    
    if ( ( motion_detect_flag == 1 ) && 
         ( motion_state != MOTION2_DETECT_OBJECT ) )
    {
        log_info( &logger, ">>> Sensor has stabilized..\r\n" );
        log_info( &logger, ">>> Ready for new detection...\r\n" );
        log_info( &logger, ">>> --------------------------\r\n" );
        motion_detect_flag = 0;
    }
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
