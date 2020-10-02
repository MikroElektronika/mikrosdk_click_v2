/*!
 * \file 
 * \brief LoRa5 Click example
 * 
 * # Description
 * This example reads and processes data from LoRa 5 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes UART interface and UART interrupt, and performs a module reset commands.
 * 
 * ## Application Task  
 * Performs a group of commands to get FW version, the serial number provided by Mipot,
 * DevEUI, the session status, the activation status and the parameters for the selected channel.
 * Also sets the next transmission data rate to the desired value.
 * The responses from the Mipot module to the host will be sent to the uart terminal.
 * 
 * ## Additional Function
 * - lora5_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * - make_response - Stores data from the module to the response structure.
 * - log_response -  Sends the recevied response from the module to the uart terminal.
 * - wait_response - Waits until response from the module was ready and then calls the 
 *                 response logging function, or writes the error message on the uart terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lora5.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 300

// ------------------------------------------------------------------ VARIABLES

static lora5_t lora5;
static log_t logger;
lora5_cmd_t response;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lora5_process ( void )
{
    int32_t rsp_size;
    uint8_t process_cnt = 10;
    
    uint8_t check_buf_cnt;

    while( process_cnt != 0 )
    {
        rsp_size = lora5_generic_read( &lora5, lora5.rx_dat, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                lora5_uart_isr( &lora5 );
            }
        }
        else 
        {
            process_cnt--;
            
            // Process delay 
            Delay_100ms( );
        }
    }
}

void make_response ( uint8_t *rsp_code, uint8_t *rsp_length, uint8_t *rsp_data )
{
    uint8_t rsp_idx;

    response.cmd_code   = *rsp_code;
    response.cmd_length = *rsp_length;

    for ( rsp_idx = 0; rsp_idx < response.cmd_length; rsp_idx++ )
    {
        response.cmd_data[ rsp_idx ] = *rsp_data;
        rsp_data++;
    }
}

void log_response ( )
{
    uint8_t rsp_idx;
    
    log_printf( &logger, "** OPCODE : 0x%x\r\n", response.cmd_code );
    
    log_printf( &logger, "** RESPONSE LENGTH : 0x%x\r\n", response.cmd_length );
    
    log_printf ( &logger, "** RESPONSE : " );
    for ( rsp_idx = 0; rsp_idx < response.cmd_length; rsp_idx++ )
    {
        log_printf( &logger, "0x%x ", response.cmd_data[ rsp_idx ] );
    }
    log_printf( &logger, "\r\n" );
    
    log_printf( &logger, "***********************************************\r\n" );
    log_printf( &logger, "\r\n" );
}

void wait_response ( )
{
    LORA5_RETVAL resp_code;
    do
    {
        lora5_process(  );
        resp_code = lora5_response_ready( &lora5 );
    }
    while ( resp_code == LORA5_RESPONSE_NOT_RECEIVED );

    resp_code = lora5_task( &lora5 );
    
    switch ( resp_code )
    {
        case LORA5_CMD_RESPONSE_READY :
        {
            log_response( );
        break;
        }
        case LORA5_IND_RESPONSE_READY :
        {
            log_response( );
        break;
        }
        case LORA5_FRAME_HEADER_ERR :
        {
            log_printf( &logger, "** Frame Header Error **\r\n" );
            log_printf( &logger, "***********************************************\r\n" );
            log_printf( &logger, "\r\n" );
        break;
        }
        case LORA5_CMD_RESPONSE_ERR :
        {
            log_printf( &logger, "** Response Code Error **\r\n" );
            log_printf( &logger, "***********************************************\r\n" );
            log_printf( &logger, "\r\n" );
        break;
        }
        case LORA5_CHKSUM_ERR :
        {
            log_printf( &logger, "** Checksum Error **\r\n" );
            log_printf( &logger, "***********************************************\r\n" );
            log_printf( &logger, "\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    Delay_ms( 1000 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lora5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lora5_cfg_setup( &cfg );
    LORA5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lora5_init( &lora5, &cfg );

    lora5_response_handler_set( &lora5, &make_response );
    Delay_ms( 1000 );

    lora5_reset_cmd( &lora5 );
    wait_response( );
    Delay_ms( 1000 );
    lora5_factory_reset_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** LoRa 5 (MIPOT 32001409) reset is done **\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    lora5_process(  );

    log_printf( &logger, "** FW version reading...\r\n" );
    lora5_get_fw_version_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** Serial number reading...\r\n" );
    lora5_get_serial_no_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** DevEUI reading...\r\n" );
    lora5_get_dev_eui_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** Session status reading...\r\n" );
    lora5_get_session_status_cmd( &lora5 );
    wait_response( );
    switch ( response.cmd_data[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, "Idle.\r\n" );
        break;
        }
        case 0x01 :
        {
            log_printf( &logger, "Busy (LoRa session running).\r\n" );
        break;
        }
        case 0x02 :
        {
            log_printf( &logger, "Device not activated.\r\n" );
        break;
        }
        case 0x03 :
        {
            log_printf( &logger, "Delayed.\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "** Activation status reading...\r\n" );
    lora5_get_activation_status_cmd( &lora5 );
    wait_response( );
    switch ( response.cmd_data[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, "Not activated.\r\n" );
        break;
        }
        case 0x01 :
        {
            log_printf( &logger, "Joining...\r\n" );
        break;
        }
        case 0x02 :
        {
            log_printf( &logger, "Joined.\r\n" );
        break;
        }
        case 0x03 :
        {
            log_printf( &logger, "MAC ERROR.\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "** Next TX Data Rate setting...\r\n" );
    lora5_set_next_dr_cmd( &lora5, LORA5_SF10_125KHZ );
    wait_response( );
    if ( response.cmd_data[ 0 ] == 0x00 )
    {
        log_printf( &logger, "Success!\r\n" );
    }
    else
    {
        log_printf( &logger, "Error!\r\n" );
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "** Channel parameters reading...\r\n" );
    lora5_get_ch_param_cmd( &lora5, LORA5_CH_IDX_15 );
    wait_response( );
    Delay_ms( 10000 );
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
