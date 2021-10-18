/*!
 * \file 
 * \brief Mic24045 Click example
 * 
 * # Description
 * This example demonstrates the use of MIC24045 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the voltage output.
 * 
 * ## Application Task  
 * Changes the voltage output every 2 seconds and displays the current set value
 * on the USB UART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic24045.h"

// ------------------------------------------------------------------ VARIABLES

static mic24045_t mic24045;
static log_t logger;
static float current_voltage;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic24045_cfg_t cfg;

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

    mic24045_cfg_setup( &cfg );
    MIC24045_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic24045_init( &mic24045, &cfg );
    
    mic24045_enable( &mic24045 );
    log_printf( &logger, " Output enabled!\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    for ( uint16_t cnt = MIC24045_MIN_VOUT_DEC; cnt <= MIC24045_MAX_VOUT_DEC; cnt += 15 )
    {
        mic24045_set_vout_decimal( &mic24045, cnt );
        Delay_ms( 500 );
        current_voltage = mic24045_get_vout( &mic24045 );
    
        log_printf( &logger, " VOUT:    ~%.3f V\r\n", current_voltage );
        log_printf( &logger, "------------------\r\n" );
        Delay_ms( 1500 );
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
