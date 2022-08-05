/*!
 * @file main.c
 * @brief Angle7 Click example
 *
 * # Description
 * This example demonstrates the use of Angle 7 click board by reading and displaying
 * the magnet's angular position in degrees and analog voltage output as well as
 * the magnet's status and magnitude.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the magnet's angular position in degrees and analog voltage output 
 * as well as the magnet's status and magnitude and displays the results on the USB UART
 * approximately every 100ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "angle7.h"

static angle7_t angle7;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    angle7_cfg_t angle7_cfg;  /**< Click config object. */

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
    angle7_cfg_setup( &angle7_cfg );
    ANGLE7_MAP_MIKROBUS( angle7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == angle7_init( &angle7, &angle7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANGLE7_ERROR == angle7_default_cfg ( &angle7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage, raw_angle, angle;
    uint16_t magnitude;
    uint8_t status;
    if ( ADC_ERROR != angle7_read_an_pin_voltage ( &angle7, &voltage ) ) 
    {
        log_printf( &logger, " AN voltage: %.3f V\r\n", voltage );
    }
    if ( ANGLE7_OK == angle7_get_angle ( &angle7, &angle ) )
    {
        log_printf ( &logger, " Angle: %.2f Degrees\r\n", angle );
    }
    if ( ANGLE7_OK == angle7_get_magnitude ( &angle7, &magnitude ) )
    {
        log_printf ( &logger, " Magnitude: %u\r\n", magnitude );
    }
    if ( ANGLE7_OK == angle7_get_status ( &angle7, &status ) )
    {
        log_printf ( &logger, " Status:" );
        if ( status & ANGLE7_STATUS_MAGNET_DETECTED )
        {
            log_printf ( &logger, " Magnet Detected \r\n Magnet Strength:" );
            if ( status & ANGLE7_STATUS_MAGNET_TOO_STRONG )
            {
                log_printf ( &logger, " Too Strong \r\n\n" );
            }
            else if ( status & ANGLE7_STATUS_MAGNET_TOO_WEAK )
            {
                log_printf ( &logger, " Too Weak \r\n\n" );
            }
            else
            {
                log_printf ( &logger, " Good \r\n\n" );
            }
        }
        else
        {
            log_printf ( &logger, " Magnet Not Detected \r\n\n" );
        }
    }
    Delay_ms ( 100 );
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
