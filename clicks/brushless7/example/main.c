/*!
 * \file 
 * \brief Brushless7 Click example
 * 
 * # Description
 * This example demonstrates the use of Brushless 7 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Sets the default configuration and then configures the click board for the selected mode.
 * 
 * ## Application Task  
 * Increases and decreases the speed of the motor rotation by setting the duty cycle or 
 * rpm values depending on which mode is previously selected. 
 * It also switches the direction of rotation at the beginning of each cycle. 
 * All data is being logged on the USB UART where you can track their changes.
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
    Delay_ms( 100 );
    
    demo_type_data = BRUSHLESS7_CTRL_TYPE_DUTY;

    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        error_flag |= brushless7_max_duty( &brushless7, 95.0 );
        error_flag |= brushless7_start_duty( &brushless7, 5.0 );
        error_flag |= brushless7_stop_duty( &brushless7, 2.0 );
        log_printf( &logger, " ----- DUTY CONTROL ----- \r\n" );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        error_flag |= brushless7_max_speed_rpm( &brushless7, BRUSHLESS7_MAX_SPEED_4096 );
        log_printf( &logger, " ----- RPM CONTROL ----- \r\n" );
    }
    
    if ( BRUSHLESS7_DEV_ERROR == error_flag )
    {
        log_printf( &logger, " ----- ERROR ----- \r\n" );
        for( ; ; );
    }
}

void application_task ( void )
{
    brushless7_control_mode_set( &brushless7, BRUSHLESS7_CTRL_TYPE_STOP );
    brushless7_toggle_dir_pin_state ( &brushless7 );
    Delay_ms( 2000 );
    brushless7_control_mode_set( &brushless7, demo_type_data );
    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        log_printf( &logger, " The motor is accelerating...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_change_duty( &brushless7, 70.0 );
        Delay_ms( 20000 );
        
        log_printf( &logger, " The motor is slowing down...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_change_duty( &brushless7, 8.0 );
        Delay_ms( 20000 );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        log_printf( &logger, " The motor is accelerating...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        brushless7_start_rpm( &brushless7, 1000 );
        Delay_ms( 20000 );
       
        log_printf( &logger, " The motor is slowing down...\r\n" );
        log_printf( &logger, "------------------------------\r\n" );
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
