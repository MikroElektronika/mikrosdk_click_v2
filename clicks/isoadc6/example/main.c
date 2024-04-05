/*!
 * @file main.c
 * @brief ISO ADC 6 Click example
 *
 * # Description
 * This example demonstrates the use of the ISO ADC 6 Click board™ 
 * by reading and writing data by using SPI serial interface 
 * and reading results of AD conversion.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration which enables channel 0,
 * puts A0 on positive analog input and A1 on negative analog input,
 * enables internal reference voltage (approximately 2.65V (AVDD = 3.3V)),
 * and also enables bipolar operation mode and puts device on full power mode.
 *
 * ## Application Task
 * The demo application reads the voltage levels from analog input (A0-A1) and displays the results.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "isoadc6.h"

static isoadc6_t isoadc6;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc6_cfg_t isoadc6_cfg;  /**< Click config object. */

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
    isoadc6_cfg_setup( &isoadc6_cfg );
    ISOADC6_MAP_MIKROBUS( isoadc6_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == isoadc6_init( &isoadc6, &isoadc6_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISOADC6_ERROR == isoadc6_default_cfg ( &isoadc6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float voltage = 0;
    if ( ISOADC6_OK == isoadc6_get_voltage( &isoadc6, &voltage ) )
    {
        log_printf( &logger, " Voltage: %.3f [V]\r\n", voltage );
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
