/*!
 * @file main.c
 * @brief Brushless 18 Click example
 *
 * # Description
 * This example demonstrates the use of the Brushless 18 Click board by driving the 
 * motor in both directions at different speeds.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and calibrates the Click board.
 *
 * ## Application Task
 * Changes the motor speed every 500 milliseconds with steps of 5%.
 * At the minimal speed, the motor switches direction. Each step will be logged
 * on the USB UART where you can track the program flow.
 *
 * @note
 * The theoretical maximal PWM Clock frequency for this Click board is 500 Hz.
 * The default PWM Clock frequency is set to 400 Hz. To achieve such a low frequency,
 * the user will probably need to decrease the MCU's main clock frequency in 
 * the Setup MCU Settings.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless18.h"

static brushless18_t brushless18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless18_cfg_t brushless18_cfg;  /**< Click config object. */

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
    brushless18_cfg_setup( &brushless18_cfg );
    BRUSHLESS18_MAP_MIKROBUS( brushless18_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == brushless18_init( &brushless18, &brushless18_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS18_ERROR == brushless18_throttle_calib ( &brushless18 ) )
    {
        log_error( &logger, " Throttle calibration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t direction = BRUSHLESS18_DIRECTION_CW;
    static int8_t speed = BRUSHLESS18_SPEED_MIN;
    static int8_t speed_step = 5;
    brushless18_drive_motor ( &brushless18, direction, speed );
    log_printf( &logger, " Direction: %s\r\n", 
                ( char * ) ( BRUSHLESS18_DIRECTION_CW == direction ? "CW" : "CCW" ) );
    log_printf( &logger, " Speed: %u%%\r\n\n", ( uint16_t ) speed );
    Delay_ms ( 500 );
    
    speed += speed_step;
    if ( speed > BRUSHLESS18_SPEED_MAX )
    {
        speed_step = -speed_step;
        speed += speed_step;
        speed += speed_step;
    }
    else if ( speed < BRUSHLESS18_SPEED_MIN )
    {
        speed_step = -speed_step;
        speed += speed_step;
        direction ^= 1;
        Delay_ms ( 1000 );
    }
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
