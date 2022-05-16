/*!
 * @file main.c
 * @brief Inclinometer2 Click example
 *
 * # Description
 * This example demonstrates the use of Inclinometer 2 click board by reading and displaying 
 * the Accel X and Y axis data (mg) and the temperature (degC) on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration which enables the accel
 * data ready interrupt, sets output data rate to 12.5 Hz and accel full-scale range to +-2g.
 *
 * ## Application Task
 * Waits for the data ready interrupt, then reads the values of accel X and Y axis as well as
 * the absolute temperature and displays the results on the USB UART. The data sample rate is 
 * set to 12.5Hz by default, therefore the data is being read approximately every 80ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "inclinometer2.h"

static inclinometer2_t inclinometer2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer2_cfg_t inclinometer2_cfg;  /**< Click config object. */

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
    inclinometer2_cfg_setup( &inclinometer2_cfg );
    INCLINOMETER2_MAP_MIKROBUS( inclinometer2_cfg, MIKROBUS_1 );
    err_t init_flag  = inclinometer2_init( &inclinometer2, &inclinometer2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER2_ERROR == inclinometer2_default_cfg ( &inclinometer2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    // Wait for accel data ready indication
    while ( !inclinometer2_get_int_pin ( &inclinometer2 ) );
    
    float x_axis, y_axis;
    if ( INCLINOMETER2_OK == inclinometer2_get_accel ( &inclinometer2, &x_axis, &y_axis ) )
    {
        log_printf( &logger, " X: %.2f mg\r\n", x_axis );
        log_printf( &logger, " Y: %.2f mg\r\n", y_axis );
    }
    float temperature;
    if ( INCLINOMETER2_OK == inclinometer2_get_temperature ( &inclinometer2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
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
