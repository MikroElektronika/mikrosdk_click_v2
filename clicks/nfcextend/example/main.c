/*!
 * \file 
 * \brief NfcExtend Click example
 * 
 * # Description
 * This example showcases how to configure and use the NFC Extend click. The click is an NFC tag 
 * interface which uses the I2C serial interface and an RF link interface in order to communicate.
 * The example requires the ST25 NFC Tap application which can be downloaded to your phone.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function waits for the interrupt signal, after which it expects data transfers. Once
 * some data has been detected it will open a communication channel with the device transmitting
 * it and show the received data in the UART console.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nfcextend.h"

// ------------------------------------------------------------------ VARIABLES

static nfcextend_t nfcextend;
static log_t logger;

uint8_t default_password[ NFCEXTEND_PASSWORD_LEN ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void wait_for_interrupt ( )
{
    uint8_t int_pin_flag;
    uint16_t timer_counter;

    int_pin_flag = nfcextend_digital_read_int( &nfcextend );
    timer_counter = 0;
    
    while ( ( int_pin_flag == 1 ) && ( timer_counter <= 300 ) )
    {
        Delay_ms( 1 );
        timer_counter++;
        int_pin_flag = nfcextend_digital_read_int( &nfcextend );
    }

    if ( timer_counter <= 300 )
    {
        int_pin_flag = nfcextend_digital_read_int( &nfcextend );

        while ( int_pin_flag == 0 )
        {
            int_pin_flag = nfcextend_digital_read_int( &nfcextend );
        }
    }

    timer_counter = 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    nfcextend_cfg_t cfg;

    uint8_t init_status_flag;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nfcextend_cfg_setup( &cfg );
    NFCEXTEND_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nfcextend_init( &nfcextend, &cfg );

    nfcextend_password_present( &nfcextend, default_password );
    Delay_ms( 100 );

    init_status_flag = nfcextend_default_cfg( &nfcextend );
    Delay_ms( 100 );

    if ( 1 == init_status_flag )
    {
        log_printf( &logger, " * App init failed. *\r\n" );
    }
    else if ( 0 == init_status_flag ) 
    {
        log_printf( &logger, " * App init done. *\r\n" );
    }
    log_printf( &logger, "-----------------------\r\n" );
}

void application_task ( )
{
    nfcextend_block_t block;

    uint8_t temp_buf[ 258 ];
    uint16_t message_len;
    uint16_t cnt;

    block.memory_area = NFCEXTEND_MEMORY_DYNAMIC;
    block.reg_addr = NFCEXTEND_DYNAMIC_REG_MB_CTRL;
    block.data_buf = temp_buf;
    block.len = 1;

    wait_for_interrupt( );
    nfcextend_i2c_get( &nfcextend, &block );

    if ( ( temp_buf[ 0 ] & 0x04 ) == 0x04 )
    {
        block.reg_addr = NFCEXTEND_DYNAMIC_REG_MB_LEN;
        block.data_buf = &temp_buf[ 0 ];

        wait_for_interrupt( );
        nfcextend_i2c_get( &nfcextend, &block );

        message_len = temp_buf[ 0 ] + 1;

        block.memory_area = NFCEXTEND_MEMORY_MAILBOX;
        block.reg_addr = NFCEXTEND_MAILBOX_REG_BYTE_0;
        block.data_buf = &temp_buf[ 0 ];
        block.len = message_len;

        wait_for_interrupt( );
        nfcextend_i2c_get( &nfcextend, &block );

        log_printf( &logger, " ** Message length:  %u Bytes**\r\n", message_len);
        
        log_printf( &logger, " ------------------------------\r\n" );
        log_printf( &logger, " ** Message START **\r\n" );

        for ( cnt = 0; cnt < message_len; cnt++ )
        {
            log_printf( &logger, " %u : 0x%x\r\n", cnt, ( uint16_t ) temp_buf[ cnt ] );
        }

        log_printf( &logger, " ** Message END **\r\n" );
        log_printf( &logger, " ------------------------------\r\n" );
    }
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
