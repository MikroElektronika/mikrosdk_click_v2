/*!
 * \file 
 * \brief Spectral2 Click example
 * 
 * # Description
 * This application enables usage of multispectral color sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init
 * Driver initialize, reset module and configuration measurement
 * 
 * ## Application Task
 * Reads the brightness value with R, G, B, I, O and V filter, every 1 second,
 * and logs on to USBUART.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spectral2.h"

// ------------------------------------------------------------------ VARIABLES

static spectral2_t spectral2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    //  Click initialization.

    spectral2_cfg_setup( &cfg );
    SPECTRAL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    if ( spectral2_init( &spectral2, &cfg ) == SPECTRAL2_INIT_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );

    spectral2_reset( &spectral2 );
    spectral2_default_cfg( &spectral2 );

    Delay_ms( 1000 );
    log_info( &logger, "---- Application Running... ----\n" );
}

void application_task ( void )
{
    log_printf( &logger, "----------------------------------\r\n" );

    int16_t v_dat = spectral2_get_data( &spectral2, SPECTRAL2_DATA_V );
    log_printf( &logger, " -- V ( Violet data ) : %d\r\n", v_dat );

    int16_t b_dat = spectral2_get_data( &spectral2, SPECTRAL2_DATA_B );
    log_printf( &logger, " -- B ( Blue data ) : %d\r\n", b_dat );

    int16_t g_dat = spectral2_get_data( &spectral2, SPECTRAL2_DATA_G );
    log_printf( &logger, " -- G ( Green data ) : %d\r\n", g_dat );

    int16_t y_dat = spectral2_get_data( &spectral2, SPECTRAL2_DATA_Y );
    log_printf( &logger, " -- Y ( Yellow data ) : %d\r\n", y_dat );

    int16_t o_dat = spectral2_get_data( &spectral2, SPECTRAL2_DATA_O );
    log_printf( &logger, " -- O ( Orange data ) : %d\r\n", o_dat );

    int16_t r_dat = spectral2_get_data( &spectral2, SPECTRAL2_DATA_R );
    log_printf( &logger, " -- R ( Red data ) : %d\r\n", r_dat );

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
