/*!
 * @file main.c
 * @brief DIGI IO Click example
 *
 * # Description
 * This example demonstrates the use of DIGI IO Click board by setting and reading 
 * the DOI channels state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration which sets 
 * the DOI1 and DOI2 as output and the DOI3 and DOI4 as inputs.
 *
 * ## Application Task
 * Toggles the DOI1 and DOI2 pins state and then reads the status of all four DOI pins
 * and displays the results on the USB UART approximately once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digiio.h"

static digiio_t digiio;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiio_cfg_t digiio_cfg;  /**< Click config object. */

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
    digiio_cfg_setup( &digiio_cfg );
    DIGIIO_MAP_MIKROBUS( digiio_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiio_init( &digiio, &digiio_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIIO_ERROR == digiio_default_cfg ( &digiio ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t set_out = 0;
    uint8_t doi_level = 0;
    digiio_sync_io ( &digiio );
    if ( DIGIIO_OK == digiio_read_reg ( &digiio, DIGIIO_REG_SET_OUT, &set_out ) )
    {
        set_out ^= ( DIGIIO_SET_OUT_HIGH_O1_MASK | DIGIIO_SET_OUT_HIGH_O2_MASK );
        if ( DIGIIO_OK == digiio_write_reg ( &digiio, DIGIIO_REG_SET_OUT, set_out ) )
        {
            digiio_sync_io ( &digiio );
        }
    }
    if ( DIGIIO_OK == digiio_read_reg ( &digiio, DIGIIO_REG_DOI_LEVEL, &doi_level ) )
    {
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI1 )
        {
            log_printf ( &logger, " DOI1: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI1: LOW\r\n" );
        }
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI2 )
        {
            log_printf ( &logger, " DOI2: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI2: LOW\r\n" );
        }
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI3 )
        {
            log_printf ( &logger, " DOI3: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI3: LOW\r\n" );
        }
        if ( doi_level & DIGIIO_DOI_LEVEL_DOI4 )
        {
            log_printf ( &logger, " DOI4: HIGH\r\n" );
        }
        else
        {
            log_printf ( &logger, " DOI4: LOW\r\n" );
        }
        log_printf ( &logger, "\r\n" );
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
