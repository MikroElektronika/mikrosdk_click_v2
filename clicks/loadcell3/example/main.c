/*!
 * @file main.c
 * @brief LoadCell3 Click example
 *
 * # Description
 * This library contains API for the Load Cell 3 click driver.
 * The library also includes a function for tare and calibration and weight measurement.
 * This demo application shows an example of weight measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization and default settings, the app sets tare the scale, 
 * calibrate scale and start measurements. 
 *
 * ## Application Task
 * This is an example that shows the use of a Load Cell 3 click board™.
 * The Load Cell 3 click board can be used to measure weight,
 * shows the measurement of scales in grams [ g ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "loadcell3.h"

static loadcell3_t loadcell3;
static log_t logger;

static loadcell3_data_t cell_data;
static float weight_val;

void application_init ( void ) {
    log_cfg_t log_cfg;              /**< Logger config object. */
    loadcell3_cfg_t loadcell3_cfg;  /**< Click config object. */

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

    loadcell3_cfg_setup( &loadcell3_cfg );
    LOADCELL3_MAP_MIKROBUS( loadcell3_cfg, MIKROBUS_1 );
    err_t init_flag = loadcell3_init( &loadcell3, &loadcell3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    loadcell3_default_cfg ( &loadcell3 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     Tare the scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " >> Remove all object << \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, " please remove all object\r\n" );
    log_printf( &logger, "     from the scale.     \r\n" );
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start tare scales    \r\n" );
    loadcell3_tare ( &loadcell3, &cell_data );
    Delay_ms( 500 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Tarring is complete   \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Calibrate Scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "   >>> Load etalon <<<   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, "place 100g weight etalon \r\n" );
    log_printf( &logger, "    on the scale for     \r\n" );
    log_printf( &logger, "   calibration purpose.  \r\n" );
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );

    if ( loadcell3_calibration ( &loadcell3, LOADCELL3_WEIGHT_100G, &cell_data ) == LOADCELL3_OK ) {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );

        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, " In the following 10 sec \r\n" );
        log_printf( &logger, "   remove 100g weight    \r\n" );
        log_printf( &logger, "   etalon on the scale.  \r\n" );
        Delay_ms( 10000 );
    }
    else {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   Calibration  Error    \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Start measurements :  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
}

void application_task ( void ) {
    weight_val = loadcell3_get_weight( &loadcell3, &cell_data );
    log_printf( &logger, "   Weight : %.2f g\r\n", weight_val );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
