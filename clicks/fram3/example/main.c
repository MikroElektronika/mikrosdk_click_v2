/*!
 * \file 
 * \brief FRAM3 Click example
 * 
 * # Description
 * This application writes data in memmory and reads data from memmory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device init
 * 
 * ## Application Task  
 * Writes and then reads data from memory
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fram3.h"

// ------------------------------------------------------------------ VARIABLES

static fram3_t fram3;
static log_t logger;

static char write_data[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fram3_cfg_t cfg;

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

    fram3_cfg_setup( &cfg );
    FRAM3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram3_init( &fram3, &cfg );
}

void application_task (  )
{
    char read_data[ 7 ];
    uint8_t cnt;
    uint8_t status_check;

    log_printf( &logger, " - Writing...  \r\n" );
    Delay_ms( 500 );
    status_check = fram3_write_free_access_memory( &fram3, 0x00, &write_data[ 0 ], 7 );
    if ( status_check == FRAM3_ERROR )
    {
        log_printf( &logger, " - ERROR WRITING!!! \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, " - Reading... \r\n" );
    Delay_ms( 500 );
    status_check = fram3_read_free_access_memory( &fram3, 0x00, &read_data[ 0 ], 7 );
    if ( status_check == FRAM3_ERROR )
    {
        log_printf( &logger, " - ERROR READING!!! \r\n" );
        for ( ; ; );
    }

    for ( cnt = 0; cnt < 7; cnt++ )
    {
        log_printf( &logger, " %c ", read_data[ cnt ] );
        Delay_ms( 100 );
    }
    log_printf( &logger, " \r\n " );
    Delay_ms( 1000 );
    log_printf( &logger, "__________________________\r\n " );
    Delay_ms( 500 );
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
