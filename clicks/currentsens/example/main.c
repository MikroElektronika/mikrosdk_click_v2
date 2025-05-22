/*!
 * @file main.c
 * @brief Current Sens Click example
 *
 * # Description
 * This example demonstrates the use of Current Sens Click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and calibrates the zero current offset and data resolution
 * at 3A load current.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @note
 * The measurement range is approximately: +/- 85A.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "currentsens.h"

// Load current [A] used for the data resolution calibration process.
#define CURRENTSENS_CALIBRATING_CURRENT   3.0f

static currentsens_t currentsens;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentsens_cfg_t currentsens_cfg;  /**< Click config object. */

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
    currentsens_cfg_setup( &currentsens_cfg );
    CURRENTSENS_MAP_MIKROBUS( currentsens_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == currentsens_init( &currentsens, &currentsens_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENTSENS_ERROR == currentsens_calib_offset ( &currentsens ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at %.1fA during the calibration process.\r\n", 
                CURRENTSENS_CALIBRATING_CURRENT );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENTSENS_ERROR == currentsens_calib_resolution ( &currentsens, CURRENTSENS_CALIBRATING_CURRENT ) )
    {
        log_error( &logger, " Calibrate resolution." );
        for ( ; ; );
    }
    log_printf( &logger, " Data resolution calibration DONE.\r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float current = 0;
    if ( CURRENTSENS_OK == currentsens_read_current ( &currentsens, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
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
