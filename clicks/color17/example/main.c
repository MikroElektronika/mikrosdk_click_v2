/*!
 * @file main.c
 * @brief Color 17 Click example
 *
 * # Description
 * This library contains API for the Color 17 Click driver.
 * This example displays CCT data, Light intensity level
 * and the light color names.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the Color 17 Click board™.
 * Reads and displays the correlated color temperature 
 * and Light intensity level.
 * This example also detects and displays the light color names.
 * Results are being sent to the UART Terminal, where you can track their changes.
 * 
 * @note
 * Color detection is obtained based on the analysis 
 * of calculate the correlated color temperature (CCT) data
 * and the CIE 1931 chromaticity diagram. For more details please refer to the 
 * “OPT4048 High Speed High Precision Tristimulus XYZ Color Sensor datasheet” 
 * (https://www.ti.com/lit/gpn/OPT4048).
 
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color17.h"

#define COLOR17_LIM_DARK_LUX                10.0
#define COLOR17_CCT_LIM_BLUE_COLOR          7000
#define COLOR17_CCT_LIM_LIGHT_BLUE_COLOR    4000
#define COLOR17_CCT_LIM_GREEN_COLOR         3100
#define COLOR17_CCT_LIM_YELLOW_COLOR        2400
#define COLOR17_CCT_LIM_ORANGE_COLOR        1950
#define COLOR17_CCT_LIM_RED_COLOR           1600

static color17_t color17;
static log_t logger;
static float light_intensity, cct;

/**
 * @brief Color 17 display color function.
 * @details This function displays the light color names.
 * @return Nothing.
 * @note None.
 */
void color17_display_color ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color17_cfg_t color17_cfg;  /**< Click config object. */

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
    color17_cfg_setup( &color17_cfg );
    COLOR17_MAP_MIKROBUS( color17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color17_init( &color17, &color17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR17_ERROR == color17_default_cfg ( &color17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    if ( COLOR17_OK == color17_get_cct( &color17, &cct, &light_intensity ) )
    {
        log_printf( &logger, " CCT: %.2f\r\n", cct );
        log_printf( &logger, " LIL: %.2f\r\n", light_intensity );
        log_printf( &logger, " - - - - - - -  - - - - \r\n" );
        color17_display_color( );
    }
    log_printf( &logger, " ----------------------\r\n" );
    Delay_ms( 1000 );
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

void color17_display_color ( void )
{
    if ( light_intensity < COLOR17_LIM_DARK_LUX )
    {
        log_printf( &logger, " Color DARK\r\n", cct );
    }
    else if ( cct > COLOR17_CCT_LIM_BLUE_COLOR  )
    {
        log_printf( &logger, " Color BLUE\r\n", cct );
    }
    else if ( cct > COLOR17_CCT_LIM_LIGHT_BLUE_COLOR  )
    {
        log_printf( &logger, " Color LIGHT BLUE\r\n", cct );
    }
    else if ( cct > COLOR17_CCT_LIM_GREEN_COLOR )
    {
        log_printf( &logger, " Color GREEN\r\n", cct );
    }
    else if ( cct > COLOR17_CCT_LIM_YELLOW_COLOR )
    {
        log_printf( &logger, " Color YELLOW\r\n", cct );
    }
    else if ( cct > COLOR17_CCT_LIM_ORANGE_COLOR )
    {
        log_printf( &logger, " Color ORANGE\r\n", cct );
    }
    else if ( cct > COLOR17_CCT_LIM_RED_COLOR )
    {
        log_printf( &logger, " Color RED\r\n", cct );
    }
    else
    {
        log_printf( &logger, " Color BLUE\r\n", cct );
    }
}

// ------------------------------------------------------------------------ END
