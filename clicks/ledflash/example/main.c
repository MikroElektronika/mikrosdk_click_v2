/*!
 * \file 
 * \brief LED Flash Click example
 * 
 * # Description
 * This application switching on and off led flash.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO, starts write log and issues a warning.
 * 
 * ## Application Task  
 * This example demonstrates the use of LED Flash Click board by flashing
 * with LEDs when ever supercapacitor is at a full voltage.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ledflash.h"

// ------------------------------------------------------------------ VARIABLES

static ledflash_t ledflash;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ledflash_cfg_t cfg;

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

    ledflash_cfg_setup( &cfg );
    LEDFLASH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledflash_init( &ledflash, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, " LED Flash Click \r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, "/////////////////\r\n" );
    log_printf( &logger, " WARNING!!! \r\n" );
    log_printf( &logger, " DO NOT LOOK \r\n" );
    log_printf( &logger, " INTO THE LEDS, \r\n" );
    log_printf( &logger, " WHILE THAY ARE ON!!! \r\n" );
    log_printf( &logger, "/////////////////\r\n" );
    Delay_ms ( 1000 );
}

void application_task (  )
{
    uint8_t state;
    
    log_printf( &logger, " Charge Supercapacitor Enable \r\n" );
    ledflash_char_supcap_enable( &ledflash );
    Delay_ms ( 1000 );
    state = ledflash_flash_rdy_flag( &ledflash );

    if ( state == 0 )
    {
        log_printf( &logger, " Flash ON! \r\n" );
        ledflash_flash_enable( &ledflash );
    }
    else
    {
        log_printf( &logger, " Flash OFF! \r\n" );
        ledflash_flash_disable( &ledflash );
    }
    log_printf( &logger, "----------------------------------\r\n" );
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
