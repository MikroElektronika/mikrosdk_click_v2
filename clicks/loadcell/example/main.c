/*!
 * \file 
 * \brief Load cell Click example
 * 
 * # Description
 * Load cell click is a weight measurement click which utilizes a load cell element, 
 * in order to precisely measure the weight of an object. 
 * The Load Cell click can be used with the strain gauge type of load cells 
 * and can measure up to ±20V or ±40V of differential voltage. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and performs the device reset, 
 * after which the next conversion cycle will be for channel B with 32 gate value.
 * This function also selects the frequency of internal oscillator to 10Hz.
 * Sets tare the scale, calibrate scale and start measurements.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Load Cell Click board.
 * Display the measurement of scales in grams [ g ].
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 1 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "loadcell.h"

// ------------------------------------------------------------------ VARIABLES

static loadcell_t loadcell;
static log_t logger;

loadcell_data_t cell_data;
static float weight_val;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    loadcell_cfg_t cfg;

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

    loadcell_cfg_setup( &cfg );
    LOADCELL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    loadcell_init( &loadcell, &cfg );
    
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "     Load cell click     \r\n");
    log_printf(&logger, "-------------------------\r\n");
    Delay_ms( 100 );
    
    loadcell_set_mode( &loadcell, LOADCELL_POWER_UP );
    Delay_ms( 100 );

    loadcell_reset( &loadcell );
    Delay_ms( 100 );

    loadcell_set_rate( &loadcell, LOADCELL_10HZ_INTERNAL_OSC );
    Delay_ms( 100 );

    log_printf(&logger, "    Tare the scale :   Channel B,  Gate 32  \r\n");
    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, " In the following 10 seconds please REMOVE all object from the scale.\r\n");
    Delay_ms( 10000 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Start tare scales    \r\n");
    loadcell_tare ( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, &cell_data );
    Delay_ms( 500 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Tarring completed \r\n");

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, " In the following 10 seconds place 100g weight etalon on the scale for calibration purpose.\r\n");
    Delay_ms( 10000 );

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "    Start calibration    \r\n");

    if ( loadcell_calibration ( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, LOADCELL_WEIGHT_100G, &cell_data ) == LOADCELL_GET_RESULT_OK )
    {
        log_printf(&logger, "-------------------------\r\n");
        log_printf(&logger, "    Calibration  Done    \r\n");

        log_printf(&logger, "- - - - - - - - - - - - -\r\n");
        log_printf(&logger, " In the following 10 seconds please REMOVE all object from the scale.\r\n");
        Delay_ms( 10000 );
    }
    else
    {
        log_printf(&logger, "-------------------------\r\n");
        log_printf(&logger, "   Calibration  Error   \r\n");
        for ( ; ; );
    }

    log_printf(&logger, "-------------------------\r\n");
    log_printf(&logger, "   Start measurements :  \r\n");
    log_printf(&logger, "-------------------------\r\n");
}

void application_task ( void )
{
    weight_val = loadcell_get_weight( &loadcell, LOADCELL_CHANN_B_GATE_32_NEXT, &cell_data );

    log_printf(&logger, "     Weight : %.2f\r\n", weight_val );

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
