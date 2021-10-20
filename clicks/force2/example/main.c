/*!
 * \file 
 * \brief Force2 Click example
 * 
 * # Description
 * This application is used to measure the pressure force.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes ADC driver, sets ADC channel and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the 
 * capabilities of the Force 2 click by taking measurements from
 * the device and displaying it via USART terminal.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "force2.h"

// ------------------------------------------------------------------ VARIABLES

static force2_t force2;
static log_t logger;

int32_t force2_val_conv 
( int32_t x, int32_t in_max, int32_t out_min, int32_t out_max )
{
    int32_t in_min = 0;

    return x * ( out_max - out_min ) / in_max + out_min;
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    force2_cfg_t cfg;

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

    force2_cfg_setup( &cfg );
    FORCE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force2_init( &force2, &cfg );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force 2 click   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    int16_t disp_val;
    force2_data_t tmp;
    
    //  Task implementation.
    
    tmp = force2_generic_read ( &force2 );
    disp_val = force2_val_conv( ( int32_t )tmp, 1024, 15, 0 );

    log_printf( &logger, "ADC: %u\r\n", tmp );
    log_printf( &logger, "Force: %d N\r\n", disp_val );
    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms( 500 );
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
