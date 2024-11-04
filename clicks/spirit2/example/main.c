/*!
 * @file main.c
 * @brief SPIRIT 2 Click Example.
 *
 * # Description
 * This example reads and processes data from SPIRIT 2 Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board.
 *
 * ## Application Task
 * Depending on the selected mode, it reads all the received data or sends the desired message 
 * every 2 seconds.
 *
 * ## Additional Function
 * - static err_t spirit2_process ( void )
 *
 * @author Jelena Milosavljevic
 *
 */

// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spirit2.h"

#define PROCESS_BUFFER_SIZE    500
#define PROCESS_COUNTER        20

#define TEXT_TO_SEND           "MikroE - SPIRIT 2 Click board\r\n"

#define DEMO_APP_RECEIVER
//#define DEMO_APP_TRANSMITTER

static spirit2_t spirit2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief SPIRIT2 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static void spirit2_process ( void );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) 
{
    log_cfg_t log_cfg;
    spirit2_cfg_t cfg;

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

    spirit2_cfg_setup( &cfg );
    SPIRIT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spirit2_init( &spirit2, &cfg );
    Delay_ms ( 1000 );

    log_info( &logger, "---- Configuring the module ----" );
    spirit2_power_module( &spirit2, SPIRIT2_MODULE_WAKE_UP );
    spirit2_reset( &spirit2 );
    spirit2_set_mode( &spirit2, SPIRIT2_OPERATING_MODE );
    Delay_ms ( 1000 );
    log_printf( &logger, "COMMAND MODE\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_ENTER_COMMAND_MODE );
    spirit2_process( );
    log_printf( &logger, "FIRMWARE VERSION\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_READ_MODULE_VERSION );
    spirit2_process( );
    log_printf( &logger, "TXRX LED - OPEN DRAIN OUTPUT\r\n" );
    spirit2_send_cmd_with_parameter( &spirit2, SPIRIT2_CMD_CFG_TXRX_LED, SPIRIT2_PCFG_TXRXLED_OPEN_DRAIN );
    spirit2_process( );
    log_printf( &logger, "STORE CONFIG\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_STORE_CURRENT_CONFIG );
    spirit2_process( );
    log_printf( &logger, "OPERATING MODE\r\n" );
    spirit2_send_cmd( &spirit2, SPIRIT2_CMD_ENTER_OPERATING_MODE );
    spirit2_process( );
    log_info( &logger, "---- The module has been configured ----" );
#ifdef DEMO_APP_RECEIVER
    log_info( &logger, "---- RECEIVER MODE ----" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- TRANSMITTER MODE ----" );
#endif 
    Delay_ms ( 1000 );
}

void application_task ( void ) {
#ifdef DEMO_APP_RECEIVER
    spirit2_process( );
#endif   
    
#ifdef DEMO_APP_TRANSMITTER 
    spirit2_generic_write( &spirit2, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_info( &logger, "---- The message has been sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void spirit2_process ( void ) {
    int32_t rsp_size;
    
    char uart_rx_buffer[ PROCESS_BUFFER_SIZE ] = { 0 };
    uint8_t process_cnt = PROCESS_COUNTER;

    while( process_cnt != 0 ) {
       
        rsp_size = spirit2_generic_read( &spirit2, &uart_rx_buffer, PROCESS_BUFFER_SIZE );
        
        if ( rsp_size > 0 ) {  
            
            for ( uint8_t cnt = 0; cnt < rsp_size; cnt++ ) {
                
                log_printf( &logger, "%c", uart_rx_buffer[ cnt ] );
                if ( uart_rx_buffer[ cnt ] == '\n' ) {
                   
                    log_printf( &logger, "-----------------------------\r\n" );
                }
            }
        } 
        else {
           
            process_cnt--;
            
            // Process delay 
            Delay_ms ( 100 );
        }
    }
}

// ------------------------------------------------------------------------ END
