/*!
 * @file main.c
 * @brief SqiFlash Click example
 *
 * # Description
 * This is an example that demonstrates the use of the SQI FLASH Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * SQI FLASH Driver Initialization, initializes the click by setting mikroBUS to
 * approprieate logic levels, performing global block unlock and chip erase functions,
 * reads manufacturer ID, memory type and device ID and logs it on USB UART terminal.
 *
 * ## Application Task
 * Writing data to click memory and displaying the read data via UART.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "sqiflash.h"

static sqiflash_t sqiflash;
static log_t logger;

uint8_t device_manufac = 0;
uint8_t device_type = 0;
uint8_t device_id = 0;

uint8_t wr_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
uint8_t rd_data[ 9 ] = { 0 };
uint32_t address = 0x015015ul;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    sqiflash_cfg_t sqiflash_cfg;  /**< Click config object. */

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
    sqiflash_cfg_setup( &sqiflash_cfg );
    SQIFLASH_MAP_MIKROBUS( sqiflash_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == sqiflash_init( &sqiflash, &sqiflash_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    Delay_ms ( 300 );
    sqiflash_global_block_unlock( &sqiflash );
    Delay_ms ( 400 );
    sqiflash_chip_erase( &sqiflash );
    Delay_ms ( 300 );
    
    device_manufac = sqiflash_device_manufac( &sqiflash );
    log_printf( &logger, " Manufacturer ID: 0x%.2X\r\n", ( uint16_t ) device_manufac );
    device_type = sqiflash_device_type( &sqiflash );
    log_printf( &logger, " Memory Type: 0x%.2X\r\n", ( uint16_t ) device_type );
    device_id = sqiflash_device_id( &sqiflash );
    log_printf( &logger, " Device ID: 0x%.2X\r\n", ( uint16_t ) device_id );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Writing data to address: 0x%.6LX\r\n", address );
    sqiflash_write_generic( &sqiflash, address, wr_data, 9 );
    log_printf( &logger, " Written data: %s", wr_data );
    log_printf( &logger, "\r\n Reading data from address: 0x%.6LX\r\n", address );
    sqiflash_read_generic( &sqiflash, address, rd_data, 9 );
    log_printf( &logger, " Read data: %s", rd_data );
    log_printf( &logger, "-------------------------------------\r\n" );
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
