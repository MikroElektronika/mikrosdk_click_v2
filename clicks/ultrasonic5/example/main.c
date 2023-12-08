/*!
 * @file main.c
 * @brief Ultrasonic 5 Click example
 *
 * # Description
 * This example demonstrates the use of Ultrasonic 5 click board by reading
 * the measurements from the connected ultrasonic sensor and displaying it
 * on a Serial Plot.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Performs a burst generation which starts the measurement and then reads the next
 * 200 ADC samples and displays the results on the USB UART (SerialPlot).
 * 
 * @note
 * In order to get valid measuremets a proper ultrasonic sensor must be connected to OUTA and OUTB.
 * We have used an UTR-1440K-TT-R sensor for the test. We recommend using the SerialPlot tool
 * for data visualizing. Refer to the datasheet "Application Curves" section in order to check
 * and compare the results from the plotter.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ultrasonic5.h"

static ultrasonic5_t ultrasonic5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic5_cfg_t ultrasonic5_cfg;  /**< Click config object. */

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
    ultrasonic5_cfg_setup( &ultrasonic5_cfg );
    ULTRASONIC5_MAP_MIKROBUS( ultrasonic5_cfg, MIKROBUS_1 );
    if ( ULTRASONIC5_OK != ultrasonic5_init( &ultrasonic5, &ultrasonic5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ULTRASONIC5_OK != ultrasonic5_default_cfg ( &ultrasonic5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    // Burst generation / Start measurement
    ultrasonic5_set_duty_cycle ( &ultrasonic5, ULTRASONIC5_DEF_DYTY );
    ultrasonic5_pwm_start( &ultrasonic5 );
    ultrasonic5_clear_io1_pin ( &ultrasonic5 );
    Delay_500us ( );
    ultrasonic5_set_io1_pin ( &ultrasonic5 );
    ultrasonic5_pwm_stop( &ultrasonic5 );
    // Read and log the next 200 ADC samples which we will plot on a Serial Plotter
    for ( uint16_t cnt = 0; cnt < 200; cnt++ )
    {
        if ( ULTRASONIC5_OK == ultrasonic5_read_an_pin_voltage ( &ultrasonic5, &voltage ) ) 
        {
            log_printf( &logger, "%.3f\r\n", voltage );
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
