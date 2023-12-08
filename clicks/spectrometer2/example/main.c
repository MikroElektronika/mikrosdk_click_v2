/*!
 * @file main.c
 * @brief Spectrometer2 Click example
 *
 * # Description
 * This example demonstrates the use of Spectrometer 2 click board by reading data
 * from 6 ALS channels and converting them to HSL color and displaying those data as 
 * well as the detected color name on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the values of all ALS channels and converts
 * them to HSL color and displays those data as well as the detected color name on the USB UART
 * every 200ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spectrometer2.h"

static spectrometer2_t spectrometer2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spectrometer2_cfg_t spectrometer2_cfg;  /**< Click config object. */

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
    spectrometer2_cfg_setup( &spectrometer2_cfg );
    SPECTROMETER2_MAP_MIKROBUS( spectrometer2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == spectrometer2_init( &spectrometer2, &spectrometer2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SPECTROMETER2_ERROR == spectrometer2_default_cfg ( &spectrometer2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Wait for the data ready interrupt indication
    while ( !spectrometer2_get_int_pin ( &spectrometer2 ) );
    
    spectrometer2_als_channels_t als_channels;
    if ( ( SPECTROMETER2_OK == spectrometer2_clear_interrupt ( &spectrometer2 ) ) &&
         ( SPECTROMETER2_OK == spectrometer2_get_data ( &spectrometer2, &als_channels ) ) )
    {
        spectrometer2_hsl_t hsl;
        spectrometer2_rgbc_to_hsl( &als_channels, &hsl );
        log_printf ( &logger, "\r\n Hue: %.1f deg\r\n", hsl.hue );
        log_printf ( &logger, " Saturation: %.1f %%\r\n", hsl.saturation );
        log_printf ( &logger, " Lightness: %.1f %%\r\n", hsl.lightness );
        switch ( spectrometer2_get_color ( &hsl ) )
        {
            case SPECTROMETER2_RED_COLOR:
            {
                log_printf( &logger, " Color: RED\r\n" );
                break;
            }
            case SPECTROMETER2_YELLOW_COLOR:
            {
                log_printf( &logger, " Color: YELLOW\r\n" );
                break;
            }
            case SPECTROMETER2_GREEN_COLOR:
            {
                log_printf( &logger, " Color: GREEN\r\n" );
                break;
            }
            case SPECTROMETER2_CYAN_COLOR:
            {
                log_printf( &logger, " Color: CYAN\r\n" );
                break;
            }
            case SPECTROMETER2_BLUE_COLOR:
            {
                log_printf( &logger, " Color: BLUE\r\n" );
                break;
            }
            case SPECTROMETER2_MAGENTA_COLOR:
            {
                log_printf( &logger, " Color: MAGENTA\r\n" );
                break;
            }
            case SPECTROMETER2_WHITE_COLOR:
            {
                log_printf( &logger, " Color: WHITE\r\n" );
                break;
            }
            case SPECTROMETER2_BLACK_COLOR:
            {
                log_printf( &logger, " Color: BLACK\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, " Color: UNKNOWN\r\n" );
                break;
            }
        }
    }
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

// ------------------------------------------------------------------------ END
