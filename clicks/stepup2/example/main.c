/*!
 * @file main.c
 * @brief Step Up 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Step Up 2 Click board by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application changes the output voltage and displays the current voltage output value.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "stepup2.h"

static stepup2_t stepup2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    stepup2_cfg_t stepup2_cfg;  /**< Click config object. */

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
    stepup2_cfg_setup( &stepup2_cfg );
    STEPUP2_MAP_MIKROBUS( stepup2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == stepup2_init( &stepup2, &stepup2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( STEPUP2_ERROR == stepup2_default_cfg ( &stepup2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float vout_table[ 15 ] = { STEPUP2_VOUT_LIST };
    for ( stepup2_vout_t vout = STEPUP2_VOUT_5V5; vout <= STEPUP2_VOUT_3V3; vout++ )
    {
        if ( STEPUP2_OK == stepup2_set_vout( &stepup2, vout ) )
        {
            log_printf( &logger, " Voltage: %.2f[V]\r\n\n", vout_table[ vout ] );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
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
