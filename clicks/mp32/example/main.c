/*!
 * \file 
 * \brief Mp32 Click example
 * 
 * # Description
 * This example demonstates the use of MP3 2 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and enables the Click board.
 * Then sets the device to play songs from SD Card, and after that sets volume, and equalizer.
 * 
 * ## Application Task  
 * Demonstrates the use of play, play next, and pause modes.
 * Each step will be logged on the USB UART where you can track the program flow.
 * 
 * @note
 * A valid microSD Card that contains at least one mp3 sound on it needs to be 
 * inserted into the Click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mp32.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

static mp32_t mp32;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mp32_cfg_t cfg;

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

    mp32_cfg_setup( &cfg );
    MP32_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mp32_init( &mp32, &cfg );

    Delay_ms ( 500 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "       MP3 2 Click       \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_100ms( );

    mp32_hw_reset( &mp32 );
    Delay_ms ( 100 );
    
    mp32_set_device( &mp32, MP32_SDCARD );
    mp32_set_volume( &mp32, 50 );
    mp32_set_eq( &mp32, MP32_EQ_NORMAL );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    log_printf( &logger, " >>> Play\r\n" );
    mp32_play_mode( &mp32 );
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
    log_printf( &logger, " >>> Next song\r\n" );
    mp32_play_next( &mp32 );
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
    log_printf( &logger, " >>> Pause\r\n" );
    mp32_pause_mode( &mp32 );
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
