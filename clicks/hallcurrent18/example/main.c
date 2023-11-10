/*!
 * @file main.c
 * @brief Hall Current 18 Click Example.
 *
 * # Description
 * This example demonstrates the use of Hall Current 18 click board™ 
 * by reading and displaying the current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module and log UART.
 * After driver initialization, the app sets the default configuration
 * and set the zero voltage reference.
 *
 * ## Application Task
 * The demo application reads the current measurements [A] and displays the results.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent18.h"

static hallcurrent18_t hallcurrent18;   /**< Hall Current 18 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent18_cfg_t hallcurrent18_cfg;  /**< Click config object. */

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
    hallcurrent18_cfg_setup( &hallcurrent18_cfg );
    HALLCURRENT18_MAP_MIKROBUS( hallcurrent18_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent18_init( &hallcurrent18, &hallcurrent18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HALLCURRENT18_ERROR == hallcurrent18_default_cfg ( &hallcurrent18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_printf( &logger, " Turn off the load current in the following 5 sec.\r\n" );
    Delay_ms( 5000 );
    if ( HALLCURRENT18_OK == hallcurrent18_set_zero_ref( &hallcurrent18 ) )
    {
        log_printf( &logger, " Process complete!\r\n");
    }
    else
    {
        log_error( &logger, " Zero reference." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    float current = 0;
    if ( HALLCURRENT18_OK == hallcurrent18_read_current ( &hallcurrent18, &current ) ) 
    {
        log_printf( &logger, " Current : %.2f [A]\r\n", current );
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
