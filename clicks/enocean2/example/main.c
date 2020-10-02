/*!
 * \file 
 * \brief EnOcean2 Click example
 * 
 * # Description
 * This example reads and processes data from EnOcean 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init and initializes chip and sets callback handler.
 * 
 * ## Application Task  
 * It checks if a switch is pressed, 
 * in case it is logging to the uart message about which swithc is pressed.
 * 
 * ## Additional Function
 * - enocean2_process ( ) - The general process of collecting presponce that sends a module.
 * - callback_handler ( enocean2_packet_t *packet ) - Checks when new response message is 
 *                      ready and executes a response message parsering. When the response
 *                      parsering is done, shows the response message on the uart terminal.
 * - decode_command ( uint8_t cmd ) - Detect which of the 4 buttons is pressed.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "enocean2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

static enocean2_t enocean2;
static enocean2_ring_buffer_t enocean2_rb;
static enocean2_rx_data_t enocean2_rx;
static log_t logger;

uint8_t rx_buffer[ 512 ] = { 0 };
uint8_t data_buffer[ 512 ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void decode_command ( uint8_t cmd )
{
    if ( cmd == 0x12 )
    {
        log_printf( &logger,  "-- Button 1 detect --\r\n" );
    }
    else if ( cmd == 0x14 )
    {
        log_printf( &logger, "-- Button 2 detect --\r\n" );
    }
    else if ( cmd == 0x18 )
    {
        log_printf( &logger, "-- Button 3 detect --\r\n" );
    }
    else if ( cmd == 0x22 )
    {
        log_printf( &logger, "-- Button 4 detect --\r\n" );
    }
    Delay_ms( 100 );
}

static void callback_handler ( enocean2_packet_t *packet )
{
    uint8_t sequence_number = 0;

    if ( packet->type == ENOCEAN2_TYPE_RADIO_802_15_4 )
    {
        if ( sequence_number != packet->data_buffer[ ENOCEAN2_SEQUENCE_NUMBER_OFFSET ] )
        {
            decode_command( packet->data_buffer[ ENOCEAN2_COMMAND_OFFSET ] );
        }
    }
}

static void enocean2_process ( void )
{
    int16_t rsp_size; 
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = enocean2_generic_read( &enocean2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                enocean2_rx( &enocean2_rb, uart_rx_buffer[ check_buf_cnt ] ); 
                enocean2_packet_recieve( &enocean2, &enocean2_rb );
            }           

            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_ms( 100 );
        }
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean2_cfg_setup( &cfg );
    ENOCEAN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean2_init( &enocean2, &cfg );

    enocean2_rx.rx_buffer   = &rx_buffer[ 0 ];
    enocean2_rx.rx_size     = ENOCEAN2_RX_BUFFER_SIZE;
    enocean2_rx.data_buffer = &data_buffer[ 0 ];
    enocean2_rx.data_size   = ENOCEAN2_RX_BUFFER_SIZE;

    enocean2_init_rx_buff( &enocean2, &enocean2_rb, &enocean2_rx );
    enocean2_set_callback_handler( &enocean2, callback_handler );
}

void application_task ( void )
{
    enocean2_process( );
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
