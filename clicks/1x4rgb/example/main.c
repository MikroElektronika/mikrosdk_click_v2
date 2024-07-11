/*!
 * @file main.c
 * @brief 1x4 RGB Click example
 *
 * # Description
 * This example demonstrates the use of the 1x4 RGB Click board
 * by controlling the color of the LEDs [LD1-LD4].
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo example shows the color change of four RGB LEDs, 
 * starting with red color, through green and blue, and ending with white.
 * These LEDs actually consist of three single-colored LEDs 
 * (Red-Green-Blue) in a single package. 
 * Various colors can be reproduced by mixing the intensity of each LED.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c1x4rgb.h"

static c1x4rgb_t c1x4rgb;
static log_t logger;

// Demo RGB color intensity
#define DEMO_COLOR_INT_0        0
#define DEMO_COLOR_INT_100      100 

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1x4rgb_cfg_t c1x4rgb_cfg;  /**< Click config object. */

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
    c1x4rgb_cfg_setup( &c1x4rgb_cfg );
    C1X4RGB_MAP_MIKROBUS( c1x4rgb_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c1x4rgb_init( &c1x4rgb, &c1x4rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1X4RGB_ERROR == c1x4rgb_default_cfg ( &c1x4rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}

void application_task ( void ) 
{
    log_printf( &logger, "\r\n\n RED: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_0 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n GREEN: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_0 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n BLUE: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_100 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n WHITE:" );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_100 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
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
