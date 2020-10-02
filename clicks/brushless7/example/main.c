/*!
 * \file 
 * \brief Brushless7 Click example
 * 
 * # Description
 * This demo app changes values of duty and rpm.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Setts default configuration and sets parameters for selected mode.
 * 
 * ## Application Task  
 * Sets 3 different speed of motor in span of 20 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "brushless7.h"

// ------------------------------------------------------------------ VARIABLES

static brushless7_t brushless7;
static log_t logger;

uint8_t demo_type_data = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void stop_start (  )
{
    brushless7_control_mode_set( &brushless7, BRUSHLESS7_CTRL_TYPE_STOP );
    Delay_ms( 1000 );
    brushless7_control_mode_set( &brushless7, demo_type_data );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless7_cfg_t cfg;
    uint8_t error_flag = 0;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless7_cfg_setup( &cfg );
    BRUSHLESS7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless7_init( &brushless7, &cfg );
    
    Delay_ms( 100 );

    brushless7_default_cfg( &brushless7 );
    
    demo_type_data = BRUSHLESS7_CTRL_TYPE_DUTY;

    brushless7_control_mode_set( &brushless7, demo_type_data );
    brushless7_rotating_direction( &brushless7, BRUSHLESS7_DIR_CW );

    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        error_flag |= brushless7_max_duty( &brushless7, 95.0 );
        error_flag |= brushless7_start_duty( &brushless7, 5.0 );
        error_flag |= brushless7_stop_duty( &brushless7, 2.0 );
        brushless7_change_duty( &brushless7, 20 );
        log_printf( &logger, " ----- DUTY CONTROL ----- \r\n" );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        error_flag |= brushless7_max_speed_rpm( &brushless7, BRUSHLESS7_MAX_SPEED_4096 );
        error_flag |= brushless7_start_rpm( &brushless7, 400 );
        log_printf( &logger, " ----- RPM CONTROL ----- \r\n" );
    }
    
    if ( BRUSHLESS7_DEV_ERROR == error_flag )
    {
        log_printf( &logger, " ----- ERROR ----- \r\n" );
        for( ; ; );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}

void application_task ( void )
{
    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        log_printf( &logger, " ----- 20 ----- \r\n" );
        stop_start( );
        brushless7_change_duty( &brushless7, 20 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 40 ----- \r\n" );
        stop_start( );
        brushless7_change_duty( &brushless7, 40 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 8 ----- \r\n" );
        stop_start( );
        brushless7_change_duty( &brushless7, 8 );
        Delay_ms( 20000 );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        log_printf( &logger, " ----- 400 ----- \r\n" );
        stop_start( );
        brushless7_start_rpm( &brushless7, 400 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 1000 ----- \r\n" );
        stop_start( );
        brushless7_start_rpm( &brushless7, 1000 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 100 ----- \r\n" );
        stop_start( );
        brushless7_start_rpm( &brushless7, 100 );
        Delay_ms( 20000 );
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
