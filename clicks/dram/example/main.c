/*!
 * @file main.c
 * @brief DRAM Click example
 *
 * # Description
 * This example demonstrates the use of DRAM click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, resets the device and checks the communication by reading
 * and verifying the device ID.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dram.h"

#define DEMO_TEXT_MESSAGE_1     "MikroE"
#define DEMO_TEXT_MESSAGE_2     "DRAM click"
#define STARTING_ADDRESS        0x012345ul

static dram_t dram;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dram_cfg_t dram_cfg;  /**< Click config object. */

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
    dram_cfg_setup( &dram_cfg );
    DRAM_MAP_MIKROBUS( dram_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dram_init( &dram, &dram_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DRAM_ERROR == dram_reset ( &dram ) )
    {
        log_error( &logger, " Reset device." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    if ( DRAM_ERROR == dram_check_communication ( &dram ) )
    {
        log_error( &logger, " Check communication." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( DRAM_OK == dram_memory_write ( &dram, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( DRAM_OK == dram_memory_read ( &dram, STARTING_ADDRESS, 
                                             data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Read data: %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
    log_printf ( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( DRAM_OK == dram_memory_write ( &dram, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( DRAM_OK == dram_memory_read_fast ( &dram, STARTING_ADDRESS, data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, " Fast read data : %s\r\n\n", data_buf );
        Delay_ms ( 3000 );
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
