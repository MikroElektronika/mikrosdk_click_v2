/*!
 * @file main.c
 * @brief RC Pulse Click example
 *
 * # Description
 * This example demonstrates the use of the RC Pulse Click board for
 * generating pulse signals with a specific duration. The application 
 * continuously changes the wiper position of a digital potentiometer AD5235 
 * and generates a trigger for the dual retriggerable monostable multivibrator 
 * TPUL2T122A which generates a pulse signal with a duration determined by 
 * the set wiper position.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Periodically sweeps the wiper position back and forth across the full scale
 * range (0 to 1023) in steps of 33. For each step it reads the wiper back,
 * logs the set and read values, and fires a trigger for generating a pulse 
 * signal with a duration determined by the set wiper position.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "rcpulse.h"

#ifndef MIKROBUS_POSITION_RCPULSE
    #define MIKROBUS_POSITION_RCPULSE MIKROBUS_1
#endif

#define RCPULSE_DEMO_CHANNEL      RCPULSE_CHANNEL_1
#define RCPULSE_DEMO_WIPER_STEP   33

static rcpulse_t rcpulse;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rcpulse_cfg_t rcpulse_cfg;  /**< Click config object. */

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
    rcpulse_cfg_setup( &rcpulse_cfg );
    RCPULSE_MAP_MIKROBUS( rcpulse_cfg, MIKROBUS_POSITION_RCPULSE );
    if ( SPI_MASTER_ERROR == rcpulse_init( &rcpulse, &rcpulse_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RCPULSE_ERROR == rcpulse_default_cfg ( &rcpulse ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static int16_t wiper_pos = RCPULSE_WIPER_MIN;
    static int16_t wiper_step = RCPULSE_DEMO_WIPER_STEP;
    uint16_t wiper_read = 0;

    if ( RCPULSE_OK == rcpulse_set_wiper( &rcpulse, RCPULSE_DEMO_CHANNEL, ( uint16_t ) wiper_pos ) )
    {
        if ( RCPULSE_OK == rcpulse_get_wiper( &rcpulse, RCPULSE_DEMO_CHANNEL, &wiper_read ) )
        {
            log_printf( &logger, " Wiper set: %d | read: %u\r\n", wiper_pos, wiper_read );
            rcpulse_trigger( &rcpulse );
            log_printf( &logger, " Pulse triggered\r\n" );
            log_printf( &logger, " -------------------------------\r\n" );
        }
        else
        {
            log_error( &logger, " Failed to get wiper." );
        }
    }
    else
    {
        log_error( &logger, " Failed to set wiper." );
    }

    wiper_pos += wiper_step;
    if ( ( RCPULSE_WIPER_MAX < wiper_pos ) || ( RCPULSE_WIPER_MIN > wiper_pos ) )
    {
        wiper_step = -wiper_step;
        wiper_pos += wiper_step;
        wiper_pos += wiper_step;
    }

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
