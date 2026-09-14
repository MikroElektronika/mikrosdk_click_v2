/*!
 * @file main.c
 * @brief HOD CAP 2 Click example
 *
 * # Description
 * This example demonstrates the use of the HOD CAP 2 Click board for
 * reading capacitive sensor measurements from four sensing channels and
 * one reference channel. The application also displays the device unique ID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and HOD CAP 2 Click driver, applies the default
 * configuration, and reads the device unique ID.
 *
 * ## Application Task
 * Periodically reads measurement data from all four sensor channels and
 * the reference channel and logs the results to the serial terminal.
 *
 * @author Stefan Filipovic
 *
 */
#include "board.h"
#include "log.h"
#include "hodcap2.h"

#ifndef MIKROBUS_POSITION_HODCAP2
    #define MIKROBUS_POSITION_HODCAP2 MIKROBUS_1
#endif

static hodcap2_t hodcap2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hodcap2_cfg_t hodcap2_cfg;  /**< Click config object. */

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
    hodcap2_cfg_setup( &hodcap2_cfg );
    HODCAP2_MAP_MIKROBUS( hodcap2_cfg, MIKROBUS_POSITION_HODCAP2 );
    if ( SPI_MASTER_ERROR == hodcap2_init( &hodcap2, &hodcap2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HODCAP2_ERROR == hodcap2_default_cfg ( &hodcap2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " Unique ID: 0x%.4X%.4X%.4X\r\n", 
                 hodcap2.unique_id[ 0 ], hodcap2.unique_id[ 1 ], hodcap2.unique_id[ 2 ] );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t sen0 = 0;
    uint16_t sen1 = 0;
    uint16_t sen2 = 0;
    uint16_t sen3 = 0;
    uint16_t ref_data = 0;

    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_1, &sen0 ) )
    {
        log_printf ( &logger, " SEN0: %u\r\n", sen0 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_2, &sen1 ) )
    {
        log_printf ( &logger, " SEN1: %u\r\n", sen1 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_3, &sen2 ) )
    {
        log_printf ( &logger, " SEN2: %u\r\n", sen2 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_4, &sen3 ) )
    {
        log_printf ( &logger, " SEN3: %u\r\n", sen3 );
    }
    if ( HODCAP2_OK == hodcap2_read_measurement ( &hodcap2, HODCAP2_TABLE_5, &ref_data ) )
    {
        log_printf ( &logger, " REF: %u\r\n\n", ref_data );
    }

    Delay_ms ( 500 );
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
