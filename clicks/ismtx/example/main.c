/*!
 * @file main.c
 * @brief ISMTX Click example
 *
 * # Description
 * This application shows capability of ISM TX Click board. 
 * It sets default configuration, and transmits data in 
 * manchester encoding with FSK or ASK signal modulation.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of log and communication, set's signal modulation, 
 * resets device, and set's default configuration for selected modulation.

 *
 * ## Application Task
 * Transmits data via external antenna in span of 500ms.
 *
 * *note:*
 * Default configuration configures device and set's transmission frequency to 433.92 MHz.
 * If selected modulation is FSK frequency deviation is set to 40kHz.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ismtx.h"

#define PREAMBLE_BYTE   0xFF

#define TX_DATA         "MikroE"

static ismtx_t ismtx;
static log_t logger;


void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ismtx_cfg_t ismtx_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ismtx_cfg_setup( &ismtx_cfg );
    ISMTX_MAP_MIKROBUS( ismtx_cfg, MIKROBUS_1 );
    err_t init_flag  = ismtx_init( &ismtx, &ismtx_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ismtx.modulation = ISM_TX_MODULATION_FSK;

    ismtx_soft_reset( &ismtx );
    
    if ( ismtx_default_cfg ( &ismtx ) < 0 )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, select correct signal modulation... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_info( &logger, " Data sent! [%s]", TX_DATA );
    ismtx_transmit_data( &ismtx, PREAMBLE_BYTE, TX_DATA, strlen( TX_DATA ) );
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
