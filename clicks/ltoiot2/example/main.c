/*!
 * \file 
 * \brief LteIot2 Click example
 * 
 * # Description
 * This example reads and processes data from LTE IoT 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - lteiot2_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lteiot2.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500
#define PROCESS_CURRENT_BUFFER_SIZE 1000

// ------------------------------------------------------------------ VARIABLES

static lteiot2_t lteiot2;
static log_t logger;

#define ATI         "ATI"
#define AT_IPR      "AT+IPR=115200;&W"
#define AT_QCFG_1   "AT+QCFG=\"nbsibscramble\",0"
#define AT_QCFG_2   "AT+QCFG=\"band\",0,0,80,1"
#define AT_QCFG_3   "AT+QCFG=\"nwscanmode\",3,1"
#define AT_QCFG_4   "AT+QCFG=\"nwscanseq\",030201,1"
#define AT_QCFG_5   "AT+QCFG=\"iotopmode\",1,1"
#define AT_QCFG_6   "AT+QCFG=\"servicedomain\",1,1"
#define AT_CGDCONT  "AT+CGDCONT=1,\"IP\",\"internet\""
#define AT_CFUN     "AT+CFUN=1"
#define AT_COPS     "AT+COPS=1,2,\"22001\",0"
#define AT_CGATT    "AT+CGATT?"
#define AT_CEREG    "AT+CEREG?"
#define AT_QIACT    "AT+QIACT=1"
#define AT_QIOPEN   "AT+QIOPEN=1,0,\"UDP\",\"79.114.83.116\",16666"
#define AT_QISENDEX "AT+QISENDEX=0,\"48656C6C6F\""

static char current_rx_buf[ PROCESS_CURRENT_BUFFER_SIZE ];
static uint8_t send_data_cnt = 0; 

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lteiot2_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    // Clear parser buffer
    memset( current_rx_buf, 0 , PROCESS_CURRENT_BUFFER_SIZE ); 
    
    while( process_cnt != 0 )
    {
        rsp_size = lteiot2_generic_read( &lteiot2, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( uart_rx_buffer[ check_buf_cnt ] == 0 ) 
                {
                    uart_rx_buffer[ check_buf_cnt ] = 13;
                }
            }
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_CURRENT_BUFFER_SIZE )
            {
                strncat( current_rx_buf, uart_rx_buffer, rsp_size );
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
    log_printf( &logger, "%s", current_rx_buf );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lteiot2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lteiot2_cfg_setup( &cfg );
    LTEIOT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lteiot2_init( &lteiot2, &cfg );

    lteiot2_module_power( &lteiot2, true );

    lteiot2_send_command( &lteiot2, ATI );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+IPR=115200;&W, set baudrate
    lteiot2_send_command( &lteiot2, AT_IPR );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="nbsibscramble",0, Enable scrambling
    lteiot2_send_command( &lteiot2, AT_QCFG_1 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="band",0,0,80,1, set baud
    lteiot2_send_command( &lteiot2, AT_QCFG_2 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="nwscanmode",3,1, Set LTE mode
    lteiot2_send_command( &lteiot2, AT_QCFG_3 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="nwscanseq",030201,1, set priority  NB1 > M1 > 2G
    lteiot2_send_command( &lteiot2, AT_QCFG_4 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="iotopmode",1,1, select CAT-NB1
    lteiot2_send_command( &lteiot2, AT_QCFG_5 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="servicedomain",1,1, Set PS domain
    lteiot2_send_command( &lteiot2, AT_QCFG_6 );
    Delay_1sec( );
    //Command: AT+CGDCONT=1,"IP","internet", set APN provided
    lteiot2_send_command( &lteiot2, AT_CGDCONT );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+CFUN=1, Full functionality
    lteiot2_send_command( &lteiot2, AT_CFUN );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+COPS=1,2,"22001",0, set MCC and MNC provided
    lteiot2_send_command( &lteiot2, AT_COPS );
    lteiot2_process( );
    Delay_1sec( );
    lteiot2_send_command( &lteiot2, AT_CGATT );
    lteiot2_process( );
    Delay_1sec( );
    lteiot2_send_command( &lteiot2, AT_CEREG );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QIACT=1, activate PDP context
    lteiot2_send_command( &lteiot2, AT_QIACT );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QIOPEN=1,0,"UDP","79.114.83.116",16666, create an UDP socket
    lteiot2_send_command( &lteiot2, AT_QIOPEN );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QISENDEX=0,"48656C6C6F", Send message - Hello
    lteiot2_send_command( &lteiot2, AT_QISENDEX );
    lteiot2_process( );
    Delay_1sec( );
}

void application_task ( void )
{
    lteiot2_process( );
    // Send message - Hello
    if ( send_data_cnt == 5 )
    {
        lteiot2_send_command( &lteiot2, AT_QISENDEX );
        lteiot2_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
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
