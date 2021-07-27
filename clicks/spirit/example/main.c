/*!
 * @file main.c
 * @brief SPIRIT Click Example.
 *
 * # Description
 * This example reads and processes data from SPIRIT click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data or sends the desired message 
 * every 2 seconds.
 *
 * ## Additional Function
 * - static err_t spirit_process ( void )
 *
 * @author Jelena Milosavljevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spirit.h"

#define PROCESS_BUFFER_SIZE 500
#define PROCESS_COUNTER        20

#define TEXT_TO_SEND           "MikroE - SPIRIT click board\r\n"

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITTER

static spirit_t spirit;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief SPIRIT 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static void spirit_process ( void );

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
    Delay_ms( 1000 );

    log_info( &logger, "---- Configuring the module ----" );
    spirit_power_module( &spirit, SPIRIT_MODULE_WAKE_UP );
    spirit_reset( &spirit );
    spirit_set_mode( &spirit, SPIRIT_OPERATING_MODE );
    Delay_ms( 1000 );
    log_printf( &logger, "COMMAND MODE\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_ENTER_COMMAND_MODE );
    spirit_process( );
    log_printf( &logger, "FIRMWARE VERSION\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_READ_MODULE_VERSION );
    spirit_process( );
    log_printf( &logger, "TXRX LED - OPEN DRAIN OUTPUT\r\n" );
    spirit_send_cmd_with_parameter( &spirit, SPIRIT_CMD_CFG_TXRX_LED, SPIRIT_PCFG_TXRXLED_OPEN_DRAIN );
    spirit_process( );
    log_printf( &logger, "STORE CONFIG\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_STORE_CURRENT_CONFIG );
    spirit_process( );
    log_printf( &logger, "OPERATING MODE\r\n" );
    spirit_send_cmd( &spirit, SPIRIT_CMD_ENTER_OPERATING_MODE );
    spirit_process( );
    log_info( &logger, "---- The module has been configured ----" );
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif 
    Delay_ms( 1000 );
}

void application_task ( void ) {
    #ifdef DEMO_APP_RECEIVER
    spirit_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITTER 
    spirit_generic_write( &spirit, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms( 2000 );
#endif
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

static void spirit_process ( void ) {
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_BUFFER_SIZE ] = { 0 };
    uint8_t process_cnt = PROCESS_COUNTER;

    while( process_cnt != 0 )
    {
        rsp_size = spirit_generic_read( &spirit, &uart_rx_buffer, PROCESS_BUFFER_SIZE );
        
        if ( rsp_size > 0 )
        {  
            for ( uint8_t cnt = 0; cnt < rsp_size; cnt++ )
            {
                log_printf( &logger, "%c", uart_rx_buffer[ cnt ] );
                if ( uart_rx_buffer[ cnt ] == '\n' )
                {
                    log_printf( &logger, "-----------------------------\r\n" );
                }
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

// ------------------------------------------------------------------------ END
