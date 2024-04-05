/*!
 * @file main.c
 * @brief Expand8 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Expand 8 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - SPI, also write log.
 *
 * ## Application Task
 * This example is working by toggling each of 10 available ports every 1 second.
 * Results are being sent to the Uart Terminal where you can track their changes.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "expand8.h"

static expand8_t expand8;
static log_t logger;
uint8_t select_port;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand8_cfg_t expand8_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    expand8_cfg_setup( &expand8_cfg );
    EXPAND8_MAP_MIKROBUS( expand8_cfg, MIKROBUS_1 );
    err_t init_flag  = expand8_init( &expand8, &expand8_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    select_port = EXPAND8_ADDR_OUT_LVL_PORT_P0;
    Delay_ms ( 100 );
}

void application_task ( void )
{
    expand8_set_port( &expand8, select_port, EXPAND8_SET_LOW_IMPEDANCE );
    
    log_printf( &logger, "     Port P%d - ON\r\n", ( uint16_t ) select_port );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    
    expand8_set_port( &expand8, select_port, EXPAND8_SET_HIGH_IMPEDANCE );
    
    log_printf( &logger, "     Port P%d - OFF\r\n", ( uint16_t ) select_port );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    select_port++;

    if ( select_port > EXPAND8_ADDR_OUT_LVL_PORT_P9 ) 
    {
        select_port = EXPAND8_ADDR_OUT_LVL_PORT_P0;
    }
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
