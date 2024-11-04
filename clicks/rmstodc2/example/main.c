/*!
 * @file main.c
 * @brief RMS to DC 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of the RMS to DC 2 Click board by measuring
 * the RMS voltage of the input signal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the RMS voltage of the input signal and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rmstodc2.h"

static rmstodc2_t rmstodc2;   /**< RMS to DC 2 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rmstodc2_cfg_t rmstodc2_cfg;  /**< Click config object. */

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
    rmstodc2_cfg_setup( &rmstodc2_cfg );
    RMSTODC2_MAP_MIKROBUS( rmstodc2_cfg, MIKROBUS_1 );
    err_t init_flag = rmstodc2_init( &rmstodc2, &rmstodc2_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    if ( RMSTODC2_OK == rmstodc2_read_voltage ( &rmstodc2, &voltage ) ) 
    {
        log_printf( &logger, " RMS voltage : %.3f[V]\r\n\n", voltage * RMSTODC2_RMS_VOLTAGE_COEF );
        Delay_ms ( 1000 );
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
