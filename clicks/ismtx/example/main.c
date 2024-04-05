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
 * Initialization of log and communication, sets signal modulation, 
 * resets device, and sets default configuration for selected modulation.
 *
 * ## Application Task
 * Transmits data via external antenna in span of 100ms.
 *
 * @note
 * Default configuration configures device and sets transmission frequency to 433.92 MHz.
 * If selected modulation is FSK frequency deviation is set to 40kHz.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ismtx.h"

#define PREAMBLE_BYTE   0xFF

uint8_t tx_data_buf[ 9 ] = { 'M', 'I', 'K', 'R', 'O', 'E', '\r', '\n', 0 };

static ismtx_t ismtx;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ismtx_cfg_t ismtx_cfg;  /**< Click config object. */

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
    ismtx_cfg_setup( &ismtx_cfg );
    ISMTX_MAP_MIKROBUS( ismtx_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ismtx_init( &ismtx, &ismtx_cfg ) ) 
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
    log_info( &logger, " Data sent: %s", tx_data_buf );
    ismtx_transmit_data( &ismtx, PREAMBLE_BYTE, tx_data_buf, sizeof( tx_data_buf ) );
    Delay_ms ( 100 );
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
