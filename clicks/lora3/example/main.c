/*!
 * \file 
 * \brief LoRa3 Click example
 * 
 * # Description
 * This example reads and processes data from LoRa 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART bus driver, sets device (module) as MASTER and enables pairing
 * in first case. In second case sets device as END NODE and sends pairing request and 
 * message witch causes that MASTER will get indication.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - lora3_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * - indication_handler ( uint8_t *cmd, uint8_t *pl_size, uint8_t *pl_buffer ) - 
 *                      Logs results on USB UART when device gets indication on command.
 *
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lora3.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_PARSER_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

//#define MASTER
#define END_NODE

static lora3_t lora3;
static lora3_tx_msg_t lora3_tx_msg;
static log_t logger;
static uint8_t tmp_cnt;
static uint8_t  crc;

static lora3_message_t tmp_msg;
static lora3_message_t tmp_rsp;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lora3_process ( void )
{
    uint16_t rsp_size;

    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    if ( 0 == digital_in_read( &lora3.int_pin ) )
    {
      while( process_cnt != 0 )
      {
        rsp_size = lora3_generic_read( &lora3, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( lora3.flag == 4 && crc != lora3_chk_sum( &tmp_rsp ) )
                {
                    lora3.result = LORA3_ERR_CHKSUM;
                    lora3.flag = 0;
                }
                else if ( lora3.flag == 4 && crc == lora3_chk_sum( &tmp_rsp ) )
                {
                    lora3.flag = 0;
                    lora3.result = LORA3_OK;
                    lora3.ind_hanlder( &tmp_rsp.command, &tmp_rsp.pay_load_size, &tmp_rsp.pay_load[ 0 ] );
                }
                else if ( lora3.flag == 3  )
                {
                    while ( tmp_cnt > 0 )
                    {
                        tmp_rsp.pay_load[ tmp_rsp.curr_pos ] = uart_rx_buffer[ check_buf_cnt ];
                        tmp_rsp.curr_pos++;
                        tmp_cnt--;
                    }
                    if ( tmp_cnt == 0 )
                    {
                        crc = uart_rx_buffer[ check_buf_cnt ];
                        digital_out_high( &lora3.wk );
                        Delay_100ms( );
                        lora3.flag = 4;
                    }
                }
                else if ( lora3.flag == 2 )
                {
                    tmp_rsp.pay_load_size = uart_rx_buffer[ check_buf_cnt ];
                    tmp_cnt = tmp_rsp.pay_load_size;
                    tmp_rsp.curr_pos = 0;
                    lora3.flag = 3;
                }
                else if ( lora3.flag == 1 )
                {
                    tmp_rsp.command = uart_rx_buffer[ check_buf_cnt ];
                    lora3.flag = 2;
                }
                else if ( lora3.flag == 0 && uart_rx_buffer[ check_buf_cnt ] == FRAME_HEADER ) 
                {
                    lora3.flag = 1;
                }
                else
                {
                    lora3.result = LORA3_ERR_HEADER;
                }
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
}

void indication_handler( uint8_t *cmd, uint8_t *pl_size, uint8_t *pl_buffer )
{
    uint8_t cnt;
    
    log_printf( &logger, "IND TYPE: 0x%x\r\n", cmd );

    log_printf( &logger, "PAYLOAD : " );
    
    for ( cnt = 0; cnt <= *pl_size; cnt++ )
    {
        log_printf( &logger, "0x%x ", pl_buffer[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lora3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lora3_cfg_setup( &cfg );
    LORA3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lora3_init( &lora3, &cfg );

    Delay_ms( 100 );
    lora3_set_ind_handler( &lora3, indication_handler );
    lora3_hard_reset( &lora3 );
    lora3_factory_reset( &lora3 );
    Delay_ms( 1000 );

    lora3.flag = 0;
    tmp_cnt = 0;
    crc = 0;

#ifdef MASTER
    // Set device as MASTER and enable pairing 
    tmp_msg.pay_load[ 0 ] = 0;

    lora3_write_eeprom( &lora3, 0x00, 1, &tmp_msg.pay_load[ 0 ] );
    if( !lora3.result )
    {
        log_printf( &logger, "EEPROM writting Error\r\n" );
    }
    else
    {
        log_printf( &logger, "EEPROM writting is OK\r\n" );
    }
    Delay_ms( 1000 );
    
    lora3_enable_pairing( &lora3, 1 );
    log_printf( &logger, "Pairing enable\r\n" );
    Delay_ms( 1000 );
#endif

#ifdef END_NODE
    // Set device as END NODE and send pairing request and message
    tmp_msg.pay_load[ 1 ] = 2;
    tmp_msg.pay_load[ 2 ] = 3;
    tmp_msg.pay_load[ 3 ] = 4;
    tmp_msg.pay_load[ 4 ] = 5;

    lora3_get_pairing_request( &lora3 );
    log_printf( &logger, "Pairing request\r\n" );
    Delay_ms( 2000 );
    
    lora3_tx_msg.data_in = &tmp_msg.pay_load[ 1 ];
    lora3_tx_msg.n_bytes = 3;
    lora3_tx_msg.destination_id = 0xFFFFFFFF;
    lora3_tx_msg.option = LORA3_UNCONFIRMED_DATA_TX;

    lora3_tx_message( &lora3, &lora3_tx_msg );
#endif
}

void application_task ( void )
{
    lora3_process( );
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
