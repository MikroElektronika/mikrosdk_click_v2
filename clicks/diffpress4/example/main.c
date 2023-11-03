/*!
 * @file main.c
 * @brief Diff Press 4 Click example
 *
 * # Description
 * This example demonstrates the use of Diff Press 4 Click board™ 
 * by reading and displaying the differential pressure and sensor temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * The demo application reads and displays the Differential Pressure [Pa] 
 * and sensor Temperature [degree Celsius] data measurements.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "diffpress4.h"

static diffpress4_t diffpress4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress4_cfg_t diffpress4_cfg;  /**< Click config object. */

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
    diffpress4_cfg_setup( &diffpress4_cfg );
    DIFFPRESS4_MAP_MIKROBUS( diffpress4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == diffpress4_init( &diffpress4, &diffpress4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " _______________________ \r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float diff_press = 0, temperature = 0;
    diffpress4_status_t status;
    diffpress4_get_status( &diffpress4, &status );
    if ( ( DIFFPRESS4_OK == diffpress4_get_measurement_data( &diffpress4, &diff_press, &temperature ) ) &&
         ( DIFFPRESS4_STATUS_DSP_S_UPDATED == status.dsp_s_up ) && 
         ( DIFFPRESS4_STATUS_DSP_T_UPDATED == status.dsp_t_up ) )
    {
        log_printf( &logger, " Diff Pressure : %.2f [Pa] \r\n", diff_press );
        log_printf( &logger, " Temperature   : %.2f [degC] \r\n", temperature );
        log_printf( &logger, " _______________________ \r\n" );
        Delay_ms( 1000 );
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
