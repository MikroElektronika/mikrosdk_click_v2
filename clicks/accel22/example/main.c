/*!
 * @file main.c
 * @brief Accel22 Click example
 *
 * # Description
 * This example demonstrates the use of Accel 22 click board by reading and displaying 
 * Accel data (X, Y, and Z axis) as well as temperature and ADC measurements on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays the Accel data (X, Y, and Z axis) as well as temperature and ADC measurements 
 * on the USB UART every 100ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel22.h"

static accel22_t accel22;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel22_cfg_t accel22_cfg;  /**< Click config object. */

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
    accel22_cfg_setup( &accel22_cfg );
    ACCEL22_MAP_MIKROBUS( accel22_cfg, MIKROBUS_1 );
    err_t init_flag  = accel22_init( &accel22, &accel22_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL22_ERROR == accel22_default_cfg ( &accel22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    accel22_axes_t axes;
    // Wait for data ready indication
    while ( !accel22_get_int1_pin ( &accel22 ) );
    if ( ACCEL22_OK == accel22_get_axes ( &accel22, &axes ) )
    {
        log_printf( &logger, " X: %.2f mg\r\n", axes.x );
        log_printf( &logger, " Y: %.2f mg\r\n", axes.y );
        log_printf( &logger, " Z: %.2f mg\r\n", axes.z );
    }
    
    if ( ACCEL22_OK == accel22_enable_temperature_measurement ( &accel22 ) )
    {
        float temperature = 0;
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( &accel22 ) );
        if ( ACCEL22_OK == accel22_get_temperature ( &accel22, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
        }
    }
    
    if ( ACCEL22_OK == accel22_enable_adc_measurement ( &accel22 ) )
    {
        float adc_voltage = 0;
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( &accel22 ) );
        if ( ACCEL22_OK == accel22_get_adc ( &accel22, &adc_voltage ) )
        {
            log_printf( &logger, " ADC: %.2f V\r\n\n", adc_voltage );
        }
    }
    Delay_ms ( 100 );
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
