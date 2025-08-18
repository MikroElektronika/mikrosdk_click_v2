/*!
 * @file main.c
 * @brief Haptic 5 Click example
 *
 * # Description
 * This example demonstrates the control of the Haptic 5 Click board.
 * In I2C mode, the example toggles the haptic trigger pin periodically to generate vibration pulses.
 * In PWM mode, it gradually increases and decreases the output duty cycle to modulate the vibration intensity,
 * while toggling the direction when the duty reaches 0%.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board driver, and applies the default configuration.
 *
 * ## Application Task
 * Depending on the selected communication interface (I2C or PWM), toggles the haptic trigger (I2C),
 * or changes PWM duty cycle and direction (PWM).
 *
 * @note
 * The mode is selected via the @b HAPTIC5_DEFAULT_COM macro. Ensure proper configuration and wiring 
 * based on the selected mode before running the example.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "haptic5.h"

static haptic5_t haptic5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    haptic5_cfg_t haptic5_cfg;  /**< Click config object. */

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
    haptic5_cfg_setup( &haptic5_cfg );
    HAPTIC5_MAP_MIKROBUS( haptic5_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == haptic5_init( &haptic5, &haptic5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HAPTIC5_ERROR == haptic5_default_cfg ( &haptic5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( HAPTIC5_DEFAULT_COM == HAPTIC5_COM_I2C )
    log_printf( &logger, " Haptic state: Active\r\n\n" );
    haptic5_set_trg_high ( &haptic5 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Haptic state: Idle\r\n\n" );
    haptic5_set_trg_low ( &haptic5 );
    Delay_ms ( 1000 );
#else
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;
    
    haptic5_set_duty_cycle ( &haptic5, duty );
    log_printf( &logger, "> Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    
    Delay_ms ( 500 );
    
    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        duty_inc = 1;
        haptic5_toggle_dir ( &haptic5 );
    }
    duty_cnt += duty_inc;
#endif
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
