/*!
 * \file 
 * \brief Mram2 Click example
 * 
 * # Description
 * This example demonstrates the use of MRAM 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, sets the write protect and disables the hold signal.
 * 
 * ## Application Task  
 * Writes "MikroE" into the first 6 memory locations, and then reads it back 
 * and displays it to the USB UART approximately every 5 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mram2.h"

// ------------------------------------------------------------------ VARIABLES

static mram2_t mram2;
static log_t logger;

char val_in[ 7 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 0 };
char val_out[ 7 ] = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mram2_cfg_t cfg;

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

    mram2_cfg_setup( &cfg );
    MRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mram2_init( &mram2, &cfg );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   MRAM 2 Click     \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    mram2_write_protect( &mram2, MRAM2_WP_ENABLE );
    mram2_hold( &mram2, MRAM2_HLD_DISABLE );
    log_printf( &logger, "   Initialized      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    mram2_wren( &mram2 );
    log_printf( &logger, "Write enabled!\r\n" );
    Delay_ms( 100 );
    log_printf( &logger, "Writing \"%s\" to memory...\r\n", val_in );
    mram2_write( &mram2, 0x000000, &val_in[ 0 ], 6 );
    Delay_ms( 100 );
    mram2_wrdi ( &mram2 );
    log_printf( &logger, "Write disabled!\r\n" );
    Delay_ms( 100 );
    mram2_read ( &mram2, 0x000000, &val_out[ 0 ], 6 );
    log_printf( &logger, "Read data : %s\r\n", val_out );
    
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms( 5000 );
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
