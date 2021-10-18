/*!
 * \file 
 * \brief LoadCell2 Click example
 * 
 * # Description
 * Load Cell 2 click is a weight measurement click 
 * which utilizes a load cell element, 
 * in order to precisely measure the weight of an object. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and performs the device reset, 
 * and performs the device reset, set power on and default configuration.
 * Sets tare the scale, calibrate scale and start measurements.
 * 
 * ## Application Task  
 * This is an example which demonstrates the 
 * use of Load Cell 2 Click board. 
 * Display the measurement of scales in grams [g].
 * Results are being sent to the Usart Terminal 
 * where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "loadcell2.h"

// ------------------------------------------------------------------ VARIABLES

static loadcell2_t loadcell2;
static log_t logger;

static loadcell2_data_t cell_data;
static float weight_val;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    loadcell2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    loadcell2_cfg_setup( &cfg );
    LOADCELL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    loadcell2_init( &loadcell2, &cfg );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "     Load cell click     \r\n");
    log_printf( &logger, "-------------------------\r\n");
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Reset all registers   \r\n");
    loadcell2_reset( &loadcell2 );
    Delay_ms( 100 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "        Power On         \r\n");
    loadcell2_power_on( &loadcell2 );
    Delay_ms( 100 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Set default config.   \r\n");
    loadcell2_default_cfg( &loadcell2 );
    Delay_ms( 100 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "      Calibrate AFE      \r\n");
    loadcell2_calibrate_afe( &loadcell2 );
    Delay_ms( 1000 );

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
    loadcell2_tare ( &loadcell2, &cell_data );
    Delay_ms( 500 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Tarring is complete   \r\n");
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Calibrate Scale :    \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, "   >>> Load etalon <<<   \r\n");
    log_printf( &logger, "- - - - - - - - - - - - -\r\n");
    log_printf( &logger, " In the following 10 sec \r\n");
    log_printf( &logger, "place 1000g weight etalon\r\n");
    log_printf( &logger, "    on the scale for     \r\n");
    log_printf( &logger, "   calibration purpose.  \r\n");
    Delay_ms( 10000 );

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");

    if ( loadcell2_calibration ( &loadcell2, LOADCELL2_WEIGHT_1000G, &cell_data ) == LOADCELL2_GET_RESULT_OK )
    {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");

        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, "  >>> Remove etalon <<<  \r\n");
        log_printf( &logger, "- - - - - - - - - - - - -\r\n");
        log_printf( &logger, " In the following 10 sec \r\n");
        log_printf( &logger, "   remove 1000g weight   \r\n");
        log_printf( &logger, "   etalon on the scale.  \r\n");
        Delay_ms( 10000 );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n");
        log_printf( &logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "   Start measurements :  \r\n");
    log_printf( &logger, "-------------------------\r\n");
}

void application_task ( void )
{
    weight_val = loadcell2_get_weight( &loadcell2, &cell_data );

    log_printf(&logger, "   Weight : %.2f g\r\n", weight_val );

    Delay_ms( 1000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
