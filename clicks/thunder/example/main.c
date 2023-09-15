/*!
 * @file 
 * @brief Thunder Click example
 * 
 * # Description
 * This application detects the presence and proximity of potentially 
 * lightning activity and provides estimated distance to the center of the storm. 
 * It can also provide information on the noise level.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes SPI driver and performs the reset command and RCO calibrate command.
 * Also configures the device for working properly.
 * 
 * ## Application Task  
 * Checks if the interrupt event has occured (Listening mode) and after that reads
 * the storm information and logs the results on the USB UART.
 * 
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "thunder.h"

static thunder_t thunder;
static log_t logger;

uint8_t storm_mode;
uint32_t storm_energy;
uint8_t storm_distance;

void application_init ( void )
{
    log_cfg_t log_cfg;
    thunder_cfg_t cfg;

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
    thunder_cfg_setup( &cfg );
    THUNDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thunder_init( &thunder, &cfg );

    thunder_default_cfg( &thunder );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    storm_mode = thunder_check_int ( &thunder );

    if ( THUNDER_NOISE_LEVEL_INTERR == storm_mode )
    {
        log_printf( &logger, "Noise level too high\r\n\n" );
    }
    else if ( THUNDER_DISTURBER_INTERR == storm_mode )
    {
        log_printf( &logger, "Disturber detected\r\n\n" );
    }
    else if ( THUNDER_LIGHTNING_INTERR == storm_mode )
    {
        thunder_get_storm_info( &thunder, &storm_energy, &storm_distance );
        log_printf( &logger, "Energy of the single lightning : %lu\r\n", storm_energy );
        log_printf( &logger, "Distance estimation : %u km\r\n\n", ( uint16_t ) storm_distance );
        // Reset configuration to prepare for the next measurement
        thunder_default_cfg( &thunder );
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
