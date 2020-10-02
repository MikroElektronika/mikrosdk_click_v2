/*!
 * \file 
 * \brief Spirit Click example
 * 
 * # Description
 * This example reads and processes data from Spirit clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and power, reset and set module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * ## Additional Function
 * - spirit_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spirit.h"
#include "string.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 500

#define DATA_TO_BE_SENT   "--MikroElektronika--"

// ------------------------------------------------------------------ VARIABLES

#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITER

static spirit_t spirit;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void spirit_process ( void )
{
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
    uint8_t process_cnt = PROCESS_COUNTER;

    while( process_cnt != 0 )
    {
        rsp_size = spirit_generic_read( &spirit, &uart_rx_buffer, PROCESS_RX_BUFFER_SIZE );
        
        if ( rsp_size != -1 )
        {  
            log_printf( &logger, "%s", uart_rx_buffer );
            
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

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spirit_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    spirit_cfg_setup( &cfg );
    SPIRIT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit_init( &spirit, &cfg );

    spirit_power_module( &spirit, SPIRIT_MODULE_WAKE_UP );
    spirit_reset( &spirit );
    spirit_set_mode( &spirit, SPIRIT_OPERATING_MODE );
    log_printf( &logger, "---- SPIRIT POWER ON ---- \r\n" );

    Delay_ms( 1500 );

    spirit_send_command( &spirit, SPIRIT_CMD_READ_MODULE_VERSION );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_WRITE_CFG_TXRX_LED );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_STORE_CURRENT_CONFIG );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_READ_ALL_CONFIG_REG );
    spirit_process( );
    spirit_send_command( &spirit, SPIRIT_CMD_ENTER_OPERATING_MODE );
    spirit_process( );

    Delay_ms( 1000 );

    log_printf( &logger, "---- SPIRIT START TASK ---- \r\n" );
}

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    spirit_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITER 
    spirit_send_command( &spirit, DATA_TO_BE_SENT );
    spirit_process( );
    Delay_ms( 1000 );
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
