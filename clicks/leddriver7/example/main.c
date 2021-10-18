/*!
 * \file 
 * \brief LedDriver7 Click example
 * 
 * # Description
 * This application is portable lighting and rechargeable flashlights.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver and writes an initial log.
 * 
 * ## Application Task  
 * This example demonstrates the use of LED Driver 7 Click board,
 * by cycling wiper positions of AD5171 Digital Potentiometer.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "leddriver7.h"

// ------------------------------------------------------------------ VARIABLES

static leddriver7_t leddriver7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver7_cfg_t cfg;

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

    leddriver7_cfg_setup( &cfg );
    LEDDRIVER7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver7_init( &leddriver7, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, " LED Driver 7 click  \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
}

void application_task ( void )
{
    uint8_t n_pos = 0;
    uint8_t pos_num = 64;

    for ( n_pos = 12; n_pos < pos_num; n_pos++ )
    {
        leddriver7_generic_write( &leddriver7, LEDDRIVER7_NORM_OP_MODE, &n_pos, 1 );
        log_printf( &logger, "Position : %d \r\n", (uint16_t)n_pos );
        Delay_ms( 500 );
    }
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
