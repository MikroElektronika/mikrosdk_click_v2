/*!
 * @file main.c
 * @brief Current 9 Click Example.
 *
 * # Description
 * This example demonstrates the use of Current 9 click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @note
 * For better accuracy, set the voltage reference by using the @b current9_set_vref function,
 * increase the number of conversions by modifying the @b CURRENT9_NUM_CONVERSIONS macro, 
 * and adjust the @b CURRENT9_ZERO_CURRENT_OFFSET voltage value.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current9.h"

static current9_t current9;   /**< Current 9 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current9_cfg_t current9_cfg;  /**< Click config object. */

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
    current9_cfg_setup( &current9_cfg );
    CURRENT9_MAP_MIKROBUS( current9_cfg, MIKROBUS_1 );
    err_t init_flag = current9_init( &current9, &current9_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    if ( CURRENT9_OK == current9_read_current ( &current9, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f[A]\r\n\n", current );
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
