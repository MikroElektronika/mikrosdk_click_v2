/*!
 * @file main.c
 * @brief LEDDriver9 Click example
 *
 * # Description
 * This app demonstrates the configuration and control
 * of the LED Driver 9 click board resulting in a nice
 * breathing effect.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization configures the UART LOG and I2C
 * drivers and adjusts the Led Driver 9 click general
 * register settings.
 *
 * ## Application Task
 * The application task is a simple breathing effect on
 * all LED out channels.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver9.h"

static leddriver9_t leddriver9;
static log_t logger;

static leddriver9_mode_reg_t dev_reg = { 0 };
static leddriver9_output_state_t output_state = { 0 };

static float max_duty = 20;
static float min_duty = 0;
static float duty_gradient = 0.1;
const uint8_t breathing_speed = 5;

void mode1_register_settings ( void );
void mode2_register_settings ( void );
void led_output_state ( void );

void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    leddriver9_cfg_t leddriver9_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    leddriver9_cfg_setup( &leddriver9_cfg );
    LEDDRIVER9_MAP_MIKROBUS( leddriver9_cfg, MIKROBUS_1 );
    err_t init_flag = leddriver9_init( &leddriver9, &leddriver9_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    leddriver9_default_cfg( &leddriver9 );
    log_info( &logger, " Application Task " );
    
    mode1_register_settings( );
    mode2_register_settings( );
    Delay_ms( 100 );
    
    led_output_state( );
    Delay_ms( 100 );
}

void application_task ( void ) {
    float duty_cnt = min_duty;
    
    while ( duty_cnt <= max_duty ) {
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL0, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL1, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL2, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL3, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL4, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL5, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL6, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL7, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL8, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL9, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL10, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL11, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL12, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL13, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL14, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL15, duty_cnt );
        duty_cnt += duty_gradient;
        Delay_ms( breathing_speed );
    }
    while ( duty_cnt > min_duty ) {
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL0, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL1, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL2, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL3, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL4, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL5, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL6, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL7, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL8, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL9, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL10, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL11, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL12, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL13, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL14, duty_cnt );
        leddriver9_set_pwm( &leddriver9, LEDDRIVER9_CHANNEL15, duty_cnt );
        duty_cnt -= duty_gradient;
        Delay_ms( breathing_speed );
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

void mode1_register_settings ( void ) {
    dev_reg.mode_1.ALLCALL = 0;
    dev_reg.mode_1.SUB3 = 0;
    dev_reg.mode_1.SUB2 = 0;
    dev_reg.mode_1.SUB1 = 0;
    dev_reg.mode_1.OSC = 0;
    leddriver9_mode1_reg_write( &leddriver9, &dev_reg );
}

void mode2_register_settings ( void ) {
    dev_reg.mode_2.OCH = 0;
    dev_reg.mode_2.DMBLNK = 0;
    dev_reg.mode_2.EFCLR = 0;
    leddriver9_mode2_reg_write( &leddriver9, &dev_reg );
}

void led_output_state ( void ) {
    output_state.LEDOUT0.LDR0 = LEDDRIVER9_GROUP;
    output_state.LEDOUT0.LDR1 = LEDDRIVER9_GROUP;
    output_state.LEDOUT0.LDR2 = LEDDRIVER9_GROUP;
    output_state.LEDOUT0.LDR3 = LEDDRIVER9_GROUP;
    output_state.LEDOUT1.LDR4 = LEDDRIVER9_GROUP;
    output_state.LEDOUT1.LDR5 = LEDDRIVER9_GROUP;
    output_state.LEDOUT1.LDR6 = LEDDRIVER9_GROUP;
    output_state.LEDOUT1.LDR7 = LEDDRIVER9_GROUP;
    output_state.LEDOUT2.LDR8 = LEDDRIVER9_GROUP;
    output_state.LEDOUT2.LDR9 = LEDDRIVER9_GROUP;
    output_state.LEDOUT2.LDR10 = LEDDRIVER9_GROUP;
    output_state.LEDOUT2.LDR11 = LEDDRIVER9_GROUP;
    output_state.LEDOUT3.LDR12 = LEDDRIVER9_GROUP;
    output_state.LEDOUT3.LDR13 = LEDDRIVER9_GROUP;
    output_state.LEDOUT3.LDR14 = LEDDRIVER9_GROUP;
    output_state.LEDOUT3.LDR15 = LEDDRIVER9_GROUP;
    leddriver9_ledout_state( &leddriver9, &output_state );
}

// ------------------------------------------------------------------------ END
