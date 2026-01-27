/*!
 * @file main.c
 * @brief Hydrogen 2 Click example
 *
 * # Description
 * This example demonstrates the use of the Hydrogen 2 Click board for
 * measuring hydrogen gas concentration and internal sensor temperature.
 * Basic device information such as sensor ID, product code, firmware
 * revision, and manufacturer code is also displayed.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and Hydrogen 2 Click driver, applies the default
 * configuration, and reads out device identification information.
 *
 * ## Application Task
 * Periodically reads hydrogen concentration data and temperature
 * values from the sensor and logs them to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hydrogen2.h"

static hydrogen2_t hydrogen2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hydrogen2_cfg_t hydrogen2_cfg;  /**< Click config object. */

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
    hydrogen2_cfg_setup( &hydrogen2_cfg );
    HYDROGEN2_MAP_MIKROBUS( hydrogen2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hydrogen2_init( &hydrogen2, &hydrogen2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HYDROGEN2_ERROR == hydrogen2_default_cfg ( &hydrogen2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " Sensor ID: 0x%.8LX\r\n", hydrogen2.info.sensor_id );
    log_printf ( &logger, " Product Code: 0x%.4LX\r\n", hydrogen2.info.product_code );
    log_printf ( &logger, " FW Revision Number: 0x%.4LX\r\n", hydrogen2.info.fw_rev_num );
    log_printf ( &logger, " Manufacturer Code: 0x%.2LX\r\n", hydrogen2.info.man_code );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    int16_t raw_conc = 0;
    int8_t temp = 0;
    if ( HYDROGEN2_OK == hydrogen2_get_conc ( &hydrogen2, &raw_conc ) )
    {
        log_printf ( &logger, " H2: %.2f %%\r\n", raw_conc * HYDROGEN2_H2_RES );
    }
    if ( HYDROGEN2_OK == hydrogen2_get_temp ( &hydrogen2, &temp ) )
    {
        log_printf ( &logger, " T: %d degC\r\n\n", temp );
    }
    Delay_ms ( 1000 );
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
