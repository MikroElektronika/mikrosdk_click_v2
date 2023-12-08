/*!
 * @file main.c
 * @brief POT 5 Click Example.
 *
 * # Description
 * This example demonstrates the use of POT 5 click board by reading and displaying
 * the potentiometer position.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads and displays on the USB UART the potentiometer position in forms of voltage and
 * percents once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pot5.h"

static pot5_t pot5;   /**< POT 5 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot5_cfg_t pot5_cfg;  /**< Click config object. */

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
    pot5_cfg_setup( &pot5_cfg );
    POT5_MAP_MIKROBUS( pot5_cfg, MIKROBUS_1 );
    err_t init_flag = pot5_init( &pot5, &pot5_cfg );
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
    if ( POT5_OK == pot5_read_voltage ( &pot5, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
        log_printf( &logger, " Potentiometer : %u %%\r\n\n", 
                    ( uint16_t ) pot5_convert_voltage_to_percents ( &pot5, voltage ) );
        Delay_ms( 1000 );
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
