/*!
 * @file main.c
 * @brief LoadCell4 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Load Cell 4 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and performs the power on. 
 * Sets tare the scale, calibrate scale and start measurements.
 *
 * ## Application Task
 * The Load Cell 4 click board can be used to measure weight,
 * shows the measurement of scales in grams [ g ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 4 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "loadcell4.h"

static loadcell4_t loadcell4;
static log_t logger;

static loadcell4_data_t cell_data;
static float weight_val;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    loadcell4_cfg_t loadcell4_cfg;  /**< Click config object. */

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
    loadcell4_cfg_setup( &loadcell4_cfg );
    LOADCELL4_MAP_MIKROBUS( loadcell4_cfg, MIKROBUS_1 );
    err_t init_flag = loadcell4_init( &loadcell4, &loadcell4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    loadcell4_default_cfg ( &loadcell4 );
    
    loadcell4_power_dev( &loadcell4, LOADCELL4_PWR_ON );
    Delay_ms( 500 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     ~~~  STEP 1  ~~~    \r\n" );
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
    loadcell4_tare( &loadcell4, &cell_data );
    Delay_ms( 500 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Tarring is complete   \r\n" );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "     ~~~  STEP 2  ~~~    \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Calibrate Scale :    \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "   >>> Load etalon <<<   \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    log_printf( &logger, " In the following 10 sec \r\n" );
    log_printf( &logger, "place 100 g weight etalon\r\n" );
    log_printf( &logger, "    on the scale for     \r\n" );
    log_printf( &logger, "   calibration purpose.  \r\n" );
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );

    if ( loadcell4_calibration( &loadcell4, LOADCELL4_WEIGHT_100G, &cell_data ) == LOADCELL4_OK ) {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n" );
        log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
        log_printf( &logger, " In the following 10 sec \r\n" );
        log_printf( &logger, "   remove 100 g weight   \r\n" );
        log_printf( &logger, "   etalon on the scale.  \r\n" );
        Delay_ms( 10000 );
    } else {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   Calibration  Error   \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Start measurements :  \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
}

void application_task ( void ) {
    weight_val = loadcell4_get_weight( &loadcell4, &cell_data );
    log_printf( &logger, "     Weight : %.2f g \r\n", weight_val );
    Delay_ms( 100 );
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
