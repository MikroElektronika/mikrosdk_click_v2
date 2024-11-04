/*!
 * @file main.c
 * @brief UWB 2 Click example
 *
 * # Description
 * This example demonstrates the use of an UWB 2 Click board by showing
 * the communication between the two Click boards.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration, then reads
 * and displays the device ID number.
 *
 * ## Application Task
 * Depending on the selected application mode, it reads all the received data or 
 * sends the desired text message with the message counter once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uwb2.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - UWB 2 Click board\0"

static uwb2_t uwb2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uwb2_cfg_t uwb2_cfg;  /**< Click config object. */

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
    uwb2_cfg_setup( &uwb2_cfg );
    UWB2_MAP_MIKROBUS( uwb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uwb2_init( &uwb2, &uwb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UWB2_ERROR == uwb2_default_cfg ( &uwb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t dev_id = 0;
    if ( UWB2_OK == uwb2_read_reg_32bit ( &uwb2, UWB2_REG_DEV_ID, &dev_id ) )
    {
        log_printf ( &logger, " Device ID: 0x%.8LX\r\n", dev_id );
    }
    
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, " Application Mode: Transmitter\r\n" );
#else
    log_printf( &logger, " Application Mode: Receiver\r\n" );
#endif
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    static uint8_t tx_msg_cnt = 0;
    uint8_t tx_buffer[ 128 ] = { 0 };
    uint16_t tx_msg_size = 0;
    tx_buffer[ 0 ] = tx_msg_cnt; // Message number.
    strcpy ( &tx_buffer[ 1 ], DEMO_TEXT_MESSAGE );
    tx_msg_size = strlen ( DEMO_TEXT_MESSAGE ) + 2; // Message size + null-terminated + tx_msg_cnt
    if ( UWB2_OK == uwb2_send_message ( &uwb2, tx_buffer, tx_msg_size ) )
    {
        log_printf ( &logger, " Message sent #%u\r\n\n", tx_buffer[ 0 ] );
        tx_msg_cnt++; // Increment message number (modulo 256).
    }
    Delay_ms ( 1000 );
#else
    uint8_t rx_buffer[ 128 ] = { 0 };
    uint16_t rx_msg_size = sizeof ( rx_buffer );
    if ( UWB2_OK == uwb2_read_message ( &uwb2, rx_buffer, &rx_msg_size ) )
    {
        log_printf ( &logger, " Message received #%u: %s\r\n\n", 
                     ( uint16_t ) rx_buffer[ 0 ], &rx_buffer[ 1 ] );
    }
#endif
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
