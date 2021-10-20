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
 * SQI FASH Driver Initialization, initializes the click by setting mikroBUS to
 * approprieate logic levels, performing global block unlock and chip erase functions,
 * reads manufacturer ID, memory type and device ID and logs it on USB UART teminal.
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

uint8_t device_manufac;
uint8_t device_type;
uint8_t device_id;

char wr_data[ 10 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10 , 0 };
char rd_data[ 10 ];

void application_init ( void ) {
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
    err_t init_flag  = sqiflash_init( &sqiflash, &sqiflash_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 300 );
    sqiflash_global_block_unlock( &sqiflash );
    Delay_ms( 400 );
    sqiflash_chip_erase( &sqiflash );
    Delay_ms( 300 );
    
    device_manufac = sqiflash_device_manufac( &sqiflash );
    log_printf( &logger, "Manufacturer ID: 0x%.2X \r\n", ( uint16_t ) device_manufac );
    device_type = sqiflash_device_type( &sqiflash );
    log_printf( &logger, "Memory Type:     0x%.2X \r\n", ( uint16_t ) device_type );
    device_id = sqiflash_device_id( &sqiflash );
    log_printf( &logger, "Device ID:       0x%.2X \r\n", ( uint16_t ) device_id );
    log_printf( &logger, "--------------------\r\n" );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_printf( &logger, "Writing data to flash memory, from address 0x015015:\r\n" );
    log_printf( &logger, "Data written: %s ", wr_data );
    sqiflash_write_generic( &sqiflash, 0x015015, &wr_data[ 0 ], 9 );
    log_printf( &logger, "Reading 9 bytes of flash memory, from address 0x015015:\r\n" );
    sqiflash_read_generic( &sqiflash, 0x015015, &rd_data[ 0 ], 9 );
    log_printf( &logger, "Data read: %s ", rd_data );
    log_printf( &logger, "--------------------------------------------------------\r\n" );
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
