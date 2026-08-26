/*!
 * @file main.c
 * @brief UNIQUE ID 2 Click example
 *
 * # Description
 * This example demonstrates the use of UNIQUE ID 2 Click board by reading and
 * displaying the unique identifier, and by writing data to the memory and
 * reading it back.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, performs the default configuration and 
 * then reads and displays the UID.
 *
 * ## Application Task
 * Writes a desired number of bytes to the memory and then verifies if it is
 * written correctly by reading from the same memory location and displaying the
 * memory content on the USB UART.
 * 
 * @note
 * When using uniqueid2_write_register() note that setting the DAL bit (CDA) or the WPL bit (SWP)
 * from 0 to 1 is a permanent, irreversible action that freezes the respective register in read-only mode.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "uniqueid2.h"

#ifndef MIKROBUS_POSITION_UNIQUEID2
    #define MIKROBUS_POSITION_UNIQUEID2 MIKROBUS_1
#endif

#define DEMO_TEXT_MESSAGE_1     "MIKROE"
#define DEMO_TEXT_MESSAGE_2     "UNIQUE ID 2 Click"
#define STARTING_ADDRESS        0x012345

static uniqueid2_t uniqueid2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uniqueid2_cfg_t uniqueid2_cfg;  /**< Click config object. */

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
    uniqueid2_cfg_setup( &uniqueid2_cfg );
    UNIQUEID2_MAP_MIKROBUS( uniqueid2_cfg, MIKROBUS_POSITION_UNIQUEID2 );
    if ( I2C_MASTER_ERROR == uniqueid2_init( &uniqueid2, &uniqueid2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UNIQUEID2_ERROR == uniqueid2_default_cfg ( &uniqueid2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint8_t uid[ UNIQUEID2_UID_LEN ] = { 0 };
    uint8_t cnt = 0;

    if ( UNIQUEID2_OK == uniqueid2_read_uid( &uniqueid2, uid ) )
    {
        log_printf( &logger, " UID: " );
        for ( cnt = 0; cnt < UNIQUEID2_UID_LEN; cnt++ )
        {
            log_printf( &logger, "%.2X ", ( uint16_t ) uid[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t data_buf[ UNIQUEID2_PAGE_SIZE ] = { 0 };

    log_printf( &logger, "\r\n Memory address: 0x%.5lX\r\n", ( uint32_t ) STARTING_ADDRESS );

    /* Write first DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_1 ) > UNIQUEID2_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, UNIQUEID2_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_1, strlen ( DEMO_TEXT_MESSAGE_1 ) );
    }
    if ( UNIQUEID2_OK == uniqueid2_write_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read first DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( UNIQUEID2_OK == uniqueid2_read_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_1 ) ) )
    {
        log_printf( &logger, " Read data: %s\r\n", data_buf );
    }
    Delay_ms ( 1000 );

    /* Write second DEMO message */
    if ( strlen ( DEMO_TEXT_MESSAGE_2 ) > UNIQUEID2_PAGE_SIZE )
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, UNIQUEID2_PAGE_SIZE );
    }
    else
    {
        memcpy( data_buf, DEMO_TEXT_MESSAGE_2, strlen ( DEMO_TEXT_MESSAGE_2 ) );
    }
    if ( UNIQUEID2_OK == uniqueid2_write_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
    {
        log_printf( &logger, " Write data: %s\r\n", data_buf );
    }
    Delay_ms ( 100 );

    /* Read second DEMO message */
    memset( data_buf, 0, sizeof ( data_buf ) );
    if ( UNIQUEID2_OK == uniqueid2_read_memory( &uniqueid2, STARTING_ADDRESS, data_buf, strlen ( DEMO_TEXT_MESSAGE_2 ) ) )
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
