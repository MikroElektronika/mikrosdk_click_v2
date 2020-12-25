/*!
 * \file 
 * \brief Ble7 Click example
 * 
 * # Description
 * This example reads and processes data from BLE 7 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes peripherals, pins, UART serial interface, uart interrupt,
 * and executes the module reset. 
 * 
 * ## Application Task  
 * Allows user to recive data from another device ( using mobile bluetooth terminal )
 * 
 * ## Additional Function
 * - ble7_process ( ) - The general process of collecting presponce that sends a module.
 * - get_rsp - Catches the response bytes and sets flag when the response was ready.
 * - log_rsp - Allows user to see and check the response on the serial terminal.
 * 
 * *note:* 
 * https://docs.silabs.com/gecko-os/1/bgx/latest/commands
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ble7.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITER

static ble7_t ble7;
static log_t logger;

char clrb_buf[5] = "clrb";
char adv_buf[9] = "adv high";
char set_blvhd_buf[17] = "set bl v h d 120";
char con_count_buf[11] = "get bl c c";
char str_mode_buf[4] = "str";

char read_buf[256];

uint8_t rx_data;
uint8_t response[ 256 ];
uint8_t rsp_idx;
uint8_t rsp_check;
uint8_t log_check;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void ble7_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t check_buf_cnt;
    uint8_t process_cnt = PROCESS_COUNTER;
    
    while( process_cnt != 0 )
    {
        rsp_size = ble7_generic_read( &ble7, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );

        if ( rsp_size != -1 )
        {  
            // Validation of the received data
            for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
    
                ble7_uart_isr( &ble7, uart_rx_buffer[ check_buf_cnt ] );
            }
            
            log_printf(&logger, uart_rx_buffer );
            
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

void get_rsp ( uint8_t *rsp_dat )
{
    if ( *rsp_dat != 10 )
    {
        response[ rsp_idx ] = *rsp_dat;

        if ( ( response[ rsp_idx ] == 13 ) || ( ( response[ rsp_idx ] == ' ') && ( response[ rsp_idx - 1 ] == '>' ) ) )
        {
            if (response[ rsp_idx ] == 13 )
            {
                rsp_idx++;
                response[ rsp_idx ] = 10;
                rsp_check = 0;
            }
            else
            {
                rsp_check = 1;
            }

            log_check = BLE7_RSP_READY;
        }

        if ( rsp_idx > 100 )
        {
            rsp_check = 0;
            log_check = BLE7_RSP_READY;
        }

        rsp_idx++;
    }
    else
    {
        rsp_check = 1;
    }
}

void log_rsp ( )
{
    if ( log_check == BLE7_RSP_READY )
    {
        char log_ptr[ 251 ];
        uint8_t rx_cnt = 0;

        while ( rx_cnt < rsp_idx )
        {
            log_ptr[ rx_cnt ] = response[ rx_cnt ];
            rx_cnt++;
        }

        log_ptr[ rx_cnt ] = BLE7_END_BUFF;
        rsp_idx = 0;
        log_check = BLE7_RSP_NOT_READY;
        log_printf( &logger, "%s", log_ptr );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void ble7_device_config ( )
{
    clrb_buf[4] = '\r';
    adv_buf[8] = '\r';
    set_blvhd_buf[16] = '\r';
    con_count_buf[10] = '\r';
    str_mode_buf[3] = '\r';
    
    ble7_generic_write ( &ble7, clrb_buf, 5 );
    Delay_ms( 500 );
    ble7_process(  );
    
    ble7_generic_write ( &ble7, set_blvhd_buf, 17 );
    Delay_ms( 200 );
    ble7_process(  );
    
    ble7_generic_write ( &ble7, adv_buf, 9 );
    Delay_ms( 200 );
    ble7_process(  );
    
    log_printf( &logger, "\nConnect to a device...\n" );
    
    Delay_ms( 10000 );
    
    ble7_generic_write ( &ble7, con_count_buf, 11 );
    Delay_ms( 200 );
    ble7_process(  );
    
    ble7_generic_write ( &ble7, str_mode_buf, 4 );
    Delay_ms( 200 );
    ble7_process(  );
}

void sending_mode ( )
{
    if ( strstr( response, "STREAM_MODE" ) != NULL )
    {
        ble7_send_command ( &ble7, "MikroE" );
    }
    else
    {
        // COMMAND_MODE
        ble7_send_command ( &ble7, "send MikroE" );
    }
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble7_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ble7_cfg_setup( &cfg );
    BLE7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble7_init( &ble7, &cfg );
    
    //Delay_ms( 200 );

    ble7_response_handler_set(  &ble7, &get_rsp );
    Delay_ms( 200 );

    ble7_reset( &ble7 );

    rsp_idx = 0;
    rsp_check = 0;
    log_check = BLE7_RSP_NOT_READY;
    
    ble7_device_config();
    
    log_printf(&logger, "---- Application Init done... ----\n");
}



void application_task ( void )
{
    ble7_send_command ( &ble7, "MikroE" );
    ble7_process(  );
    
    log_rsp( );
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
