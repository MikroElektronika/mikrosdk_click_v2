/*!
 * @file main.c
 * @brief Current5 Click example
 *
 * # Description
 * This example application showcases ability of the device
 * to read raw adc data and calculate the current from it.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of communication modules(SPI, UART) and 
 * additional pins for controlling device(RST, ALERT->INT).
 *
 * ## Application Task
 * Read ADC data with SPI communication and calculate input current.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current5.h"

static current5_t current5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current5_cfg_t current5_cfg;  /**< Click config object. */

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
    current5_cfg_setup( &current5_cfg );
    CURRENT5_MAP_MIKROBUS( current5_cfg, MIKROBUS_1 );
    err_t init_flag  = current5_init( &current5, &current5_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float current = 0;
    current5_get_current( &current5, &current );
    log_printf( &logger, " > Current[ A ]: %.2f\r\n", current );
    log_printf( &logger, "*************************************************\r\n" );
    Delay_ms( 300 );
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
