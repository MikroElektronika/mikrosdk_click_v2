/*!
 * \file 
 * \brief Stspin233 Click example
 * 
 * # Description
 * This application is motor driver.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init, starts basic engine setups and initializes a uart interrupt routine for logs data.
 * 
 * ## Application Task  
 * Waits for valid user input and executes functions based on set of valid commands.
 * 
 * *note:* 
 * For all other commands that you can use to control your engine, 
 * see the firmware documentation. We used an 8 pole motor for the test.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "stspin233.h"

// ------------------------------------------------------------------ VARIABLES

static stspin233_t stspin233;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    stspin233_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    stspin233_cfg_setup( &cfg );
    STSPIN233_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stspin233_init( &stspin233, &cfg );

    log_printf( &logger, " \r\n" );
    log_printf( &logger, " \r\n" );
    log_printf( &logger, ">> STSPIN233 MOTOR DRIVER <<\r\n" );
    stspin233_wakeup( &stspin233 );
    Delay_100ms( );
    
    // Motor settings
    
    log_printf( &logger, " \r\n" );
    log_printf( &logger, " \r\n" );
    log_printf( &logger, ">>> START MOTOR SETTINGS <<< \r\n" );
    
    log_printf( &logger, "> MOTOR POLE / [ 8 pole ]< \r\n" );
    stspin233_send_double_cmd( &stspin233, &STSPIN233_CMD_MOTOR_POLE,  &STSPIN233_M_POLE_8 );
    Delay_ms( 1000 );
    log_printf( &logger, "> PWM DUTY CYCLE / [ 20 percent ] < \r\n" );
    stspin233_send_double_cmd( &stspin233, &STSPIN233_CMD_SET_PWM, &STSPIN233_START_PWM_DUTY_DEF );
    Delay_ms( 1000 );
    log_printf( &logger, "> MOTOR SPEED / [1000 RPM] < \r\n" );
    stspin233_send_double_cmd( &stspin233, &STSPIN233_CMD_SET_SPEED, &STSPIN233_SPEED_DEF );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    // START MOTOR
    stspin233_send_single_cmd( &stspin233, &STSPIN233_CMD_START_MOTOR );
    log_printf( &logger, " >>> Motor is start! \r\n" );
    Delay_ms( 5000 );
    
    // STOP MOTOR
    stspin233_send_single_cmd( &stspin233, &STSPIN233_CMD_STOP_MOTOR );
    log_printf( &logger, " >>> Motor is stop! \r\n" );
    Delay_ms( 5000 );
    
    // FW STATUS
    stspin233_send_single_cmd( &stspin233, &STSPIN233_CMD_STATUS );
    log_printf( &logger, " >>> Motor status! \r\n" );
    Delay_ms( 5000 );
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
