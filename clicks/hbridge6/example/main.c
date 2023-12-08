/*!
 * @file main.c
 * @brief HBridge6 Click example
 *
 * # Description
 * This is an example that demonstrates the use of H-Bridge 6 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C,
 * reset the device and set default configuration,
 * initialization and configure the PWM, also write log.
 *
 * ## Application Task
 * It shows moving in the clockwise direction of rotation
 * and moving in the counterclockwise direction of rotation
 * from slow to fast speed.
 * All data logs write on USB uart changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hbridge6.h"

static hbridge6_t hbridge6;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    hbridge6_cfg_t hbridge6_cfg;  /**< Click config object. */

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
    hbridge6_cfg_setup( &hbridge6_cfg );
    HBRIDGE6_MAP_MIKROBUS( hbridge6_cfg, MIKROBUS_1 );
    err_t init_flag = hbridge6_init( &hbridge6, &hbridge6_cfg );
    if ( I2C_MASTER_ERROR == init_flag || PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Set default config.  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_default_cfg( &hbridge6 );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = 0;

    log_printf( &logger, "       Clockwise       \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_CLOCKWISE );

    while ( duty_cnt < 10 ) {
        duty = duty_cnt / 10.0;
        hbridge6_set_duty_cycle ( &hbridge6, duty );
        Delay_ms( 500 );
        duty_cnt += duty_inc;
    }

    log_printf( &logger, "         Brake         \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_BRAKE );
    duty_cnt = 1;
    Delay_ms( 1000 );

    log_printf( &logger, "    Counterclockwise   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_COUNTERCLOCKWISE );

    while ( duty_cnt < 10 ) {
        duty = duty_cnt / 10.0;
        hbridge6_set_duty_cycle ( &hbridge6, duty );
        Delay_ms( 500 );
        duty_cnt += duty_inc;
    }

    log_printf( &logger, "         Brake         \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    hbridge6_set_direction( &hbridge6, HBRIDGE6_DIRECTION_BRAKE );
    duty_cnt = 1;

    Delay_ms( 3000 );
    hbridge6_pwm_stop( &hbridge6 );
    Delay_ms( 2000 );
    hbridge6_pwm_start( &hbridge6 );
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
