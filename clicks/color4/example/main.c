/*!
 * @file main.c
 * @brief Color 4 Click example
 *
 * # Description
 * This library contains API for the Color 4 Click driver.
 * This driver provides the functions for the sensor configuration
 * and for reading RGBW and ambient light data from the device.
 * This example displays RGBW data, Ambient light level, CCT data 
 * and the light color names.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the Color 4 Click board™.
 * Reads and displays the results of the RGBW, Ambient light level, 
 * calculate the correlated color temperature. 
 * This example also detects and displays the light color names.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @note
 * Color detection is obtained based on the analysis 
 * of calculate the correlated color temperature (CCT) data
 * and the CIE 1931 chromaticity diagram.
 * For more details please refer to the “Designing the VEML6040 into an Application” 
 * application note (www.vishay.com/doc?84331).
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color4.h"

#define COLOR4_LIM_WHITE_COLOR        17000
#define COLOR4_LIM_DARK_LUX           15.0
#define COLOR4_CCT_LIM_BLUE_COLOR     9000
#define COLOR4_CCT_LIM_PURPLE_COLOR   7500
#define COLOR4_CCT_LIM_GREEN_COLOR    6000
#define COLOR4_CCT_LIM_YELLOW_COLOR   3500
#define COLOR4_CCT_LIM_ORANGE_COLOR   2200
#define COLOR4_CCT_LIM_PINK_COLOR     1900
#define COLOR4_CCT_LIM_RED_COLOR      700

static color4_t color4;
static log_t logger;
static uint16_t red_data, green_data, blue_data, white_data;
static float ambient_light, cct;

void display_color ( void )
{
    if ( ambient_light < COLOR4_LIM_DARK_LUX )
    {
        log_printf( &logger, " Color DARK\r\n", cct );
    }
    else if ( white_data > COLOR4_LIM_WHITE_COLOR )
    {
        log_printf( &logger, " Color WHITE\r\n", cct );   
    }
    else if ( cct > COLOR4_CCT_LIM_BLUE_COLOR  )
    {
        log_printf( &logger, " Color BLUE\r\n", cct );
    }
    else if ( cct > COLOR4_CCT_LIM_PURPLE_COLOR )
    {
        log_printf( &logger, " Color PURPLE\r\n", cct );
    }
    else if ( cct > COLOR4_CCT_LIM_GREEN_COLOR )
    {
        log_printf( &logger, " Color GREEN\r\n", cct );
    }
    else if ( cct > COLOR4_CCT_LIM_YELLOW_COLOR )
    {
        log_printf( &logger, " Color YELLOW\r\n", cct );
    }
    else if ( cct > COLOR4_CCT_LIM_ORANGE_COLOR )
    {
        log_printf( &logger, " Color ORANGE\r\n", cct );
    }
    else if ( cct > COLOR4_CCT_LIM_PINK_COLOR )
    {
        log_printf( &logger, " Color PINK\r\n", cct );
    }
    else if ( cct > COLOR4_CCT_LIM_RED_COLOR )
    {
        log_printf( &logger, " Color RED\r\n", cct );
    }
    else
    {
        log_printf( &logger, " Color BLUE\r\n", cct );
    }
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color4_cfg_t color4_cfg;  /**< Click config object. */

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
    color4_cfg_setup( &color4_cfg );
    COLOR4_MAP_MIKROBUS( color4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color4_init( &color4, &color4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( COLOR4_ERROR == color4_default_cfg ( &color4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_RED, &red_data ) )
    {
        log_printf( &logger, " Red: %u\r\n", red_data );
    }

    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_GREEN, &green_data ) )
    {
        log_printf( &logger, " Green: %u\r\n", green_data );
    }

    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_BLUE, &blue_data ) )
    {
        log_printf( &logger, " Blue: %u\r\n", blue_data );
    }

    if ( COLOR4_OK == color4_get_color_data( &color4, COLOR4_WHITE, &white_data ) )
    {
        log_printf( &logger, " White: %u\r\n", white_data );
    }
    log_printf( &logger, " - - - - - - -  - - - - \r\n" );

    if ( COLOR4_OK == color4_get_ambient_light( &color4, &ambient_light ) )
    {
        log_printf( &logger, " ALS lux level: %.2f\r\n", ambient_light );
    }

    if ( COLOR4_OK == color4_get_cct( &color4, &cct ) )
    {
        log_printf( &logger, " CCT: %.2f\r\n", cct );
    }
    log_printf( &logger, " - - - - - - -  - - - - \r\n" );

    display_color( );
    log_printf( &logger, " ----------------------\r\n" );
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
