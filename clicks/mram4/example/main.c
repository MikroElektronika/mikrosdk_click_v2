/*!
 * @file main.c
 * @brief MRAM 4 Click example
 *
 * # Description
 * This example demonstrates the use of MRAM 4 Click board.
 * The demo app writes specified data to the memory and reads it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application writes a desired number of bytes to the memory 
 * and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mram4.h"

static mram4_t mram4;
static log_t logger;

#define STARTING_ADDRESS             0x012345ul
#define DEMO_TEXT_MESSAGE_1         "MikroE"
#define DEMO_TEXT_MESSAGE_2         "MRAM 4 Click"

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram4_cfg_t mram4_cfg;  /**< Click config object. */

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
    mram4_cfg_setup( &mram4_cfg );
    MRAM4_MAP_MIKROBUS( mram4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mram4_init( &mram4, &mram4_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM4_ERROR == mram4_default_cfg ( &mram4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( MRAM4_OK == mram4_block_erase( &mram4, MRAM4_CMD_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
        Delay_ms ( 100 );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );    
    if ( MRAM4_OK == mram4_memory_write( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM4_OK == mram4_memory_read( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf( &logger, " ----------------------------\r\n" );
    
    log_printf( &logger, " Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );
    if ( MRAM4_OK == mram4_block_erase( &mram4, MRAM4_CMD_ERASE_4KB, STARTING_ADDRESS ) )
    {
        log_printf( &logger, " Erase memory block (4KB)\r\n" );
    }
    
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM4_OK == mram4_memory_write( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
        Delay_ms ( 100 );
    }
    
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM4_OK == mram4_memory_read( &mram4, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    log_printf ( &logger, " ----------------------------\r\n" );
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
