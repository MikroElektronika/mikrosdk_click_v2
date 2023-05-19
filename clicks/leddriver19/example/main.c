/*!
 * @file main.c
 * @brief LED Driver 19 Click example
 *
 * # Description
 * This library contains API for LED Driver 19 Click driver. 
 * The library initializes and defines the I2C bus drivers to 
 * write the default configuration for a PWM output value 
 * of the out pins.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs default configuration, sets the device
 * in output enabled mode and checks communication by reading device ID.
 *
 * ## Application Task
 * This example demonstrates the use of the LED Driver 19 Click board by 
 * changing PWM values of all channels from maximum to minimum turning 
 * LEDs on and off in the process.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "leddriver19.h"

static leddriver19_t leddriver19;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    leddriver19_cfg_t leddriver19_cfg;  /**< Click config object. */

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
    leddriver19_cfg_setup( &leddriver19_cfg );
    LEDDRIVER19_MAP_MIKROBUS( leddriver19_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == leddriver19_init( &leddriver19, &leddriver19_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint8_t device_id;
    
    leddriver19_read_reg( &leddriver19, LEDDRIVER19_REG_DEVICE_ID, &device_id );
    if ( LEDDRIVER19_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( LEDDRIVER19_ERROR == leddriver19_default_cfg ( &leddriver19 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( &leddriver19, LEDDRIVER19_PATSEL_0, n_cnt, 100  );
        Delay_ms( 100 );
    }
    Delay_ms( 1000 );
    
    for ( uint8_t n_cnt = LEDDRIVER19_CH_SEL_0; n_cnt <= LEDDRIVER19_CH_SEL_11; n_cnt++ )
    {
        leddriver19_set_pattern_pwm( &leddriver19, LEDDRIVER19_PATSEL_0, n_cnt, 0  );
        Delay_ms( 100 );
    }
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
