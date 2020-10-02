/*!
 * \file 
 * \brief Enocean4 Click example
 * 
 * # Description
 * This example reads and processes data from EnOcean 4 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - enocean4_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * *note:* 
 * <NOTE>
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "enocean4.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

enocean4_packet_t  response;
enocean4_packet_t  message;
uint8_t  response_size_cnt;
uint8_t  rsp_check;
uint8_t  device_mode;

char message1[ 10 ] = "Message 1";
char message2[ 10 ] = "Message 2";
char answer1[ 9 ] = "Answer 1";
char answer2[ 9 ] = "Answer 2";

const uint8_t TRANSMITTER = 1;
const uint8_t RECEIVER = 0;

// ------------------------------------------------------------------ VARIABLES

//#define DEMO_APP_RECEIVER
#define DEMO_APP_TRANSMITER

static enocean4_t enocean4;
static log_t logger;

static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void resp_message( uint8_t resp_byte )
{
    char text[ 5 ];

    switch ( resp_byte )
    {
        case ENOCEAN4_RET_OK :
        {
            log_printf( &logger, "OK\r\n" );
        break;
        }
        case ENOCEAN4_RET_ERROR :
        {
            log_printf( &logger,"ERROR\r\n" );
        break;
        }
        case ENOCEAN4_RET_NOT_SUPPORTED :
        {
            log_printf( &logger, "NOT SUPPORTED\r\n" );
        break;
        }
        case ENOCEAN4_RET_WRONG_PARAM :
        {
            log_printf( &logger, "WRONG PARAM\r\n" );
        break;
        }
        case ENOCEAN4_RET_OP_DENIED :
        {
            log_printf( &logger, "OPERATION DENIED\r\n" );
        break;
        }
        case ENOCEAN4_RET_LOCK_SET :
        {
            log_printf( &logger, "LOCK SET\r\n" );
        break;
        }
        case ENOCEAN4_RET_BUFF_TO_SMALL :
        {
            log_printf( &logger, "BUFFER TO SMALL\r\n" );
        break;
        }
        case ENOCEAN4_RET_NO_FREE_BUFF :
        {
            log_printf( &logger, "NO FREE BUFFER\r\n" );
        break;
        }
        default :
        {
            log_printf( &logger, "0x%x \r\n", resp_byte );
            
        break;
        }
    }
}

static void enocean4_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = enocean4_generic_read( &enocean4, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
               log_printf( &logger, " 0x%x ", uart_rx_buffer[ check_buf_cnt ] );
            }
            
            resp_message( uart_rx_buffer[ 1 ] );
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, uart_rx_buffer, rsp_size );
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

void packet_type( )
{
    switch ( response.packet_type )
    {
        case ENOCEAN4_PACK_TYPE_RADIO_ERP1 :
        {
            log_printf( &logger, "RADIO TELEGRAM : \r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_RESPONSE :
        {
            log_printf( &logger, "RESPONSE :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_SUB_TEL :
        {
            log_printf( &logger, "RADIO SUBTELEGRAM :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_EVENT :
        {
            log_printf( &logger, "EVENT :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_COMMON_CMD :
        {
            log_printf( &logger, "COMMON COMMAND :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_SMART_ACK_CMD :
        {
            log_printf( &logger, "SMART ACK COMMAND :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_REMOTE_MAN_CMD :
        {
            log_printf( &logger, "REMOTE MAN COMMAND :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_MSG :
        {
            log_printf( &logger, "RADIO MESSAGE :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_ERP2 :
        {
            log_printf( &logger, "RADIO TELEGRAM ERP2 :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_802_15_4 :
        {
            log_printf( &logger, "802_15_4_RAW PACKET :\r\n " );
        break;
        }
        case ENOCEAN4_PACK_TYPE_CMD_2_4 :
        {
            log_printf( &logger, "2.4 GHz COMMAND :\r\n " );
        break;
        }
        default :
        {
            log_printf( &logger, "MSC - MESSAGE :\r\n " );
        break;
        }
    }
}

void make_response( enocean4_packet_t *rsp, uint8_t *rsp_length_size )
{
    uint16_t rsp_cnt;

    for ( rsp_cnt = 0; rsp_cnt < rsp->data_length; rsp_cnt++ )
    {
        response.data_buff[ rsp_cnt ] = rsp->data_buff[ rsp_cnt ];
    }

    response.data_length = rsp->data_length;
    response.opt_length  = rsp->opt_length;
    response.packet_type = rsp->packet_type;
    response_size_cnt    = *rsp_length_size;
}

void log_response( )
{
    uint16_t rsp_cnt;
    char text_resp[ 5 ];
    char *rsp_byte;

    if ( rsp_check == 1 )
    {
        if ( ( response.packet_type == ENOCEAN4_PACK_TYPE_RESPONSE ) && ( response.data_length == 1 ) )
        {
            packet_type( );
            resp_message( response.data_buff[ 0 ] );

            return;
        }

        packet_type( );
        rsp_check = 0;
    }

    if ( response.packet_type == ENOCEAN4_PACK_TYPE_RADIO_ERP1 )
    {
        for ( rsp_cnt = 1; rsp_cnt < response.data_length - 12; rsp_cnt++ )
        {
            rsp_byte = &response.data_buff[ rsp_cnt ];
            log_printf( &logger, rsp_byte );
        }
    }
    else
    {
        for (rsp_cnt = 0; rsp_cnt < response.data_length; rsp_cnt++)
        {
            log_printf( &logger, "0x", response.data_buff[ rsp_cnt ] );
            
            log_printf( &logger, " ", text_resp );
        }
    }

    if ( response_size_cnt == 0 )
    {
        log_printf( &logger, "" );
        rsp_check = 1;
    }
}

void send_telegram ( char *telegram, uint8_t tel_type )
{
    uint16_t tel_length;
    uint16_t tel_idx;
	char *chr_ptr;

    tel_length = 0;
	chr_ptr = telegram;

    while ( *chr_ptr != 0 )
    {
        tel_length++;
		chr_ptr++;
    }

// Packet Header
    if ( tel_type == ENOCEAN4_RORG_ADT )
    {
        message.opt_length = 7;
    }
    else
    {
        message.opt_length = 0;
    }

    message.data_length = 6 + tel_length;
    message.packet_type = ENOCEAN4_PACK_TYPE_RADIO_ERP1;
    message.data_buff[ 0 ] = tel_type;

// Telegram Data
	chr_ptr = telegram;
	
    for ( tel_idx = 0; tel_idx < tel_length; tel_idx++ )
    {
        message.data_buff[ tel_idx + 1 ] = *chr_ptr;
		chr_ptr++;
    }

// Sender ID	
    message.data_buff[ tel_length + 1 ] = 0x04;
    message.data_buff[ tel_length + 2 ] = 0x10;
    message.data_buff[ tel_length + 3 ] = 0x0B;
    message.data_buff[ tel_length + 4 ] = 0x8B;
    
// Status
    message.data_buff[ tel_length + 5 ] = 0x00;

// Number of sub telegram
    message.data_buff[ tel_length + 6 ] = 0x03;
    
// Destination ID
    message.data_buff[ tel_length + 7 ] = 0x04;
    message.data_buff[ tel_length + 8 ] = 0x10;
    message.data_buff[ tel_length + 9 ] = 0x0B;
    message.data_buff[ tel_length + 10 ] = 0x81;
    
// dBm
    message.data_buff[ tel_length + 11 ] = 0xFF;
    
// Security Level
    message.data_buff[ tel_length + 12 ] = 0x00;

    enocean4_send_packet( &enocean4, &message );
}

void check_response( )
{
    uint8_t response_ready;

    response_ready = enocean4_response_ready( &enocean4 );

    while ( response_ready != ENOCEAN4_RESPONSE_READY )
    {
        response_ready = enocean4_response_ready( &enocean4 );
    }

    enocean4_process( );
    log_response( );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean4_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    enocean4_cfg_setup( &cfg );
    ENOCEAN4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean4_init( &enocean4, &cfg );

    Delay_ms( 500 );

    enocean4_response_handler_set( &enocean4, &make_response );
    Delay_ms( 300 );
    rsp_check = 1;
    enocean4_reset( &enocean4 );

    device_mode = RECEIVER;

    log_printf( &logger, "** EnOcean 4 initialization done **\r\n" );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 500 );

    log_printf( &logger, "Device version reading...\r\n" );
    message.data_length    = 0x0001;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_RD_VERSION;
    enocean4_send_packet( &enocean4, &message );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 1500 );

    log_printf( &logger, "Add filter to filter list...\r\n" );
    message.data_length    = 0x0007;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_WR_FILTER_ADD;
    message.data_buff[ 1 ] = ENOCEAN4_FILTER_TYPE_RORG;
    message.data_buff[ 2 ] = 0x00;
    message.data_buff[ 3 ] = 0x00;
    message.data_buff[ 4 ] = 0x00;
    message.data_buff[ 5 ] = ENOCEAN4_RORG_ADT;
    message.data_buff[ 6 ] = ENOCEAN4_APPLY_RADIO_INTER;
    enocean4_send_packet( &enocean4, &message );
   
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 1500 );

    log_printf( &logger, "Supplied filters reading...\r\n" );
    message.data_length    = 0x0001;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_RD_FILTER;
    enocean4_send_packet( &enocean4, &message );
   
    log_printf( &logger, "***********************************\r\n" );
    log_printf( &logger, "Ready to exchange a telegrams\r\n" );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 1500 );
}

void application_task ( void )
{
    enocean4_process( );

    if ( device_mode == RECEIVER )
    {
        log_printf( &logger, "Telegram receiving...\r\n " );
        log_printf( &logger, "Ok \r\n" );
        Delay_ms( 5000 );
        enocean4_process ( );
        
        log_printf( &logger, "***********************************\r\n" );

        log_printf( &logger, "Telegram sending...\r\n " );
        send_telegram( &answer1[ 0 ], ENOCEAN4_RORG_ADT );
        enocean4_process(  );
        
        log_printf( &logger, "***********************************\r\n" );

        log_printf( &logger, "Telegram receiving...\r\n" );
        log_printf( &logger, "Ok \r\n" );
        enocean4_process( );

        log_printf( &logger, "***********************************\r\n" );
        Delay_ms( 5000 );

        log_printf( &logger, "Telegram sending...\r\n" );
        send_telegram( &answer2[ 0 ], ENOCEAN4_RORG_ADT );
        enocean4_process(  );
        
        log_printf( &logger, "***********************************\r\n" );
    }
    else if ( device_mode == TRANSMITTER )
    {
        log_printf( &logger, "Telegram sending...\r\n" );
        send_telegram( &message1[ 0 ], ENOCEAN4_RORG_ADT );
        enocean4_process( );
        log_printf( &logger, "***********************************\r\n" );

        log_printf( &logger, "Telegram receiving...\r\n" );
        enocean4_process(  );
        log_printf( &logger, "***********************************\r\n" );
        Delay_ms( 5000 );

        log_printf( &logger, "Telegram sending...\r\n" );
        send_telegram( &message2[ 0 ], ENOCEAN4_RORG_ADT );
        enocean4_process( );
        log_printf( &logger, "***********************************\r\n" );

        log_printf( &logger, "Telegram receiving...\r\n" );
        enocean4_process( );
        log_printf( &logger, "***********************************\r\n" );
        Delay_ms( 5000 );
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
