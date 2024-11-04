/*!
 * @file main.c
 * @brief Brushless 11 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 11 Click board by driving the 
 * motor at different speeds.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Controls the motor speed by changing the PWM duty cycle every second.
 * The duty cycle ranges from 10% to 100%.
 * Each step will be logged on the USB UART where you can track the program flow.
 *
 * @author Stefan Ilic
 */

#include "board.h"
#include "log.h"
#include "brushless11.h"

static brushless11_t brushless11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless11_cfg_t brushless11_cfg;  /**< Click config object. */

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
    brushless11_cfg_setup( &brushless11_cfg );
    BRUSHLESS11_MAP_MIKROBUS( brushless11_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless11_init( &brushless11, &brushless11_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS11_ERROR == brushless11_default_cfg ( &brushless11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Motor brake is off \r\n" );
    brushless11_set_brake( &brushless11, BRUSHLESS11_BRAKE_OFF );
    for ( uint8_t speed_cnt = 10; speed_cnt <= 100; speed_cnt += 10 )
    {
        brushless11_set_speed( &brushless11, speed_cnt );
        log_printf( &logger, " Speed is: %d%% \r\n", ( uint16_t ) speed_cnt );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Motor brake is on \r\n" );
    brushless11_set_brake( &brushless11, BRUSHLESS11_BRAKE_ON );
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
