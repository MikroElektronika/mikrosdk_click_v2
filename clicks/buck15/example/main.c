/*!
 * @file main.c
 * @brief Buck 15 Click example
 *
 * # Description
 * This example demonstrates the use of the Buck 15 Click board by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the device default configuration.
 *
 * ## Application Task
 * The demo application changes the output voltage and displays the currently set voltage output value.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck15.h"

static buck15_t buck15;
static log_t logger;

// Output voltage data table
static float vout_table[ 22 ] = { BUCK15_VOUT_TABLE };

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck15_cfg_t buck15_cfg;  /**< Click config object. */

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
    buck15_cfg_setup( &buck15_cfg );
    BUCK15_MAP_MIKROBUS( buck15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck15_init( &buck15, &buck15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK15_ERROR == buck15_default_cfg ( &buck15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "____________\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    for ( buck15_vout_t vout = BUCK15_VOUT_0V6; vout <= BUCK15_VOUT_5V; vout++ )
    {
        if ( BUCK15_OK == buck15_set_vout( &buck15, vout ) )
        {
            log_printf( &logger, " Vout : %.1f [V]\r\n", vout_table[ vout ] );
            log_printf( &logger, "____________\r\n" );
            Delay_ms( 5000 );
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
