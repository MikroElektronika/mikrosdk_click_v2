/*!
 * @file main.c
 * @brief Current 15 Click example
 *
 * # Description
 * This example demonstrates the use of Current 15 Click board by reading and
 * displaying the input current measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and calibrates the data resolution at 3A load current.
 *
 * ## Application Task
 * Reads the input current measurements and displays the results on the USB UART
 * approximately once per second.
 *
 * @note
 * The measurement range is approximately: +/- 50A.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "current15.h"

// Load current [A] used for the data resolution calibration process.
#define CURRENT15_CALIBRATING_CURRENT   3.0f

static current15_t current15;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current15_cfg_t current15_cfg;  /**< Click config object. */

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
    current15_cfg_setup( &current15_cfg );
    CURRENT15_MAP_MIKROBUS( current15_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == current15_init( &current15, &current15_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at %.1fA during the calibration process.\r\n", 
                CURRENT15_CALIBRATING_CURRENT );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT15_ERROR == current15_calib_resolution ( &current15, CURRENT15_CALIBRATING_CURRENT ) )
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
    if ( CURRENT15_OK == current15_read_current ( &current15, &current ) ) 
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
