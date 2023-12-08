/*!
 * @file main.c
 * @brief POT 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of POT 4 click board by reading and displaying
 * the potentiometer position.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads and displays on the USB UART the potentiometer position in forms of voltage and
 * percents once per second only when the potentiometer switch is active.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pot4.h"

static pot4_t pot4;     /**< POT 4 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot4_cfg_t pot4_cfg;  /**< Click config object. */

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
    pot4_cfg_setup( &pot4_cfg );
    POT4_MAP_MIKROBUS( pot4_cfg, MIKROBUS_1 );
    err_t init_flag = pot4_init( &pot4, &pot4_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !pot4_get_switch_pin ( &pot4 ) )
    {
        float voltage = 0;
        if ( POT4_OK == pot4_read_voltage ( &pot4, &voltage ) ) 
        {
            log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
            log_printf( &logger, " Potentiometer : %u %%\r\n\n", 
                        ( uint16_t ) pot4_convert_voltage_to_percents ( &pot4, voltage ) );
            Delay_ms( 1000 );
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
