/*!
 * @file main.c
 * @brief ECG 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of ECG 7 click board by reading and displaying
 * the voltage from VOUT BUFF which can be visualized on the SerialPlot application.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the output voltage and displays it on the USB UART (SerialPlot)
 * every 4ms approximately.
 *
 * @note
 * We recommend using the SerialPlot tool for data visualizing. 
 * Please make sure to set up ECG electrodes properly.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ecg7.h"

static ecg7_t ecg7;   /**< ECG 7 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg7_cfg_t ecg7_cfg;  /**< Click config object. */

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
    ecg7_cfg_setup( &ecg7_cfg );
    ECG7_MAP_MIKROBUS( ecg7_cfg, MIKROBUS_1 );
    err_t init_flag = ecg7_init( &ecg7, &ecg7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float ecg7_an_voltage = 0;
    if ( ECG7_OK == ecg7_read_voltage ( &ecg7, &ecg7_an_voltage ) ) 
    {
        log_printf( &logger, "%.3f\r\n", ecg7_an_voltage );
        Delay_ms ( 4 );
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
