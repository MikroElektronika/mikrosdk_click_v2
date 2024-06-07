/*!
 * @file main.c
 * @brief Load Cell 8 Click example
 *
 * # Description
 * This example demonstrates the use of Load Cell 8 click by measuring the weight
 * in grams of the goods from the load cell sensor connected to the click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and reads the tare scale of the empty container, and after
 * that, it calibrates the weight scale with a known calibration weight.
 *
 * ## Application Task
 * The demo application measures weight and shows the measurement of scales in grams [ g ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "loadcell8.h"

static loadcell8_t loadcell8;
static log_t logger;

static loadcell8_data_t cell_data;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell8_cfg_t loadcell8_cfg;  /**< Click config object. */

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
    loadcell8_cfg_setup( &loadcell8_cfg );
    LOADCELL8_MAP_MIKROBUS( loadcell8_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == loadcell8_init( &loadcell8, &loadcell8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LOADCELL8_ERROR == loadcell8_default_cfg ( &loadcell8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Remove all goods from the scale in the following 5 sec.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Calculating tare scale...\r\n" );
    if ( LOADCELL8_OK == loadcell8_tare_scale( &loadcell8, &cell_data ) )
    {
        log_printf( &logger, " Tarring complete!\r\n\n" );
    }
    else 
    {
        log_error( &logger, " Calculating tare scale." );
        for ( ; ; );
    }

    log_printf( &logger, " Place a %ug calibration weight on the scale in the following 5 sec.\r\n", 
                ( uint16_t ) LOADCELL8_WEIGHT_100G );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Calibrating weight...\r\n" );
    if ( LOADCELL8_OK == loadcell8_calibration_weight( &loadcell8, LOADCELL8_WEIGHT_100G, &cell_data ) ) 
    {
        log_printf( &logger, " Calibration complete!\r\n\n" );
    } 
    else 
    {
        log_error( &logger, " Calibrating weight." );
        for ( ; ; );
    }

    log_printf( &logger, " ___________________\r\n" );
    log_printf( &logger, " Start measurements:\r\n" );
    log_printf( &logger, " ___________________\r\n" );
    Delay_ms ( 500 );
}

void application_task ( void ) 
{
    float weight_g = 0;
    if ( LOADCELL8_OK == loadcell8_get_weight( &loadcell8, &cell_data, &weight_g ) )
    {
        log_printf( &logger, " Weight : %.2f g \r\n", weight_g );
    }
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
