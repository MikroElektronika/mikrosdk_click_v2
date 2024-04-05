/*!
 * @file main.c
 * @brief 2x2 RGB Click example
 *
 * # Description
 * This example demonstrates the use of the 2x2 RGB Click board™ 
 * by controlling the color of the LEDs [1-4].
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * This simple example shows all LEDs in different colors.
 * These LEDs actually consist of three single-colored LEDs (Red, Green and Blue) in a single package. 
 * Various colors can be reproduced by mixing the intensity of each LED.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "c2x2rgb.h"

#define DEMO_LED_CURRENT    600

static c2x2rgb_t c2x2rgb;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c2x2rgb_cfg_t c2x2rgb_cfg;  /**< Click config object. */

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
    c2x2rgb_cfg_setup( &c2x2rgb_cfg );
    C2X2RGB_MAP_MIKROBUS( c2x2rgb_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c2x2rgb_init( &c2x2rgb, &c2x2rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C2X2RGB_ERROR == c2x2rgb_default_cfg ( &c2x2rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    log_printf( &logger, "\r\nRED: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, DEMO_LED_CURRENT,
                                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                                   C2X2RGB_LED_CURRENT_OFF ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nGREEN: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, C2X2RGB_LED_CURRENT_OFF, 
                                                                   DEMO_LED_CURRENT, 
                                                                   C2X2RGB_LED_CURRENT_OFF ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nBLUE: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, C2X2RGB_LED_CURRENT_OFF, 
                                                                   C2X2RGB_LED_CURRENT_OFF, 
                                                                   DEMO_LED_CURRENT ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    
    log_printf( &logger, "\r\nWHITE: " );
    for ( uint8_t led_pos = C2X2RGB_SET_LD1; led_pos <= C2X2RGB_SET_LD4; led_pos++ )
    {
        if ( C2X2RGB_OK == c2x2rgb_set_rgb_led( &c2x2rgb, led_pos, DEMO_LED_CURRENT, 
                                                                   DEMO_LED_CURRENT, 
                                                                   DEMO_LED_CURRENT ) )
        {
            log_printf( &logger, "LD%d ", ( uint16_t ) led_pos );
        }
        Delay_ms ( 200 );
    }
    log_printf( &logger, "\r\n----------------" );
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
