/*!
 * @file main.c
 * @brief LoadCell5 Click example
 *
 * # Description
 * This library contains API for Load Cell 5 Click driver.
 * The library initializes and defines the SPI bus drivers to read status and ADC data. 
 * The library also includes a function for tare, calibration and weight measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of SPI module, log UART, and additional pins
 * and performs the power on. Sets tare the scale, calibrate scale 
 * and start measurements. 
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Load Cell 5 click board.
 * The Load Cell 5 click board can be used to measure weight,
 * shows the measurement of scales in grams [ g ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "loadcell5.h"

static loadcell5_t loadcell5;
static log_t logger;

static uint8_t status_val;
static uint32_t adc_val;

static loadcell5_data_t cell_data;
static float weight_val;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell5_cfg_t loadcell5_cfg;  /**< Click config object. */

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

    loadcell5_cfg_setup( &loadcell5_cfg );
    LOADCELL5_MAP_MIKROBUS( loadcell5_cfg, MIKROBUS_1 );
    err_t init_flag  = loadcell5_init( &loadcell5, &loadcell5_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    loadcell5_default_cfg ( &loadcell5 );
    log_info( &logger, " Application Task " );
    Delay_ms( 500 ); 
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "     Tare the scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " >> Remove all object << \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, " please remove all object\r\n");
    log_printf( &logger, "     from the scale.     \r\n");
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start tare scales    \r\n");
    loadcell5_tare ( &loadcell5, &cell_data );
    Delay_ms( 500 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Tarring is complete   \r\n");
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Calibrate Scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, "   >>> Load etalon <<<   \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, "place 100g weight etalon\r\n");
    log_printf( &logger, "    on the scale for     \r\n");
    log_printf( &logger, "   calibration purpose.  \r\n");
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");

    if ( loadcell5_calibration ( &loadcell5, LOADCELL5_WEIGHT_100G, &cell_data ) == LOADCELL5_OK ) {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");

        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, " In the following 10 sec \r\n");
        log_printf( &logger, "   remove 100g weight   \r\n");
        log_printf( &logger, "   etalon on the scale.  \r\n");
        Delay_ms( 10000 );
    }
    else {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Start measurements :  \r\n");
    log_printf( &logger, "-------------------------\r\n");
}

void application_task ( void ) {   
    weight_val = loadcell5_get_weight( &loadcell5, &cell_data );

    log_printf(&logger, "   Weight : %.2f g\r\n", weight_val );

    Delay_ms( 1000 );
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
