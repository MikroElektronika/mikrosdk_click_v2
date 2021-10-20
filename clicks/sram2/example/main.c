/*!
 * \file 
 * \brief Sram2 Click example
 * 
 * # Description
 * This demo application writes and reads from memory.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver init.
 * 
 * ## Application Task  
 * Writes and then reads data from memory.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "sram2.h"

// ------------------------------------------------------------------ VARIABLES

static sram2_t sram2;
static log_t logger;

static char rx_data;
static uint8_t message_data[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };
static uint16_t memory_addr = 0x1234;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    sram2_cfg_t cfg;

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

    sram2_cfg_setup( &cfg );
    SRAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    sram2_init( &sram2, &cfg );
    
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t cnt;
     
    log_printf( &logger, ">> Write data [ MikroE ] to memory. \r\n" );

    sram2_write_protect( &sram2, SRAM2_WR_ENABLE );
    Delay_ms( 10 );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        sram2_generic_write( &sram2, memory_addr + cnt, message_data[ cnt ] );
        Delay_ms( 10 );
    }
    Delay_ms( 1000 );
    sram2_write_protect( &sram2, SRAM2_WR_DISABLE );
    Delay_ms( 10 );

    log_printf( &logger, ">> Read data from memory. Data : " );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        sram2_generic_read( &sram2, memory_addr + cnt, &rx_data );
        Delay_ms( 10 );
        log_printf( &logger, " %c ", rx_data );
        Delay_ms( 100 );
    }
    log_printf( &logger, "  \r\n" );
    log_printf( &logger, "-------------------------------- \r\n" );
    Delay_ms( 2000 );
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
