/*!
 * \file 
 * \brief 3dHall6 Click example
 * 
 * # Description
 * This application measure the intensity of the magnetic field across three perpendicular axes.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 *  Executes one or more 'c3dhall6_log_xxx_task' functions
 *  
 *  Additional Functions :
 *
 *  - c3dhall6_log_adc_task() - performs and logs adc measurements on all channels
 *  - c3dhall6_log_volt_task() - performs and logs voltage measurements on all channels
 *  - c3dhall6_log_angleRad_task() - performs and logs angle measurements in radians on each die
 *  - c3dhall6_log_angleDeg_task() - performs and logs angle measurements in degrees on each die
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c3dhall6.h"

// ------------------------------------------------------------------ VARIABLES

static c3dhall6_t c3dhall6;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void c3dhall6_log_adc_task( )
{
    uint16_t ch0_adc_value;
    uint16_t ch1_adc_value;
    uint16_t ch2_adc_value;
    uint16_t ch3_adc_value;

    c3dhall6_get_adc_value( &c3dhall6, C3DHALL6_CHANNEL_0, &ch0_adc_value );
    c3dhall6_get_adc_value( &c3dhall6, C3DHALL6_CHANNEL_1, &ch1_adc_value );
    c3dhall6_get_adc_value( &c3dhall6, C3DHALL6_CHANNEL_2, &ch2_adc_value );
    c3dhall6_get_adc_value( &c3dhall6, C3DHALL6_CHANNEL_3, &ch3_adc_value );
    
    log_printf( &logger, "ADC on CH0 : %d \r\n", ch0_adc_value );
    log_printf( &logger, "ADC on CH1 : %d \r\n", ch1_adc_value );
    log_printf( &logger, "ADC on CH2 : %d \r\n", ch2_adc_value );
    log_printf( &logger, "ADC on CH3 : %d \r\n", ch3_adc_value );
}

void c3dhall6_log_volt_task( )
{
    float ch0_voltage;
    float ch1_voltage;
    float ch2_voltage;
    float ch3_voltage;

    c3dhall6_get_volt( &c3dhall6, C3DHALL6_CHANNEL_0, &ch0_voltage );
    c3dhall6_get_volt( &c3dhall6, C3DHALL6_CHANNEL_1, &ch1_voltage );
    c3dhall6_get_volt( &c3dhall6, C3DHALL6_CHANNEL_2, &ch2_voltage );
    c3dhall6_get_volt( &c3dhall6, C3DHALL6_CHANNEL_3, &ch3_voltage );
   
    log_printf( &logger, "Voltage on CH0 : %f V \r\n", ch0_voltage );
    log_printf( &logger, "Voltage on CH1 : %f V \r\n", ch1_voltage );
    log_printf( &logger, "Voltage on CH2 : %f V \r\n", ch2_voltage );
    log_printf( &logger, "Voltage on CH3 : %f V \r\n", ch3_voltage );
}

void c3dhall6_log_angle_rad_task( )
{
    float die_a_angle;
    float die_b_angle;

    c3dhall6_get_angle_rad( &c3dhall6, C3DHALL6_DIE_A, &die_a_angle );
    c3dhall6_get_angle_rad( &c3dhall6, C3DHALL6_DIE_B, &die_b_angle );

    log_printf( &logger, "DIE A Angle value :  %f rad \r\n", die_a_angle );
    log_printf( &logger, "DIE B Angle value :  %f rad \r\n", die_b_angle );    
}

void c3dhall6_log_angle_deg_task( )
{
    float die_a_angle;
    float die_b_angle;
    char degree_unit[2] = { 176, 0 };

    c3dhall6_get_angle_deg( &c3dhall6, C3DHALL6_DIE_A, &die_a_angle );
    c3dhall6_get_angle_deg( &c3dhall6, C3DHALL6_DIE_B, &die_b_angle );

    log_printf( &logger, "DIE A Angle value :  %f %c \r\n", die_a_angle, degree_unit );
    log_printf( &logger, "DIE B Angle value :  %f %c \r\n", die_b_angle, degree_unit ); 
    
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall6_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );


    //  Click initialization.

    c3dhall6_cfg_setup( &cfg );
    C3DHALL6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall6_init( &c3dhall6, &cfg );

    Delay_ms( 300 );
    c3dhall6_set_reference_values( &c3dhall6, 3.3, 2048.0, 2048.0, 2048.0, 2048.0 );
}

void application_task ( void )
{
    c3dhall6_log_angle_deg_task( );
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
