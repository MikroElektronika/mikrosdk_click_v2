/*!
 * @file main.c
 * @brief MRAM3 Click example
 *
 * # Description
 * This example demonstrates the use of MRAM 3 click board by writing specified data to
 * the memory and reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
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
#include "mram3.h"

static mram3_t mram3;
static log_t logger;

#define DEMO_TEXT_MESSAGE_1         "MikroE"
#define DEMO_TEXT_MESSAGE_2         "MRAM 3 click"
#define STARTING_ADDRESS            0x01234

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mram3_cfg_t mram3_cfg;  /**< Click config object. */

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
    mram3_cfg_setup( &mram3_cfg );
    MRAM3_MAP_MIKROBUS( mram3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == mram3_init( &mram3, &mram3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MRAM3_ERROR == mram3_default_cfg ( &mram3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t data_buf[ 128 ] = { 0 };
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    if ( MRAM3_OK == mram3_memory_write ( &mram3, STARTING_ADDRESS, 
                                          data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( MRAM3_OK == mram3_memory_read ( &mram3, STARTING_ADDRESS, 
                                         data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    memcpy ( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    if ( MRAM3_OK == mram3_memory_write ( &mram3, STARTING_ADDRESS, 
                                          data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data written to address 0x%.5LX: %s\r\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                      data_buf );
    }
    memset ( data_buf, 0, sizeof ( data_buf ) );
    if ( MRAM3_OK == mram3_memory_read ( &mram3, STARTING_ADDRESS, 
                                         data_buf, sizeof ( data_buf ) ) )
    {
        log_printf ( &logger, "Data read from address  0x%.5LX: %s\r\n\n", ( uint32_t ) STARTING_ADDRESS, 
                                                                                        data_buf );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
