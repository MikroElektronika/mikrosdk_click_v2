/*!
 * \file 
 * \brief Big7Seg Click example
 * 
 * # Description
 * This application sets seven-segment leds on the display.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Driver initializaion and turning on the display
 * by setting PWM pin to logic 1 and prepare to communcation via SPI.
 * 
 * ## Application Task  
 * This example shows functionality of the BIG 7-SEG R click,
 * shows number or character on display.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "big7seg.h"

// ------------------------------------------------------------------ VARIABLES

static big7seg_t big7seg;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    big7seg_cfg_t cfg;

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

    big7seg_cfg_setup( &cfg );
    BIG7SEG_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    big7seg_init( &big7seg, &cfg );

    big7seg_set7seg( &big7seg );
    Delay_100ms( );
}

void application_task ( )
{
    uint8_t counter;

    big7seg_reset7seg( &big7seg );
    big7seg_display_on( &big7seg );
    Delay_1sec( );

    big7seg_write_data( &big7seg, 0x40 );
    Delay_1sec( );
    big7seg_write_data_character( &big7seg, 'B' );
    Delay_1sec( );
    big7seg_write_data_character( &big7seg, 'I' );
    Delay_1sec( );
    big7seg_write_data_character( &big7seg, 'G' );
    Delay_1sec( );
    big7seg_write_data( &big7seg, 0x08 );
    Delay_1sec( );
    big7seg_write_data_number( &big7seg, 7 );
    Delay_1sec( );
    big7seg_write_data( &big7seg, 0x40 );
    Delay_1sec( );
    big7seg_write_data_character( &big7seg, 'S' );
    Delay_1sec( );
    big7seg_write_data_character( &big7seg, 'E' );
    Delay_1sec( );
    big7seg_write_data_character( &big7seg, 'G' );
    Delay_1sec( );
    
    big7seg_write_data( &big7seg, 0x00 );
    Delay_1sec( );
    for ( counter = 65; counter < 91; counter ++ )
    {
        big7seg_write_data_character(  &big7seg, counter );
        Delay_1sec( );
    }

    big7seg_display_off( &big7seg );
    Delay_1sec( );
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
