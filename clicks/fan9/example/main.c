/*!
 * @file main.c
 * @brief Fan 9 Click example
 *
 * # Description
 * This example demonstrates the use of FAN 9 click board, 
 * by changing speed of the fan from 0 to 100 percent, then decreasing it back to 0.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Changes the speed of fans by changing the PWM duty cycle.
 * The results are being displayed via USB UART where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "fan9.h"

static fan9_t fan9;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    fan9_cfg_t fan9_cfg;  /**< Click config object. */

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
    fan9_cfg_setup( &fan9_cfg );
    FAN9_MAP_MIKROBUS( fan9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == fan9_init( &fan9, &fan9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( FAN9_ERROR == fan9_default_cfg ( &fan9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    fan9_set_pwm( &fan9, 10 );
    // Waiting for motor to start.
    while ( 0 == fan9_get_rd_pin( &fan9 ) );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static int8_t duty_cnt = 10;
    static int8_t duty_inc = 10;
    uint8_t direction = FAN9_DIRECTION_CW;

    fan9_set_pwm( &fan9, duty_cnt );
    log_printf( &logger, " Set PWM: %d%% \r\n", ( uint16_t ) duty_cnt );
    
    if ( 100 == duty_cnt ) 
    {
        duty_inc = -10;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 10;
    }
    duty_cnt += duty_inc;
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
