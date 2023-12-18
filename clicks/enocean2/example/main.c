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
 * It checks if a switch is pressed, and logs an appropriate message to the uart terminal.
 * 
 * ## Additional Function
 * - enocean2_process ( ) - The general process of collecting data the module sends.
 * - callback_handler ( enocean2_packet_t *packet ) - Checks if a new response message is 
 *                      ready and executes a response message parsing. Once the response
 *                      parsing is done, shows the response message on the uart terminal.
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
#define PROCESS_RX_BUFFER_SIZE 200

// ------------------------------------------------------------------ VARIABLES

static enocean2_t enocean2;
static enocean2_ring_buffer_t enocean2_rb;
static enocean2_rx_data_t enocean2_rx_data;
static log_t logger;

uint8_t rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
uint8_t data_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void clear_app_buf ( void )
{
    Delay_ms( 200 );
    enocean2_generic_read( &enocean2, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
    memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
}

static void decode_command ( uint8_t cmd )
{
    if ( cmd == 0x12 )
    {
        log_printf( &logger,  "-- Button 1 detect --\r\n" );
        clear_app_buf(  );
    }
    else if ( cmd == 0x14 )
    {
        log_printf( &logger, "-- Button 2 detect --\r\n" );
        clear_app_buf(  );
    }
    else if ( cmd == 0x18 )
    {
        log_printf( &logger, "-- Button 3 detect --\r\n" );
        clear_app_buf(  );
    }
    else if ( cmd == 0x22 )
    {
        log_printf( &logger, "-- Button 4 detect --\r\n" );
        clear_app_buf(  );
    }
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
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = enocean2_generic_read( &enocean2, uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
        if ( rsp_size > 0 )
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

    enocean2_cfg_setup( &cfg );
    ENOCEAN2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean2_init( &enocean2, &cfg );

    enocean2_rx_data.rx_buffer   = &rx_buffer[ 0 ];
    enocean2_rx_data.rx_size     = ENOCEAN2_RX_BUFFER_SIZE;
    enocean2_rx_data.data_buffer = &data_buffer[ 0 ];
    enocean2_rx_data.data_size   = ENOCEAN2_RX_BUFFER_SIZE;

    enocean2_init_rx_buff( &enocean2, &enocean2_rb, &enocean2_rx_data );
    enocean2_set_callback_handler( &enocean2, callback_handler );
}

void application_task ( void )
{
    enocean2_process( );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
