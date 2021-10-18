/*!
 * \file 
 * \brief LR5 Click example
 * 
 * # Description
 * This example reads and processes data from LR 5 clicks.
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
 * - lr5_process - The general process of collecting data the module sends.
 * - make_response - Stores data from the module to the response structure.
 * - log_response -  Sends the received response from the module to the uart terminal.
 * - wait_response - Waits until response from the module is ready and then calls the 
 *                 response logging function, or writes the error message on the uart terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lr5.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 300

// ------------------------------------------------------------------ VARIABLES

static lr5_t lr5;
static log_t logger;
lr5_cmd_t response;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void lr5_process ( void )
{
    int32_t rsp_size;
    uint8_t process_cnt = 10;
    
    uint8_t check_buf_cnt;

    while( process_cnt != 0 )
    {
        rsp_size = lr5_generic_read( &lr5, lr5.rx_dat, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size > 0 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                lr5_uart_isr( &lr5 );
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
    
    log_printf( &logger, "** OPCODE : 0x%.2X\r\n", ( uint16_t ) response.cmd_code );
    
    log_printf( &logger, "** RESPONSE LENGTH : 0x%.2X\r\n", ( uint16_t ) response.cmd_length );
    
    log_printf ( &logger, "** RESPONSE : " );
    for ( rsp_idx = 0; rsp_idx < response.cmd_length; rsp_idx++ )
    {
        log_printf( &logger, "0x%.2X ", ( uint16_t ) response.cmd_data[ rsp_idx ] );
    }
    log_printf( &logger, "\r\n" );
    
    log_printf( &logger, "***********************************************\r\n" );
    log_printf( &logger, "\r\n" );
}

void wait_response ( )
{
    LR5_RETVAL resp_code;
    do
    {
        lr5_process(  );
        resp_code = lr5_response_ready( &lr5 );
    }
    while ( resp_code == LR5_RESPONSE_NOT_RECEIVED );

    resp_code = lr5_task( &lr5 );
    
    switch ( resp_code )
    {
        case LR5_CMD_RESPONSE_READY :
        {
            log_response( );
        break;
        }
        case LR5_IND_RESPONSE_READY :
        {
            log_response( );
        break;
        }
        case LR5_FRAME_HEADER_ERR :
        {
            log_printf( &logger, "** Frame Header Error **\r\n" );
            log_printf( &logger, "***********************************************\r\n" );
            log_printf( &logger, "\r\n" );
        break;
        }
        case LR5_CMD_RESPONSE_ERR :
        {
            log_printf( &logger, "** Response Code Error **\r\n" );
            log_printf( &logger, "***********************************************\r\n" );
            log_printf( &logger, "\r\n" );
        break;
        }
        case LR5_CHKSUM_ERR :
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
    lr5_cfg_t cfg;

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

    lr5_cfg_setup( &cfg );
    LR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr5_init( &lr5, &cfg );

    lr5_response_handler_set( &lr5, &make_response );
    Delay_ms( 1000 );

    lr5_reset_cmd( &lr5 );
    wait_response( );
    Delay_ms( 1000 );
    lr5_factory_reset_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** LR 5 (MIPOT 32001409) reset is done **\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms( 1000 );
}

void application_task ( void )
{
    lr5_process(  );

    log_printf( &logger, "** FW version reading...\r\n" );
    lr5_get_fw_version_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** Serial number reading...\r\n" );
    lr5_get_serial_no_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** DevEUI reading...\r\n" );
    lr5_get_dev_eui_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** Session status reading...\r\n" );
    lr5_get_session_status_cmd( &lr5 );
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
            log_printf( &logger, "Busy (LR session running).\r\n" );
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
    lr5_get_activation_status_cmd( &lr5 );
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
    lr5_set_next_dr_cmd( &lr5, LR5_SF10_125KHZ );
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
    lr5_get_ch_param_cmd( &lr5, LR5_CH_IDX_15 );
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
