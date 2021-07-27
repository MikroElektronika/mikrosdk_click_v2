/*!
 * \file 
 * \brief HBridge3 Click example
 * 
 * # Description
 * H-bridge in general, allows the current to flow in one or another direction.
 * This click is used for driving a H-Bridge motor by changing output states. 
 * The outputs can be pulse width modulated at frequencies up to 20kHz by means of PWM/DIR control. 
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI and LOG modules, AN, RST, CS and PWM pins
 * 
 * ## Application Task  
 * This example demonstrates the use of H-Bridge 3 Click board, 
 * by running dc motor in both directions - increasing and decreasing PWM duty cycle.
 * 
 * ## Additional Functions :
 * 
 * - void case_plus( ) - Increments duty cycle
 * - void case_minus( ) - Decrements duty cycle
 * - void case_diagnosis( ) - Gets diagnosis register content and logs status message
 * - void case_direction1( ) - Changes rotation direction to direction 1
 * - void case_direction2( ) - Changes rotation direction to direction 2
 * - void case_on_off( ) - Switches oputput MOSFETs on and off
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "hbridge3.h"

// ------------------------------------------------------------------ VARIABLES

static hbridge3_t hbridge3;
static log_t logger;

static float duty_cycle = 0;
static float duty_cycle_max = 0;
static float duty_cycle_min = 0;

static uint8_t spi_response;
static uint8_t diagnosis_old = 0;
static uint8_t diagnosis_new = 0;
static uint8_t on_off_toggle = 0;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_diagnosis ( uint8_t diagnostic_byte )
{
    switch ( diagnostic_byte )
    {
        case 0x03 :
        {
            log_printf( &logger, "> VS Undervoltage (VS_UV)\r\n" );
            break;
        }
        case 0x05 :
        {
            log_printf( &logger, "> Short to Battery at OUT1 and OUT2 (SCB1, SCB2)\r\n" );
            break;
        }
        case 0x06 :
        {
            log_printf( &logger, "> Short to GND at OUT1 and short to Bat. at OUT2 (SCG1, SCB2)\r\n" );
            break;
        }
        case 0x07 :
        {
            log_printf( &logger, "> Short to Battery at OUT2 (SCB2)\r\n" );
            break;
        }
        case 0x09 :
        {
            log_printf( &logger, "> Short to Bat. at OUT1 and short to GND at OUT2 (SCB1, SCG2)\r\n" );
            break;
        }
        case 0x0A :
        {
            log_printf( &logger, "> Short to GND at OUT1 and OUT2 (SCG1, SCG2)\r\n" );
            break;
        }
        case 0x0B :
        {
            log_printf( &logger, "> Short to GND at OUT2 (SCG2)\r\n" );
            break;
        }
        case 0x0C :
        {
            log_printf( &logger, "> Open Load (OL)\r\n" );
            break;
        }
        case 0x0D :
        {
            log_printf( &logger, "> Short to Battery at OUT1 (SCB1)\r\n" );
            break;
        }
        case 0x0E :
        {
            log_printf( &logger, "> Short to GND at OUT1 (SCG1)\r\n" );
            break;
        }
        case 0x0F :
        {
            log_printf( &logger, "> No failure\r\n" );
            break;
        }
        default :
        {
            log_printf( &logger, "> Unknown message\r\n" );
            break;
        }
    }
}

void case_plus ( )
{
    if ( duty_cycle < duty_cycle_max )
    {
        duty_cycle +=0.1;
        hbridge3_set_duty_cycle ( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %u\r\n", duty_cycle );
    }
    else
    {
        log_printf( &logger, "> duty cycle max\r\n" );
    }
}

void case_minus ( )
{
    if ( duty_cycle > duty_cycle_min )
    {
        duty_cycle -=0.1;
        hbridge3_set_duty_cycle ( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %u\r\n", duty_cycle );
    }
    else
    {
        log_printf( &logger, "> duty cycle min\r\n" );
    }
}

void case_diagnosis ( )
{
    spi_response = hbridge3_spi( &hbridge3, HBRIDGE3_CMD_RD_DIA );
    spi_response &= 0x0F;
    log_diagnosis( spi_response );
}

void case_direction1( )
{
    hbridge3_dir_set( &hbridge3, 0 );
    log_printf( &logger, "> direction 1\r\n" );
}

void case_direction2( )
{
    hbridge3_dir_set( &hbridge3, 1 );
    log_printf( &logger, "> direction 2\r\n" );
}

void case_on_off( )
{
    if ( on_off_toggle == 0 )
    {
        hbridge3_dis_set( &hbridge3, 1 );
        log_printf( &logger, "> outputs disabled\r\n" );
        on_off_toggle = 1;
    }
    else if ( on_off_toggle == 1 )
    {
        hbridge3_dis_set( &hbridge3, 0 );
        log_printf( &logger, "> outputs enabled\r\n" );
        on_off_toggle = 0;
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hbridge3_cfg_setup( &cfg );
    HBRIDGE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge3_init( &hbridge3, &cfg );

    Delay_ms( 500 );
    
    hbridge3_pwm_start( &hbridge3 );
}

void application_task ( void )
{
    log_printf( &logger, "------------------------------\r\n" );
    case_direction1( );
    Delay_ms( 20 );
    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
    
    for ( duty_cycle = 1; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
    
    log_printf( &logger, "------------------------------\r\n" );
    case_direction2( );
    Delay_ms( 20 );
    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
    
    for ( duty_cycle = 1; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
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
