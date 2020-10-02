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
 * - gnsszoe_process ( ) - The general process of collecting presponce 
 *                                   that sends a module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gnsszoe.h"

#define PROCESS_COUNTER 10
#define PROCESS_RX_BUFFER_SIZE 256
#define PROCESS_PARSER_BUFFER_SIZE 1000

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

    uint8_t process_cnt = PROCESS_COUNTER;
    int32_t rsp_size;
    uint16_t rsp_cnt = 0;
    uint16_t check_buf_cnt; 

    memset( current_parser_buf, 0 , PROCESS_PARSER_BUFFER_SIZE ); 

    Delay_ms(1);
    gnsszoe_generic_read( &gnsszoe, demo_buffer, PROCESS_RX_BUFFER_SIZE );

    rsp_size = strlen( demo_buffer );

    if ( rsp_size != -1 )
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
    
    log_printf( &logger, "\r\n-----------------------\r\n", element_buf ); 
    gnsszoe_generic_parser( rsp, GNSSZOE_NEMA_GNGGA, GNSSZOE_GNGGA_LATITUDE, element_buf );
    log_printf( &logger, "Latitude:  %s \r\n", element_buf );    
    gnsszoe_generic_parser( rsp, GNSSZOE_NEMA_GNGGA, GNSSZOE_GNGGA_LONGITUDE, element_buf );
    log_printf( &logger, "Longitude:  %s \r\n", element_buf );  
    memset( element_buf, 0, sizeof( element_buf ) );
    gnsszoe_generic_parser( rsp, GNSSZOE_NEMA_GNGGA, GNSSZOE_GNGGA_ALTITUDE, element_buf );
    log_printf( &logger, "Alitude: %s \r\n", element_buf );  
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gnsszoe_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    Delay_ms(100);


    //  Click initialization.

    gnsszoe_cfg_setup( &cfg );
    GNSSZOE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gnsszoe_init( &gnsszoe, &cfg );

    Delay_ms( 500 );

    gnsszoe_module_reset( &gnsszoe );

    Delay_ms( 500 );
}

void application_task ( void )
{
    //  Task implementation.
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
