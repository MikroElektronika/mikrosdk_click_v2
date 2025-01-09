/*!
 * @file main.c
 * @brief Piezo Accel 2 25g Click example
 *
 * # Description
 * This example demonstrates the use of Piezo Accel 2 25g Click board by reading and displaying
 * the ADC values of X, Y, and Z axis, and the internal temperature sensor measurements. 
 * Those data can be visualized on the SerialPlot application.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration for ADC measurements.
 *
 * ## Application Task
 * Reads the ADC values of X, Y, and Z axis, and the internal temperature sensor measurements
 * and displays them on the USB UART (SerialPlot) every 5ms approximately.
 *
 * @note
 * We recommend using the SerialPlot tool for data visualization. The temperature measurements
 * should be visualized independently. The data format for plotter is as follows: X;Y;Z;TEMP;
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "piezoaccel225g.h"

static piezoaccel225g_t piezoaccel225g;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    piezoaccel225g_cfg_t piezoaccel225g_cfg;  /**< Click config object. */

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
    piezoaccel225g_cfg_setup( &piezoaccel225g_cfg );
    PIEZOACCEL225G_MAP_MIKROBUS( piezoaccel225g_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == piezoaccel225g_init( &piezoaccel225g, &piezoaccel225g_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIEZOACCEL225G_ERROR == piezoaccel225g_default_cfg ( &piezoaccel225g ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    piezoaccel225g_adc_data_t adc_data;
    if ( PIEZOACCEL225G_OK == piezoaccel225g_read_adc_data ( &piezoaccel225g, &adc_data ) )
    {
        log_printf ( &logger, "%lu;%lu;%lu;%lu;\r\n", adc_data.raw_x, adc_data.raw_y, 
                                                      adc_data.raw_z, adc_data.raw_temp );
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