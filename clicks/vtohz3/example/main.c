/*!
 * @file main.c
 * @brief VtoHz3 Click example
 *
 * # Description
 * This example demonstrates the use of the V to Hz 3 click board by calculating
 * the estimated output frequency from the input voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the input frequency.
 *
 * ## Application Task
 * Reads the input voltage from AN pin and calculates the output frequency from it.
 * The results are being displayed on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "vtohz3.h"

static vtohz3_t vtohz3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    vtohz3_cfg_t vtohz3_cfg;  /**< Click config object. */

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
    vtohz3_cfg_setup( &vtohz3_cfg );
    VTOHZ3_MAP_MIKROBUS( vtohz3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == vtohz3_init( &vtohz3, &vtohz3_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    vtohz3_set_input_frequency ( &vtohz3, VTOHZ3_DEFAULT_IN_FREQUENCY );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage;
    if ( VTOHZ3_OK == vtohz3_read_an_pin_voltage ( &vtohz3, &voltage ) ) 
    {
        log_printf( &logger, " Voltage : %.2f V\r\n", voltage );
        log_printf( &logger, " Output frequency : %lu Hz\r\n\n", 
                    vtohz3_get_frequency ( &vtohz3, voltage, VTOHZ3_VREF_INTERNAL_2V5 ) );
    }
    Delay_ms( 1000 );
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
