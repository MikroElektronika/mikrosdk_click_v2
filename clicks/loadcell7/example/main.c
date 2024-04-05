/*!
 * @file main.c
 * @brief Load Cell 7 Click example
 *
 * # Description
 * This example demonstrates the use of Load Cell 7 click by measuring the weight
 * in grams of the goods from the load cell sensor connected to the click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and reads the tare scale of the empty container, and after
 * that, it calibrates the weight scale with a known calibration weight.
 *
 * ## Application Task
 * Reads the net weight of the goods in grams approximately once per second and logs the
 * results on the USB UART. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "loadcell7.h"

// Enter below the weight in grams of the goods with a known weight which 
// you will use to calibrate the scale weight.
#define LOADCELL7_CALIBRATION_WEIGHT_G  1000.0

static loadcell7_t loadcell7;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell7_cfg_t loadcell7_cfg;  /**< Click config object. */

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
    loadcell7_cfg_setup( &loadcell7_cfg );
    LOADCELL7_MAP_MIKROBUS( loadcell7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == loadcell7_init( &loadcell7, &loadcell7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove all goods from the scale in the following 5 sec.\r\n");
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Calculating tare scale...\r\n");
    if ( LOADCELL7_OK == loadcell7_tare_scale ( &loadcell7 ) ) 
    {
        log_printf( &logger, " Tarring complete!\r\n\n");
    }
    else 
    {
        log_error( &logger, " Calculating tare scale.");
        for ( ; ; );
    }
    
    log_printf( &logger, " Place a %ug calibration weight on the scale in the following 5 sec.\r\n", 
                ( uint16_t ) LOADCELL7_CALIBRATION_WEIGHT_G );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Calibrating weight...\r\n");
    if ( LOADCELL7_OK == loadcell7_calibrate_weight ( &loadcell7, LOADCELL7_CALIBRATION_WEIGHT_G ) ) 
    {
        log_printf( &logger, " Calibration complete!\r\n\n");
    }
    else 
    {
        log_error( &logger, " Calibrating weight.");
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    float weight;
    if ( LOADCELL7_OK == loadcell7_get_weight ( &loadcell7, &weight ) ) 
    {
        log_printf(&logger, " Weight : %.2f g\r\n", weight );
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
