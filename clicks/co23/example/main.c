/*!
 * @file main.c
 * @brief CO2 3 Click example
 *
 * # Description
 * This library contains API for CO2 3 Click driver.
 * This driver provides the functions for sensor configuration 
 * and reading the CO2 gas concentration in the air.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or UART module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the CO2 3 Click board™.
 * The device starts a single measurement sequence,
 * measures and display air CO2 gas concentration (ppm).
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "co23.h"

static co23_t co23;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    co23_cfg_t co23_cfg;  /**< Click config object. */

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
    co23_cfg_setup( &co23_cfg );
    CO23_MAP_MIKROBUS( co23_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == co23_init( &co23, &co23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( CO23_ERROR == co23_default_cfg ( &co23 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{     
    co23_meas_cfg_t meas_cfg;
    meas_cfg.op_mode = CO23_OP_MODE_SINGLE;
    co23_set_meas_cfg( &co23, meas_cfg );
    Delay_ms ( 1000 );
    
    uint16_t co2_ppm = 0;
    co23_get_co2_ppm( &co23, &co2_ppm );
    log_printf( &logger, " CO2: %d ppm\r\n", co2_ppm );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
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
