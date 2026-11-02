/*!
 * @file main.c
 * @brief 4-20mA T 5 Click example
 *
 * # Description
 * This example demonstrates the use of 4-20mA T 5 Click board by setting the
 * analog output current of an industry standard 4-20mA current loop.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Sweeps the loop output current from 4mA to 20mA in 4mA steps
 * and displays the selected current and the error flag state on the USB UART.
 *
 * @author Milan Ivancic
 *
 * @note
 * The JP2 jumper must be in the VCC position in order to select the current
 * output mode. An external power supply from 8V to 60V must be connected to
 * the TB3 terminal and the current loop to the TB2 terminal.
 *
 */

#include "board.h"
#include "log.h"
#include "c420mat5.h"

#ifndef MIKROBUS_POSITION_C420MAT5
    #define MIKROBUS_POSITION_C420MAT5 MIKROBUS_1
#endif

// Demo iteration steps
#define C420MAT5_DEMO_STEPS     5

static c420mat5_t c420mat5;
static log_t logger;

// Demo current values in mA
static float demo_current[ C420MAT5_DEMO_STEPS ] = { 4.0, 8.0, 12.0, 16.0, 20.0 };

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c420mat5_cfg_t c420mat5_cfg;  /**< Click config object. */

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
    c420mat5_cfg_setup( &c420mat5_cfg );
    C420MAT5_MAP_MIKROBUS( c420mat5_cfg, MIKROBUS_POSITION_C420MAT5 );
    if ( SPI_MASTER_ERROR == c420mat5_init( &c420mat5, &c420mat5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C420MAT5_ERROR == c420mat5_default_cfg ( &c420mat5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( uint8_t cnt = 0; C420MAT5_DEMO_STEPS > cnt; cnt++ )
    {
        if ( C420MAT5_OK == c420mat5_set_output_current( &c420mat5, demo_current[ cnt ] ) )
        {
            log_printf( &logger, " Loop current: %.2f mA\r\n", demo_current[ cnt ] );
        }
        else
        {
            log_error( &logger, " Failed to set output current." );
        }
        if ( C420MAT5_ERR_FLAG_ACTIVE == c420mat5_get_err_pin( &c420mat5 ) )
        {
            log_printf( &logger, " Error flag is active\r\n" );
        }
        log_printf( &logger, " --------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
