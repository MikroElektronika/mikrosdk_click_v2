/*!
 * \file 
 * \brief NfcTag4 Click example
 * 
 * # Description
 * This application checks if a message was placed to the mailbox, and then logs
 * the message length.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, presents password to the device and initializes the device.
 * 
 * ## Application Task  
 * Checks if RF placed a message to mailbox and if it did, checks message
 * length and logs message bytes.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nfctag4.h"

// ------------------------------------------------------------------ VARIABLES

static nfctag4_t nfctag4;
static log_t logger;

static uint8_t aux_buffer[ 258 ];
static uint16_t i;
 
static uint8_t message_length = 0;
static transfer_info info;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void nfctag4_wait_for_int ()
{
    uint32_t timer_counter = 0;
    uint8_t int_pin_flag = 0;
    int_pin_flag = nfctag4_int_get( &nfctag4 );
    while ( ( int_pin_flag == 1 ) && ( timer_counter <= 300 ) )
    {
        Delay_ms( 1 );
        timer_counter++;
        int_pin_flag = nfctag4_int_get( &nfctag4 );
    }

    if ( timer_counter <= 300 )
    {
        int_pin_flag = nfctag4_int_get( &nfctag4 );
        while ( int_pin_flag == 0 )
        {
            int_pin_flag = nfctag4_int_get( &nfctag4 );
        }
    }

    timer_counter = 0;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nfctag4_cfg_t cfg;

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    nfctag4_cfg_setup( &cfg );
    NFCTAG4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nfctag4_init( &nfctag4, &cfg );

    nfctag4_default_cfg( &nfctag4 );
}

void application_task ( void )
{
    nfctag4_wait_for_int( );

    info.memory_area = NFCTAG4_MEMORY_DYNAMIC;
    info.register_address = NFCTAG4_DYNAMIC_REG_MB_CTRL;
    info.n_registers = 1;
    nfctag4_i2c_get( &nfctag4, &info, aux_buffer );

    if ( ( aux_buffer[ 0 ] & 0x04 ) == ( 0x04 ) )
    {
        nfctag4_wait_for_int( );
        info.memory_area = NFCTAG4_MEMORY_DYNAMIC;
        info.register_address = NFCTAG4_DYNAMIC_REG_MB_LEN;
        info.n_registers = 1;
        nfctag4_i2c_get( &nfctag4, &info, aux_buffer );
        message_length = aux_buffer[ 0 ];
        message_length++;
        nfctag4_wait_for_int( );
        info.memory_area = NFCTAG4_MEMORY_MAILBOX;
        info.register_address = NFCTAG4_MAILBOX_REG_BYTE_0;
        info.n_registers = message_length;
        nfctag4_i2c_get( &nfctag4, &info, aux_buffer );

        log_printf( &logger, "************* MESSAGE ***************\r\n" );
        log_printf( &logger, "Message length: %d\r\n", message_length );

        for ( i = 0; i < message_length; i++ )
        {
            log_printf( &logger, "%d: 0x%x\r\n", i, aux_buffer[ i ] );
        }

        log_printf( &logger, "************** END ****************\r\n" );
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
