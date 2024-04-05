/*!
 * @file main.c
 * @brief Driver2 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Driver 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver module and sets PWM.
 *
 * ## Application Task
 * Start motor example with change in motor speed using changes in PWM duty cycle.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "driver2.h"

static driver2_t driver2;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    driver2_cfg_t driver2_cfg;  /**< Click config object. */

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

    driver2_cfg_setup( &driver2_cfg );
    DRIVER2_MAP_MIKROBUS( driver2_cfg, MIKROBUS_1 );
    err_t init_flag  = driver2_init( &driver2, &driver2_cfg );
    if ( PWM_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    driver2_default_cfg ( &driver2 );

    driver2_set_duty_cycle ( &driver2, 0.0 );
    driver2_pwm_start( &driver2 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    driver2_set_duty_cycle ( &driver2, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) {
        duty_inc = -1;
    } else if ( 0 == duty_cnt ) {
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
