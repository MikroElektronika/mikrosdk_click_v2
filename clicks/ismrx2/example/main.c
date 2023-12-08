/*!
 * @file main.c
 * @brief ISM RX 2 Click Example.
 *
 * # Description
 * This application shows capability of ISM RX 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize GPIO pins and LOG module and sets default configuration.
 *
 * ## Application Task
 * Wait for the data pin to go down and start sampling and wait for sync word if it's received 
 * collect data to buffer till it receives 0 byte
 *
 * @note
 * Application task is broken down into two parts:
 * DEFAULT_EXAMPLE - Collects data from the OOK TX Click board and displays it on the 
 * USB UART terminal.
 * MANCHESTER_EXAMPLE - Collects Manchester encoded data from the ISM TX Click board, 
 * decodes it and displays it on the USB UART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ismrx2.h"

#define DEFAULT_EXAMPLE        
// #define MANCHESTER_EXAMPLE       

static ismrx2_t ismrx2;   /**< ISM RX 2 Click driver object. */
static log_t logger;    /**< Logger object. */

static uint8_t read_data[ 8 ] = { 0 }; /**< Read data buffer. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ismrx2_cfg_t ismrx2_cfg;  /**< Click config object. */

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
    ismrx2_cfg_setup( &ismrx2_cfg );
    ISMRX2_MAP_MIKROBUS( ismrx2_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == ismrx2_init( &ismrx2, &ismrx2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ISMRX2_ERROR == ismrx2_default_cfg ( &ismrx2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEFAULT_EXAMPLE
    
    if ( ISMRX2_PIN_STATE_LOW == ismrx2_get_data_pin_state( &ismrx2 ) )
    {
        if ( ISMRX2_OK == ismrx2_read_rf_data( &ismrx2, read_data ) )
        {
            log_printf( &logger, " RX data: " );
            for ( uint8_t n_cnt = 0; n_cnt < strlen( read_data ); n_cnt++ )
            {
                if ( read_data[ n_cnt ] != '\0' )
                {
                    log_printf( &logger, "%c", read_data[ n_cnt ] );
                }
            }    
            log_printf( &logger, "\r\n*********************\r\n" );
            Delay_ms( 10 );
        }
    }
#endif
#ifdef MANCHESTER_EXAMPLE 
    if ( ISMRX2_PIN_STATE_LOW == ismrx2_get_data_pin_state( &ismrx2 ) )
    {
        if ( ISMRX2_OK == ismrx2_read_manchester_data( &ismrx2, &read_data ) )
        {
            log_printf( &logger, " Read data: " );
            for ( uint8_t n_cnt = 1; n_cnt < strlen( read_data ); n_cnt++ )
            {
                log_printf( &logger, "%c", read_data[ n_cnt ] );
            }
            log_printf( &logger, "\r\n*********************\r\n" );
            Delay_ms( 10 );
        }
    }
#endif
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
