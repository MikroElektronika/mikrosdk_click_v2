/*!
 * \file 
 * \brief Audio Xover Click example
 * 
 * # Description
 * This example demonstrates the use of the Audio Xover Click board. 
 * The Click is an analog active crossover solution for two-way loudspeakers. 
 * The primary purpose of the crossover circuit in a loudspeaker is to split 
 * an incoming audio signal into frequency bands that are passed to 
 * the speaker best suited.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes the driver and makes an initial log.
 * 
 * ## Application Task  
 * This function enables and disables the Click board every 10 seconds,
 * and logs an appropriate message on the USB UART.
 * 
 * @note
 * The hardware revision v100 of the Click board works only with MCUs that operates
 * at 5V operating voltage level.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioxover.h"

// ------------------------------------------------------------------ VARIABLES

static audioxover_t audioxover;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioxover_cfg_t cfg;

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

    audioxover_cfg_setup( &cfg );
    AUDIOXOVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioxover_init( &audioxover, &cfg );
}

void application_task ( void )
{
    log_printf( &logger, " * Switch: ON *\r\n" );
    audioxover_power_on ( &audioxover );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " * Switch: OFF *\r\n" );
    audioxover_shut_down ( &audioxover );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
