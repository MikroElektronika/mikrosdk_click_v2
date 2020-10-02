/*!
 * \file 
 * \brief HeartRate9 Click example
 * 
 * # Description
 * This application measures heart rate.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init and logs instructions on commands and format of response data
 * 
 * ## Application Task  
 * Waits for valid user input and executes functions based on set of valid commands
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate9.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate9_t heartrate9;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


static void heartrate9_process ( void )
{
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    
    char uart_rx_buffer[ 1500 ] = { 0 };
    uint8_t check_buf_cnt = 4;
    uint8_t process_cnt = 3;
    
    while( process_cnt != 0 )
    {
        rsp_size = heartrate9_generic_read( &heartrate9, &uart_rx_buffer, 1500 );

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
            
            log_printf( &logger, "%s", uart_rx_buffer );
            
            // Storages data in parser buffer
            rsp_cnt += rsp_size;
            
            // Clear RX buffer
            memset( uart_rx_buffer, 0, 1500 );
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
    heartrate9_cfg_t cfg;

    //  Logger initialization.
    
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    heartrate9_cfg_setup( &cfg );
    HEARTRATE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate9_init( &heartrate9, &cfg );
}

void application_task ( void )
{
    heartrate9_process( );
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
