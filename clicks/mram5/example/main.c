/*!
 * @file main.c
 * @brief MRAM 5 Click example
 *
 * # Description
 * This example demonstrates the use of MRAM 5 Click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies if it is written correctly
 * by reading from the same memory location and displaying the memory content on the USB UART.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "mram5.h"

#ifndef MIKROBUS_POSITION_MRAM5
    #define MIKROBUS_POSITION_MRAM5 MIKROBUS_1
#endif

#define DEMO_TEXT_MESSAGE_1     "MikroE"
#define DEMO_TEXT_MESSAGE_2     "MRAM 5 Click"
#define STARTING_ADDRESS        0x012345
#define DEMO_BUFFER_SIZE        64

static mram5_t mram5;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram5_cfg_t mram5_cfg;  /**< Click config object. */

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
    mram5_cfg_setup( &mram5_cfg );
    MRAM5_MAP_MIKROBUS( mram5_cfg, MIKROBUS_POSITION_MRAM5 );
    if ( SPI_MASTER_ERROR == mram5_init( &mram5, &mram5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM5_ERROR == mram5_default_cfg ( &mram5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ DEMO_BUFFER_SIZE ] = { 0 };

    log_printf( &logger, "\r\n Memory address: 0x%.6LX\r\n", ( uint32_t ) STARTING_ADDRESS );

    /* Write first DEMO message */
    memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen( DEMO_TEXT_MESSAGE_1 ) );
    if ( MRAM5_OK == mram5_memory_write( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read first DEMO message */
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM5_OK == mram5_memory_read( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 1000 );

    /* Write second DEMO message */
    memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM5_OK == mram5_memory_write( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read second DEMO message */
    memset( data_buf, 0, sizeof( data_buf ) );
    if ( MRAM5_OK == mram5_memory_read( &mram5, STARTING_ADDRESS, data_buf, sizeof( data_buf ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
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
