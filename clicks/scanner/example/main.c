/*!
 * \file 
 * \brief Scanner Click example
 * 
 * # Description
 * This example reads data from Scanner clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver an start up module.
 * 
 * ## Application Task  
 * Reads the received data.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "scanner.h"

// ------------------------------------------------------------------ VARIABLES

static scanner_t scanner;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void log_write_func ( uint8_t *str_buf, uint8_t str_type )
{
    char *temp_buf = str_buf;
    
    if ( str_type == 0 || str_type == 1  )
    {
        log_printf( &logger, temp_buf );
    }
    else if ( str_type == 2 )
    {
        log_printf( &logger, temp_buf ); 
        log_printf( &logger, "\r\n" );
    }
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    scanner_cfg_t cfg;

    uint8_t data_cnt = 0;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "--->>> APP INIT <<<---\r\n" );

    //  Click initialization.

    scanner_cfg_setup( &cfg );
    SCANNER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    scanner_init( &scanner, &cfg );

    Delay_ms( 300 );

    scanner_startup( &scanner );
    Delay_ms( 100 );
    
    scanner_serial_write_reg( &scanner, SCANNER_REG_MODE, SCANNER_DATA_NORMAL_MODE );
    
    for ( data_cnt = 0; data_cnt < 3; )
    {
        scanner_serial_write_reg( &scanner, SCANNER_REG_OFFSET_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
        scanner_serial_write_reg( &scanner, SCANNER_REG_GAIN_LEFT + ( 2 * data_cnt ), 25 );
        data_cnt++;
    }
    log_printf( &logger, "--->>> APP TASK <<<--- \r\n" );
}

void application_task ( void )
{
    scanner_pixel_log( &scanner, &log_write_func );
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
