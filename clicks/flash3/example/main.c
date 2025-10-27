/*!
 * \file 
 * \brief Flash3 Click example
 * 
 * # Description
 * This applicaion adding more flash memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes device, Flash 3 Click board and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the Flash 3 Click by
   writing into memory array of a Flash 3 Click board and reading same data from memory array.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "flash3.h"

// ------------------------------------------------------------------ VARIABLES

static flash3_t flash3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    flash3_cfg_t cfg;

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

    flash3_cfg_setup( &cfg );
    FLASH3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    flash3_init( &flash3, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "  Flash  3  Click  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    flash3_setting( &flash3 );
    Delay_ms ( 100 );
    log_printf( &logger, "   Initialized     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}

void application_task ( void )
{
    char val_in[ 8 ] = { 0x4D, 0x49, 0x4B, 0x52, 0x4F, 0x45, 0x00 };
    char val_out[ 8 ] = { 0 };

    log_printf( &logger, "\r\n ____________________ \r\n" );
    log_printf( &logger, "Begin demonstration! \r\n\r\n" );
    
    flash3_write( &flash3, 0x000000, &val_in[ 0 ], 6 );
    log_printf( &logger, "Written : %s\r\n", val_in );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );

    flash3_normal_read( &flash3, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read : %s\r\n", val_out );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );

    flash3_sector_erase( &flash3, 0x000000 );
    log_printf( &logger, "Erased!\r\n" );
    log_printf( &logger, "------------------ \r\n"  );
    Delay_ms ( 500 );

    flash3_fast_read( &flash3, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read : %s\r\n", val_out );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );

    log_printf( &logger, "Demonstration over!" );
    log_printf( &logger, "\r\n ___________________ \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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


// ------------------------------------------------------------------------ END
