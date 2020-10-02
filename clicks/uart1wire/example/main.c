/*!
 * \file 
 * \brief UART1Wire Click example
 * 
 * # Description
 * This example reads and processes data from UART 1-Wire clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - process ( ) : The general process of collecting presponce that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uart1wire.h"
#include "string.h"

#define PROCESS_COUNTER    10
#define RX_BUFFER_SIZE     500

// ------------------------------------------------------------------ VARIABLES

static uart1wire_t uart1wire;
static log_t logger;

static char rx_buffer[ RX_BUFFER_SIZE ];
static uint16_t msb;
static uint16_t old_val;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void process ( void )
{
    uint16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    uint16_t check_buf_cnt;    
    uint8_t process_cnt = PROCESS_COUNTER;

    uart1wire_write_command( &uart1wire, UART1WIRE_READ_SEQ );
    
    // Clear parser buffer
    memset( rx_buffer, 0, RX_BUFFER_SIZE ); 
    
    while ( process_cnt != 0 )
    {
        rsp_size = uart1wire_generic_read( &uart1wire, &rx_buffer, RX_BUFFER_SIZE );
        
        process_cnt--;

        Delay_10ms( );
    }
}

static uint16_t msb_check ( uint16_t new_val ) 
{
    uint8_t new;
    uint8_t old;

    new = new_val;
    old = old_val;

    if ( new <= 0x0F )
    {
        if ( old >= 0xF0 && old <= 0xFF )
        {
            msb++;
        }
    }
    else if ( new >= 0xF0 && new <= 0xFF )
    {
        if ( old <= 0x0F )
        {
            msb--;
        }
    }

    old_val = new_val;

    new_val &= 0x00FF;
    new_val |= ( msb << 8 );
    
    return new_val;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uart1wire_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uart1wire_cfg_setup( &cfg );
    UART1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uart1wire_init( &uart1wire, &cfg );

    uart1wire_reset( &uart1wire );
    uart1wire_default_cfg( &uart1wire );

    msb = 0;
    old_val = 0;
}

void application_task ( void )
{
    uint16_t temp;
    float temp_f;

    /* Conversion */

    uart1wire_reset( &uart1wire );
    uart1wire_write_command( &uart1wire, UART1WIRE_DATA_MODE );
    Delay_10ms( );
    uart1wire_write_command( &uart1wire, UART1WIRE_SKIP_ROM );
    uart1wire_write_command( &uart1wire, 0x44 );
    Delay_ms( 750 );

    /* Temperature reading */ 
    
    uart1wire_reset( &uart1wire );
    uart1wire_write_command( &uart1wire, UART1WIRE_DATA_MODE );
    Delay_10ms( );
    uart1wire_write_command( &uart1wire, UART1WIRE_SKIP_ROM );
    uart1wire_write_command( &uart1wire, 0xBE );
    Delay_10ms( );

    process( );

    temp = msb_check ( rx_buffer[ 0 ] );
    temp <<= 1;

    temp_f = temp * 0.0625;

    log_printf( &logger, " * Raw (<< 1):            %d\r\n", temp );
    log_printf( &logger, " * Temperature:     %.2f C\r\n", temp_f );
    log_printf( &logger, "*------------------------------*\r\n" );

    Delay_ms( 1000 );
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
