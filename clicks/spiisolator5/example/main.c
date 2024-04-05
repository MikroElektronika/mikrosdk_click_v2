/*!
 * @file main.c
 * @brief SPI Isolator 5 Click example
 *
 * # Description
 * This example demonstrates the use of SPI Isolator 5 click board 
 * by reading the manufacturer ID and device ID 
 * of the connected Flash 11 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module, log UART, and additional pins.
 * After the driver init, the app performs enabling a device.
 *
 * ## Application Task
 * The demo application reads and checks the manufacturer ID and 
 * device ID of the connected Flash 11 click board. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator5.h"

#define FLASH11_CMD_GET_ID         0x90, 0x00, 0x00, 0x00, 0x00, 0x00
#define FLASH11_MANUFACTURER_ID    0x1F
#define FLASH11_DEVICE_ID          0x15

static spiisolator5_t spiisolator5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator5_cfg_t spiisolator5_cfg;  /**< Click config object. */

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
    spiisolator5_cfg_setup( &spiisolator5_cfg );
    SPIISOLATOR5_MAP_MIKROBUS( spiisolator5_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator5_init( &spiisolator5, &spiisolator5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    spiisolator5_enable( &spiisolator5 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    if ( SPIISOLATOR5_OK == spiisolator5_transfer( &spiisolator5, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
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
