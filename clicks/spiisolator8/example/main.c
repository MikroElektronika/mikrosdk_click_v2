/*!
 * @file main.c
 * @brief SPI Isolator 8 Click example
 *
 * # Description
 * This example demonstrates the use of SPI Isolator 8 Click board™ 
 * by reading the manufacturer ID and device ID 
 * of the connected Flash 11 Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module, log UART, and additional pins.
 * After the driver init, the application enabled both isolated sides of the device.
 *
 * ## Application Task
 * The demo application reads and checks the manufacturer ID and 
 * device ID of the connected Flash 11 Click board™. 
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "spiisolator8.h"

static spiisolator8_t spiisolator8;
static log_t logger;

#define FLASH11_CMD_GET_ID         0x90, 0x00, 0x00, 0x00, 0x00, 0x00
#define FLASH11_MANUFACTURER_ID    0x1F
#define FLASH11_DEVICE_ID          0x15

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    spiisolator8_cfg_t spiisolator8_cfg;  /**< Click config object. */

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
    spiisolator8_cfg_setup( &spiisolator8_cfg );
    SPIISOLATOR8_MAP_MIKROBUS( spiisolator8_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == spiisolator8_init( &spiisolator8, &spiisolator8_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    spiisolator8_default_cfg ( &spiisolator8 );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    static uint8_t cmd_get_id[ 6 ] = { FLASH11_CMD_GET_ID };
    static uint8_t read_id[ 6 ] = { 0 };
    if ( SPIISOLATOR8_OK == spiisolator8_transfer( &spiisolator8, &cmd_get_id[ 0 ], &read_id[ 0 ], 6 ) )
    {
        if ( ( FLASH11_MANUFACTURER_ID == read_id[ 4 ] ) && ( FLASH11_DEVICE_ID == read_id[ 5 ] ) )
        {
            log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) read_id[ 4 ] );
            log_printf( &logger, " Device ID: 0x%.2X    \r\n", ( uint16_t ) read_id[ 5 ] );
            log_printf( &logger, " -----------------------\r\n" );
            Delay_ms( 3000 );
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
