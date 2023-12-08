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
 * Initializes the driver and configures the click board.
 * 
 * ## Application Task  
 * In the receiver mode, it waits for a telegram, then replies to it with the certain message.
 * In the transmitter mode, first it sends the telegram with the certain message, 
 * then waits for a response.
 * 
 * ## Additional Function
 * - resp_message - Displays the response message on the USB UART.
 * - packet_type - Displays the packet type message on the USB UART.
 * - make_response - Driver handler function which stores data in the response buffer.
 * - log_response - Displays a response on the USB UART.
 * - send_telegram - Allows user to send a telegram to the determined destination.
 * - check_response - Waits until response is ready, then displays it on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "enocean4.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

#define DEMO_MESSAGE "MikroE"
#define DEMO_ANSWER  "EnOcean 4"

enocean4_packet_t response;
enocean4_packet_t message;
uint8_t response_size_cnt;
uint8_t rsp_check;
uint8_t device_mode;

static enocean4_t enocean4;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void resp_message( uint8_t resp_byte )
{
    switch ( resp_byte )
    {
        case ENOCEAN4_RET_OK :
        {
            log_printf( &logger, "OK\r\n" );
            break;
        }
        case ENOCEAN4_RET_ERROR :
        {
            log_printf( &logger, "ERROR\r\n" );
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
            log_printf( &logger, "0x%.2X\r\n", ( uint16_t ) resp_byte );
            break;
        }
    }
}

void packet_type( )
{
    switch ( response.packet_type )
    {
        case ENOCEAN4_PACK_TYPE_RADIO_ERP1 :
        {
            log_printf( &logger, "RADIO TELEGRAM : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_RESPONSE :
        {
            log_printf( &logger, "RESPONSE : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_SUB_TEL :
        {
            log_printf( &logger, "RADIO SUBTELEGRAM : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_EVENT :
        {
            log_printf( &logger, "EVENT : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_COMMON_CMD :
        {
            log_printf( &logger, "COMMON COMMAND : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_SMART_ACK_CMD :
        {
            log_printf( &logger, "SMART ACK COMMAND : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_REMOTE_MAN_CMD :
        {
            log_printf( &logger, "REMOTE MAN COMMAND : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_MSG :
        {
            log_printf( &logger, "RADIO MESSAGE : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_ERP2 :
        {
            log_printf( &logger, "RADIO TELEGRAM ERP2 : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_RADIO_802_15_4 :
        {
            log_printf( &logger, "802_15_4_RAW PACKET : " );
            break;
        }
        case ENOCEAN4_PACK_TYPE_CMD_2_4 :
        {
            log_printf( &logger, "2.4 GHz COMMAND : " );
            break;
        }
        default :
        {
            log_printf( &logger, "MSC - MESSAGE : " );
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
            log_printf( &logger, "%c", ( uint16_t ) response.data_buff[ rsp_cnt ] );
        }
    }
    else
    {
        for ( rsp_cnt = 0; rsp_cnt < response.data_length; rsp_cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) response.data_buff[ rsp_cnt ] );
        }
    }

    if ( response_size_cnt == 0 )
    {
        log_printf( &logger, "\r\n" );
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

    enocean4_uart_isr( &enocean4 );
    response_ready = enocean4_response_ready( &enocean4 );

    while ( response_ready != ENOCEAN4_RESPONSE_READY )
    {
        enocean4_uart_isr( &enocean4 );
        response_ready = enocean4_response_ready( &enocean4 );
        Delay_1ms( );
    }

    enocean4_process( &enocean4 );
    log_response( );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    enocean4_cfg_t cfg;

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

    enocean4_cfg_setup( &cfg );
    ENOCEAN4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    enocean4_init( &enocean4, &cfg );

    Delay_ms( 500 );

    enocean4_response_handler_set( &enocean4, &make_response );
    Delay_ms( 300 );
    rsp_check = 1;
    enocean4_reset( &enocean4 );

    log_printf( &logger, "** EnOcean 4 initialization done **\r\n" );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 500 );
    
    // Clearing RX buffer
    {
        uint8_t tmp_buf[ 100 ];
        enocean4_generic_read( &enocean4, tmp_buf, 100 );
    }

    log_printf( &logger, "Device version reading...\r\n" );
    message.data_length    = 0x0001;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_RD_VERSION;
    enocean4_send_packet( &enocean4, &message );
    check_response( );
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
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 1500 );

    log_printf( &logger, "Supplied filters reading...\r\n" );
    message.data_length    = 0x0001;
    message.opt_length     = 0x00;
    message.packet_type    = ENOCEAN4_PACK_TYPE_COMMON_CMD;
    message.data_buff[ 0 ] = ENOCEAN4_CMD_CO_RD_FILTER;
    enocean4_send_packet( &enocean4, &message );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    log_printf( &logger, "Ready to exchange telegrams\r\n" );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 1500 );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    log_printf( &logger, "Waiting for a telegram...\r\n" );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );

    log_printf( &logger, "Replying to the received telegram...\r\n" );
    send_telegram( DEMO_ANSWER, ENOCEAN4_RORG_ADT );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
#endif
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "Sending a telegram...\r\n" );
    send_telegram( DEMO_MESSAGE, ENOCEAN4_RORG_ADT );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );

    log_printf( &logger, "Waiting for a response...\r\n" );
    check_response( );
    log_printf( &logger, "***********************************\r\n" );
    Delay_ms( 5000 );
#endif
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
