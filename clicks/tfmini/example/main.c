/*!
 * @file main.c
 * @brief TFmini Click Example.
 *
 * # Description
 * This example demonstrates the use of TFmini click board by reading the measurements
 * from the attached TFmini-S or TFmini Plus sensors.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and the click board, and reads the firmware version of the attached sensor.
 *
 * ## Application Task
 * Reads the target distance, signal strength and the internal sensor temperature every 100ms approximately,
 * and displays the results on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "tfmini.h"

static tfmini_t tfmini;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;        /**< Logger config object. */
    tfmini_cfg_t tfmini_cfg;  /**< Click config object. */

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
    tfmini_cfg_setup( &tfmini_cfg );
    TFMINI_MAP_MIKROBUS( tfmini_cfg, MIKROBUS_1 );
    tfmini_drv_interface_selection ( &tfmini_cfg, TFMINI_DRV_SEL_UART );
    if ( TFMINI_OK != tfmini_init( &tfmini, &tfmini_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TFMINI_OK != tfmini_default_cfg ( &tfmini ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t fw_version = 0;
    if ( TFMINI_OK == tfmini_get_firmware_version ( &tfmini, &fw_version ) )
    {
        log_printf( &logger, " FW Version: 0x%.6LX\r\n", fw_version );
    }
    Delay_ms( 1000 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    int16_t distance = 0, strength = 0;
    float temperature = 0;
    if ( TFMINI_OK == tfmini_get_measurement ( &tfmini, &distance, &strength, &temperature ) ) 
    {
        log_printf( &logger, " Target distance: %d cm\r\n", distance );
        log_printf( &logger, " Signal strength: %d\r\n", strength );
        log_printf( &logger, " Sensor temperature: %.2f C\r\n\n", temperature );
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
