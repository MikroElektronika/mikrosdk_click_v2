/*!
 * \file 
 * \brief DualEE Click example
 * 
 * # Description
 * This application writes data in memory and reads data from memory
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device init
 * 
 * ## Application Task  
 * Reads your command and then execute it
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dualee.h"

// ------------------------------------------------------------------ VARIABLES

static dualee_t dualee;
static log_t logger;

static uint32_t page_address = 0x00000000;
static uint8_t write_data[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dualee_cfg_t cfg;

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

    dualee_cfg_setup( &cfg );
    DUALEE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dualee_init( &dualee, &cfg );

    log_printf( &logger, "*********** APPLICATION INIT ***********\r\n" );
    Delay_ms( 100 );
}

void application_task ( )
{
    uint8_t write_dual;
    uint8_t read_dual;
    char demo_text[ 255 ];

    log_printf( &logger, "Writing data [MikroE]....\r\n" );
    write_dual = dualee_write( &dualee, page_address, write_data, 7 );
  
    if ( write_dual == DUALEE_ERROR_RW )
    {
        log_printf( &logger, "Error writing data!!!\r\n" );
        Delay_ms( 1000 );
        return;
    }
    Delay_ms( 100 );

    log_printf( &logger, "Reading data...\r\n" );
    read_dual = dualee_read( &dualee, page_address, demo_text, 7 );

    if ( read_dual == 0 )
    {
        log_printf( &logger, "Error reading data!!!\r\n" );
        Delay_ms( 1000 );
        return;
    }
    Delay_ms( 100 );
    log_printf( &logger, "Data from read page is: %s \r\n", demo_text );
    
    log_printf( &logger, "__________________________________\r\n" );
    Delay_ms( 1000 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}


// ------------------------------------------------------------------------ END
