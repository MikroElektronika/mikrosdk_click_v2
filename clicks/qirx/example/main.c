/*!
 * @file main.c
 * @brief QiRX Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Qi RX Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes I2C driver and makes an initial log.
 *
 * ## Application Task
 * This example shows the capabilities of the Qi RX click by measuring voltage of the connected
 * battery. In order to get correct calculations user should change "v_ref" value 
 * to his own power supply voltage.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "qirx.h"

static qirx_t qirx;
static log_t logger;
uint16_t voltage;
uint16_t v_ref = 5058;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    qirx_cfg_t qirx_cfg;  /**< Click config object. */

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
    qirx_cfg_setup( &qirx_cfg );
    QIRX_MAP_MIKROBUS( qirx_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == qirx_init( &qirx, &qirx_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "----------------------- \r\n" );
    log_printf( &logger, "      Qi RX click       \r\n" );
    log_printf( &logger, "----------------------- \r\n" );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------- \r\n" );
}

void application_task ( void ) 
{
    voltage = qirx_read_voltage( &qirx, v_ref );
    log_printf( &logger, " Battery voltage: %d mV \r\n", voltage );
    log_printf( &logger, "----------------------- \r\n" );
    Delay_ms( 2000 );
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
