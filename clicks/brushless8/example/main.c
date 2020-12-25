/*!
 * @file main.c
 * @brief Brushless8 Click example
 *
 * # Description
 * TODO.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init 
 * Initializes the click board to appropriate settings based on selected mode.
 * Initialization settings are sent through I2C bus and the motor itself is
 * controlled via PWM or DAC over I2C.
 * Modes:
 *     - BRUSHLESS8_PWM
 *     - BRUSHLESS8_DAC
 *
 * ## Application Task  
 * This example demonstrates the use of Brushless 8 click board.
 * Brushless 8 click communicates with the device via I2C driver in order to 
 * set adequate voltage level for connected motor.
 * Current PWM/DAC settings being output are sent via logger.
 * 
 * @note Take into consideration that the jumper on Brushless 8 click board
 * has to be set adequately for selected mode ( @b VSPSEL ).
 *
 * @author Luka Filipovic
 */

// ------------------------------------------------------------------- INCLUDES

#include "brushless8.h"
#include "board.h"
#include "math.h"
#include "log.h"

/* Select desired mode. */
#define BRUSHLESS8_MODE BRUSHLESS8_PWM
// #define BRUSHLESS8_MODE BRUSHLESS8_DAC

#define COMM_DELAY 1000

// ------------------------------------------------------------------ VARIABLES

static brushless8_t brushless8;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless8_cfg_t brushless8_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "Application Init" );

    // Click initialization.

    brushless8_cfg_setup( &brushless8_cfg );
    // Select desired mode.
    brushless8_cfg.ctrl_mod = BRUSHLESS8_MODE;
    BRUSHLESS8_MAP_MIKROBUS( brushless8_cfg, MIKROBUS_1 );

    BRUSHLESS8_RETVAL init_flag = brushless8_init( &brushless8, &brushless8_cfg );
    if ( BRUSHLESS8_OK != init_flag )
    {
        log_error( &logger, "Application Init Error" );
        log_info( &logger, "Please, run program again..." );

        for ( ; ; );
    }

    brushless8_default_cfg ( &brushless8 );

    if ( BRUSHLESS8_PWM == brushless8.ctrl_mod )
    {
        brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 0 );
        brushless8_set_duty_cycle( &brushless8, 0.1 );
        brushless8_pwm_start( &brushless8 );

        Delay_ms( 3000 );
    }
    else if ( BRUSHLESS8_DAC == brushless8.ctrl_mod )
    {
        brushless8_pwm_stop( &brushless8 );
        brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, 100 );

        Delay_ms( 3000 );
    }

    log_info( &logger, "Application Task" );
    log_printf( &logger, "------------------------------\r\n" );
}

void application_task ( void )
{
    if ( BRUSHLESS8_PWM == brushless8.ctrl_mod )
    {
        for ( float duty = 0.1; duty < 1; duty += 0.1 )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_DIS );
            brushless8_set_duty_cycle( &brushless8, duty );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "Duty: %u%%", ( uint16_t )ceil( duty * 100 ) );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }

        for ( float duty = 0.9; duty >= 0; duty -= 0.1 )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_DIS );
            brushless8_set_duty_cycle( &brushless8, duty );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "Duty: %u%%", ( uint16_t )ceil( duty * 100 ) );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }

        Delay_ms( COMM_DELAY );
        brushless8_pwm_stop( &brushless8 );
        Delay_ms( COMM_DELAY );
        brushless8_pwm_start( &brushless8 );
    } else if ( BRUSHLESS8_DAC == brushless8.ctrl_mod ) {
        for ( int16_t dsvp = 200; dsvp <= 5000; dsvp += ( ( 5000 - 200 ) / 10 ) )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, ( uint16_t )dsvp );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "DSVP [ mV ]: %d", dsvp );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }

        for ( int16_t dsvp = 5000; dsvp >= 200; dsvp -= ( ( 5000 - 200 ) / 10 ) )
        {
            Delay_ms( COMM_DELAY );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            brushless8_set_dac_vout( &brushless8, BRUSHLESS8_DAC_REG_CHN_A_DVSP, ( uint16_t )dsvp );
            brushless8_set_reset( &brushless8, BRUSHLESS8_RESET_EN );
            log_info( &logger, "DSVP [ mV ]: %d", dsvp );

            float adc_vout;
            brushless8_read_an_voltage( &brushless8, &adc_vout );
            log_info( &logger, "ADC [ V ]: %.2f", adc_vout );

            log_printf( &logger, "------------------------------\r\n" );
        }
    } else {
        log_error( &logger, "Application Task Error" );
        log_info( &logger, "Please, run program again..." );

        for ( ; ; );
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
