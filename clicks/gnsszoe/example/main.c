/*!
 * \file 
 * \brief Gnsszoe Click example
 * 
 * # Description
 * This example reads and processes data from GNSS ZOE clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - gnsszoe_process ( ) - The general process of collecting data the module sends.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gnsszoe.h"

#define PROCESS_RX_BUFFER_SIZE 300
#define PROCESS_PARSER_BUFFER_SIZE 600

// ------------------------------------------------------------------ VARIABLES

static gnsszoe_t gnsszoe;
static log_t logger;

uint8_t aux_char = 0;
uint32_t i = 0;


char demo_buffer[ PROCESS_RX_BUFFER_SIZE ] = { 0 };
static char current_parser_buf[ PROCESS_PARSER_BUFFER_SIZE ];

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

static void gnsszoe_process ( void )
{
    int16_t rsp_size;
    uint16_t rsp_cnt = 0;
    uint16_t check_buf_cnt; 

    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 

    gnsszoe_generic_read( &gnsszoe, demo_buffer, PROCESS_RX_BUFFER_SIZE );

    rsp_size = strlen( demo_buffer );

    if ( rsp_size > 0 )
    {
      for ( check_buf_cnt = 0; check_buf_cnt < rsp_size; check_buf_cnt++ )
            {
                if ( demo_buffer[ check_buf_cnt ] == 0 ) 
                {
                    demo_buffer[ check_buf_cnt ] = 13;
                }
            }  
           
            rsp_cnt += rsp_size;
            if ( rsp_cnt < PROCESS_PARSER_BUFFER_SIZE )
            {
                strncat( current_parser_buf, demo_buffer, rsp_size );
            }

             memset( demo_buffer, 0, PROCESS_RX_BUFFER_SIZE );
    }
    
    Delay_ms( 1000 );
}

static void parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    
    log_printf( &logger, "\r\n-----------------------\r\n" ); 
    gnsszoe_generic_parser( rsp, GNSSZOE_NEMA_GNGGA, GNSSZOE_GNGGA_LATITUDE, element_buf );
    if ( strlen( element_buf ) > 0 )
    {
        log_printf( &logger, "Latitude:  %.2s degrees, %s minutes \r\n", element_buf, &element_buf[ 2 ] );
        gnsszoe_generic_parser( rsp, GNSSZOE_NEMA_GNGGA, GNSSZOE_GNGGA_LONGITUDE, element_buf );
        log_printf( &logger, "Longitude:  %.3s degrees, %s minutes \r\n", element_buf, &element_buf[ 3 ] );
        memset( element_buf, 0, sizeof( element_buf ) );
        gnsszoe_generic_parser( rsp, GNSSZOE_NEMA_GNGGA, GNSSZOE_GNGGA_ALTITUDE, element_buf );
        log_printf( &logger, "Alitude: %s m", element_buf );  
    }
    else
    {
        log_printf( &logger, "Waiting for the position fix..." );
    }  
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gnsszoe_cfg_t cfg;

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

    gnsszoe_cfg_setup( &cfg );
    GNSSZOE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnsszoe_init( &gnsszoe, &cfg );

    gnsszoe_module_reset( &gnsszoe );

    Delay_ms( 1000 );
}

void application_task ( void )
{
    gnsszoe_process(  );
    parser_application( current_parser_buf );
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
