/*!
 * @file main.c
 * @brief Proximity 18 Click example
 *
 * # Description
 * This example demonstrates the use of Proximity 18 click board by reading and 
 * displaying the proximity data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, and performs the click default configuration.
 *
 * ## Application Task
 * Reads the proximity data from 3 sensors in a multiplex mode and displays it on the USB UART 
 * approximately once per second. The higher the proximity value, the closer the detected object is.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proximity18.h"

static proximity18_t proximity18;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity18_cfg_t proximity18_cfg;  /**< Click config object. */

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
    proximity18_cfg_setup( &proximity18_cfg );
    PROXIMITY18_MAP_MIKROBUS( proximity18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity18_init( &proximity18, &proximity18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY18_ERROR == proximity18_default_cfg ( &proximity18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t ps1_data, ps2_data, ps3_data;
    if ( PROXIMITY18_ERROR == proximity18_start_measurement ( &proximity18 ) )
    {
        log_error ( &logger, " Start measurement." );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( PROXIMITY18_ERROR == proximity18_wait_for_data_ready ( &proximity18 ) )
    {
        log_error ( &logger, " Wait for data ready." );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( PROXIMITY18_ERROR == proximity18_read_proximity ( &proximity18, &ps1_data, &ps2_data, &ps3_data ) )
    {
        log_error ( &logger, " Read proximity." );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_printf ( &logger, " PS1 data: %u\r\n", ps1_data );
        log_printf ( &logger, " PS2 data: %u\r\n", ps2_data );
        log_printf ( &logger, " PS3 data: %u\r\n\n", ps3_data );
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
