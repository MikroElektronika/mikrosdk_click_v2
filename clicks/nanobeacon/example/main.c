/*!
 * @file main.c
 * @brief NanoBeacon Click Example.
 *
 * # Description
 * This example demonstrates the use of NanoBeacon Click board by setting
 * the Eddystone URI advertisement to Click boards webpage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Every 10 seconds, it restarts and configures the device for advertisement
 * with the Eddystone URI beacon format set to Click boards webpage: https://www.mikroe.com/click
 * 
 * @note
 * During advertising, the Click board should appear as an Eddystone URI beacon on
 * the BLE Scanner application.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nanobeacon.h"

static nanobeacon_t nanobeacon;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nanobeacon_cfg_t nanobeacon_cfg;  /**< Click config object. */

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
    nanobeacon_cfg_setup( &nanobeacon_cfg );
    NANOBEACON_MAP_MIKROBUS( nanobeacon_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nanobeacon_init( &nanobeacon, &nanobeacon_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // The device MAC address for advertisement
    static uint8_t mac_address[ 6 ] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };

    // Eddystone advertisement raw data
    static uint8_t eddystone_adv_raw[ ] = 
    { 
        0x03, // Length of Service List
        0x03, // Param: Service List
        0xAA, 0xFE, // Eddystone ID
        0x12, // Length of Service Data
        0x16, // Service Data
        0xAA, 0xFE, // Eddystone ID
        0x10, // Frame type: URL
        0x00, // Power
        0x01, // https://www.
        'm','i','k','r','o','e', 
        0x00, // .com/
        'c','l','i','c','k' 
    };
    log_printf( &logger, "\r\n Restart device\r\n" );
    nanobeacon_restart_device ( &nanobeacon );
    
    while ( NANOBEACON_OK != nanobeacon_check_communication ( &nanobeacon ) )
    {
        log_error( &logger, " Check communication." );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " Configure device for advertisement\r\n" );
    if ( NANOBEACON_OK != nanobeacon_set_advertising ( mac_address, 1000, eddystone_adv_raw, 
                                                       sizeof( eddystone_adv_raw ) ) )
    {
        log_error( &logger, " Set advertising." );
    }

    if ( NANOBEACON_OK != nanobeacon_load_adv_to_ram( &nanobeacon ) )
    {
        log_error( &logger, " Load data to RAM." );
    }
    
    log_printf( &logger, " Start advertising\r\n" );
    if ( NANOBEACON_OK != nanobeacon_start_advertising ( &nanobeacon ) )
    {
        log_error( &logger, " Start advertising." );
    }    
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
