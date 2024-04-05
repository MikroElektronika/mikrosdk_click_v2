/*!
 * \file 
 * \brief FRAM2 Click example
 * 
 * # Description
 * This example performs write & read operation to certain register.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initiazlize device and enable write operation.
 * 
 * ## Application Task  
 * Write value 42 to register 0x10 and check if operation was done properly.
 * 
 * *note:* 
 * data_to_write variable is declared as const, so compiler may warn user 
 * about 'suspisuous pointer conversion'. Note it is the case only with this
 * code snippet but user has freedom to use driver functions as he wishes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "fram2.h"
#include <string.h>

// ------------------------------------------------------------------ VARIABLES

static fram2_t fram2;
static log_t logger;

static uint8_t data_to_write[ 3 ] = { '4', '2', 0 };
static uint8_t read_buf [ 32 ];
static uint32_t test_addr;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    fram2_cfg_t cfg;

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

    fram2_cfg_setup( &cfg );
    FRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fram2_init( &fram2, &cfg );
    fram2_default_cfg ( &fram2 );
}

void application_task ( void )
{
    log_info( &logger, "Writing value 42 into register 0x10..." );  
    test_addr = 0x0010;  
    fram2_write( &fram2, test_addr, data_to_write, 3 );
    Delay_ms ( 200 );

    log_info( &logger, "Reading from register 0x10..." );
    memset( read_buf, 0, 32 );
    Delay_ms ( 500 );
    
    fram2_read( &fram2, test_addr, read_buf, 3 );
    log_printf ( &logger, "Read value: %s\r\n\n", read_buf );
    Delay_ms ( 500 );
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
