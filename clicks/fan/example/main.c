/*!
 * \file main.c
 * \brief Fan Click Example
 *
 * # Description
 * This application is controller for powering and regulating of fan.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of click driver and usb uart serial terminal for results
 * logging.
 *
 * ## Application Task
 * Performs a control of the fan and reads rotation per minute (RPM).
 * Results will be sent to the usb uart terminal.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fan.h"


#define FAN_DUTY_RATIO_0_PER    0       /**< PWM duty ratio 0 pecrents - zero scale. >*/
#define FAN_DUTY_RATIO_10_PER   10      /**< PWM duty ratio 10 percents - step. >*/
#define FAN_DUTY_RATIO_100_PER  100     /**< PWM duty ratio 100 percents - full scale. >*/

#define FAN_PWM_BASE_FREQ_ZERO_SCALE  0x00  /**< PWM base frequency zero scale. >*/
#define FAN_PWM_BASE_FREQ_HALF_SCALE  0x80  /**< PWM base frequency half scale. >*/
#define FAN_PWM_BASE_FREQ_FULL_SCALE  0xFF  /**< PWM base frequency full scale. >*/

// ------------------------------------------------------------------ VARIABLES

static fan_t fan;       /**< Fan click object. >*/
static log_t logger;    /**< Logger object. >*/

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fan_cfg_t fan_cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    fan_cfg_setup( &fan_cfg );
    FAN_MAP_MIKROBUS( fan_cfg, MIKROBUS_1 );
    if ( fan_init( &fan, &fan_cfg ) == I2C_MASTER_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----" );
    fan_default_cfg( &fan );
    fan_pwm_base( &fan, FAN_PWM_BASE_FREQ_HALF_SCALE );
    log_info( &logger, "---- Application Program Running... ----\n" );
}

void application_task ( void )
{
    for ( uint8_t duty = FAN_DUTY_RATIO_0_PER; duty <= FAN_DUTY_RATIO_100_PER;
          duty += FAN_DUTY_RATIO_10_PER )
    {
        fan_setting( &fan, duty );
        log_printf( &logger, " Duty Ratio : %u%%\r\n", (uint16_t)duty );
        Delay_ms( 2000 );

        uint16_t tacho = 0;

        fan_get_tach( &fan, &tacho );
        log_printf( &logger, " Rotation per minute : %urpm\r\n\n", tacho );
        Delay_ms( 2000 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
