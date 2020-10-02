/*!
 * \file 
 * \brief NanoLora Click example
 * 
 * # Description
 * This example reads and processes data from Nano LoRa clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART serial interface, UART interrupt, and power ON the module.
 * 
 * ## Application Task  
 * This function has two segments.
 * The first segment allows user to enter a commands, module configurations,
 * data which will be transmitted, and also to check all module and connection
 * status by using the serial terminal.
 * Special commands:
 * Press 'Enter' when you want to send the entered command (data).
 * Press 'Backspace' to delete the wrong entered character before you send the
 * command.
 * Press 'Up-Down' or 'Left-Right' to see and enter a 3 last sent commands.
 * Press 'Esc' and then 'r' character to perform a hardware reset via RST pin.
 * The second segment allows user to read and check response from the SIM868
 * module when the response is ready.
 * 
 * ## Additional Function
 * - nanolora_process ( ) - The general process of collecting presponce 
 *                          that sends a module.
 * - application_handler ( ) - Checks when new response message is ready and executes
 *                             a response message parsering. When the response
 *                             parsering is done, shows the response message on the
 *                             uart terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nanolora.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

#define RECEIVER
//#define TRANSMITTER

static nanolora_t nanolora;
static log_t logger;

static char demo_text[ 7 ] = "mikorE";
static uint16_t rsp_size;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void nanolora_process ( void )
{
    
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint16_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    

    while( process_cnt != 0 )
    {
        rsp_size = nanolora_generic_read( &nanolora, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                nanolora_uart_isr( &nanolora, uart_rx_buffer[ check_buf_cnt ] ); 
            }
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, PROCESS_RX_BUFFER_SIZE );
        } 
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

void application_handler( )
{
    uint8_t drdy_flag;

    drdy_flag = nanolora_rsp_rdy( &nanolora );

    if ( drdy_flag )
    {
        nanolora_err_t error;
        nanolora_rsp_t response;

        log_printf( &logger, "** NEW MESSAGE:\r\n" );

        error = nanolora_parser_rsp( &nanolora, &response );

        if ( error == 0 )
        {
            uint16_t cnt;

            log_printf( &logger, "** Message Length: 0x%x\r\n", response.length );

            log_printf( &logger, "** Message ID: 0x%x\r\n", response.message_id );

            for ( cnt = 0; cnt < response.length - 4; cnt++ )
            {
                log_printf( &logger, "** Message Content[ %d ]: 0x%x\r\n", cnt, response.payload[ cnt ] );
                Delay_ms( 10 );
            }

            log_printf( &logger, "** Message Checksum: 0x%x\r\n", response.crc );
        }
        else
        {
            log_printf( &logger, "** Message Error!\r\n" );
        }

        log_printf( &logger, "\r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanolora_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanolora_cfg_setup( &cfg );
    NANOLORA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanolora_init( &nanolora, &cfg );

    nanolora_default_cfg( &nanolora );

    log_printf( &logger,  "--  Nano LoRa Click --\r\n" );
    log_printf( &logger,  " Initialization  done \r\n" );
    log_printf( &logger,  "----------------------\r\n" );

    #ifdef TRANSMITTER
    
        log_printf( &logger,  "----  TRANSMITER  ----\r\n" );

    #endif

    #ifdef RECEIVER
    
        log_printf( &logger,  "-----  RECEIVER  -----\r\n" );

    #endif

    log_printf( &logger, "----------------------\r\n" ); 
    Delay_ms( 2000 );
}

void application_task ( void )
{    
    #ifdef RECEIVER

    nanolora_process( );
    application_handler( );
        
    #endif

    #ifdef TRANSMITTER

    nanolora_send_data( &nanolora, &demo_text[ 0 ], 6 );
    Delay_ms( 2000 );

    #endif
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
