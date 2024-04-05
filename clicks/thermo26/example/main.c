/*!
 * @file main.c
 * @brief Thermo 26 Click example
 *
 * # Description
 * This example demonstrates the use of Thermo 26 click board by reading and displaying
 * the temperature measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and resets the device, and after that reads the serial number and
 * starts the periodic measurements at 2 mps with high repeatability.
 *
 * ## Application Task
 * Reads the temperature measurement in degrees Celsius and displays the results on the USB UART
 * approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "thermo26.h"

static thermo26_t thermo26;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo26_cfg_t thermo26_cfg;  /**< Click config object. */

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
    thermo26_cfg_setup( &thermo26_cfg );
    THERMO26_MAP_MIKROBUS( thermo26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo26_init( &thermo26, &thermo26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    thermo26_reset_device ( &thermo26 );
    
    uint32_t serial_num;
    if ( THERMO26_ERROR == thermo26_read_serial_num ( &thermo26, &serial_num ) )
    {
        log_error( &logger, " Read serial number." );
        for ( ; ; );
    }
    log_printf ( &logger, " Serial number: 0x%.8LX\r\n", serial_num );
    
    if ( THERMO26_ERROR == thermo26_start_measurement ( &thermo26, THERMO26_CMD_PERIODIC_2_MPS_REP_HIGH ) )
    {
        log_error( &logger, " Start measurement." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature;
    if ( THERMO26_OK == thermo26_read_temperature ( &thermo26, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.2f\r\n\n", temperature );
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
