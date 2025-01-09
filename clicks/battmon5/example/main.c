/*!
 * @file main.c
 * @brief BATT-MON 5 Click example
 *
 * # Description
 * This example demonstrates the use of BATT-MON 5 Click board by reading
 * the battery cell voltage and the relative state of charge (RSOC).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the battery cell voltage and the relative state of charge (RSOC) and
 * displays the results on the USB UART approximately once per second.
 *
 * @note
 * For the communication with the Click board to work, the battery needs to be connected.
 * The Click board is configured by default for a 2000 mAh battery pack capacity.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "battmon5.h"

static battmon5_t battmon5;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    battmon5_cfg_t battmon5_cfg;  /**< Click config object. */

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
    battmon5_cfg_setup( &battmon5_cfg );
    BATTMON5_MAP_MIKROBUS( battmon5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == battmon5_init( &battmon5, &battmon5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BATTMON5_ERROR == battmon5_default_cfg ( &battmon5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t voltage = 0;
    uint16_t rsoc = 0;
    if ( BATTMON5_OK == battmon5_read_reg ( &battmon5, BATTMON5_REG_CELL_V, &voltage ) )
    {
        log_printf ( &logger, " Voltage: %u mV\r\n", voltage ); // Battery Cell Voltage
    }
    if ( BATTMON5_OK == battmon5_read_reg ( &battmon5, BATTMON5_REG_RSOC, &rsoc ) )
    {
        log_printf ( &logger, " RSOC: %u %%\r\n\n", rsoc ); // Relative State Of Charge
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
