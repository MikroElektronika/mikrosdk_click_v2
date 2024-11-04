/*!
 * @file main.c
 * @brief RS232toI2C Click example
 *
 * # Description
 * This example demonstrates the use of an RS232 to I2C Click board by showing
 * the communication between the two Click board configured as a receiver and transmitter.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets
 * the default UART configuration with 9600 baud rate.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data and sends an adequate response back or 
 * sends the desired message and waits for a response every 2 seconds.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rs232toi2c.h"

static rs232toi2c_t rs232toi2c;
static log_t logger;

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

#define DEMO_TEXT_MESSAGE           "MikroE - RS232 to I2C Click"
#define RESPONSE_OK                 "OK"
#define RESPONSE_ERROR              "ERROR"

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs232toi2c_cfg_t rs232toi2c_cfg;  /**< Click config object. */

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
    rs232toi2c_cfg_setup( &rs232toi2c_cfg );
    RS232TOI2C_MAP_MIKROBUS( rs232toi2c_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == rs232toi2c_init( &rs232toi2c, &rs232toi2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RS232TOI2C_ERROR == rs232toi2c_default_cfg ( &rs232toi2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    uint32_t system_version;
    if ( RS232TOI2C_OK == rs232toi2c_read_system_version ( &rs232toi2c, &system_version ) )
    {
        log_printf ( &logger, " System Version: 0x%.6LX\r\n", system_version );
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
    if ( RS232TOI2C_OK == rs232toi2c_write_tx_fifo( &rs232toi2c, DEMO_TEXT_MESSAGE, strlen( DEMO_TEXT_MESSAGE ) ) )
    {
        log_printf( &logger, " The message \"%s\" has been sent!\r\n", ( char * ) DEMO_TEXT_MESSAGE );
        uint16_t timeout_cnt = 5000;
        // wait for an RX interrupt
        while ( rs232toi2c_get_int_pin ( &rs232toi2c ) && timeout_cnt )
        {
            Delay_ms ( 1 );
            timeout_cnt--;
        }
        if ( timeout_cnt )
        {
            uint8_t data_buf[ 256 ] = { 0 };
            uint8_t data_len = 0;
            if ( RS232TOI2C_OK == rs232toi2c_read_rx_fifo( &rs232toi2c, data_buf, &data_len ) )
            {
                log_printf( &logger, " Response: " );
                for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
                {
                    log_printf( &logger, "%c", data_buf[ cnt ] );
                }
            }
        }
        else
        {
            log_error ( &logger, "TIMEOUT - no response received" );
        }
        log_printf( &logger, "\r\n\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
#else
    // wait for an RX interrupt
    while ( rs232toi2c_get_int_pin ( &rs232toi2c ) );
    
    uint8_t data_buf[ 256 ] = { 0 };
    uint8_t data_len = 0;
    if ( RS232TOI2C_OK == rs232toi2c_read_rx_fifo( &rs232toi2c, data_buf, &data_len ) )
    {
        log_printf( &logger, " A new message has received: \"" );
        for ( uint8_t cnt = 0; cnt < data_len; cnt++ )
        {
            log_printf( &logger, "%c", data_buf[ cnt ] );
        }
        log_printf( &logger, "\"\r\n" );
        if ( strstr ( data_buf, DEMO_TEXT_MESSAGE ) )
        {
            if ( RS232TOI2C_OK == rs232toi2c_write_tx_fifo( &rs232toi2c, RESPONSE_OK, strlen( RESPONSE_OK ) ) )
            {
                log_printf( &logger, " Response \"%s\" has been sent to the sender!\r\n\n", ( char * ) RESPONSE_OK );
            }
        }
        else
        {
            if ( RS232TOI2C_OK == rs232toi2c_write_tx_fifo( &rs232toi2c, RESPONSE_ERROR, strlen( RESPONSE_ERROR ) ) )
            {
                log_printf( &logger, " Response \"%s\" has been sent to the sender!\r\n\n", ( char * ) RESPONSE_ERROR );
            }
        }
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
