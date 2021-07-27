/*!
 * @file main.c
 * @brief Force5 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Force 5 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C,
 * calibration the device, display diagnostic states and temperature.
 *
 * ## Application Task
 * Force 5 Click board is measuring force ( N ).
 * All data logs write on USB uart changes every 500 milliseconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "force5.h"

static force5_t force5;
static log_t logger;

force5_calibration_t calib_data;
uint8_t status;
float force_n;
float temperature;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    force5_cfg_t force5_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    force5_cfg_setup( &force5_cfg );
    FORCE5_MAP_MIKROBUS( force5_cfg, MIKROBUS_1 );
    err_t init_flag = force5_init( &force5, &force5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "      Calibration... \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    
    status = force5_calibration( &force5, &calib_data );
    Delay_ms( 100 );
    
    log_printf( &logger, "      Completed \r\n" );
    log_printf( &logger, "-------------------------\r\n" );
    
    log_printf( &logger, "      Diagnostic States: \r\n" );
    if ( status == FORCE5_STATES_NORMAL_OPERATION ) {
        log_printf( &logger, "    Normal Operation \r\n" );
    }
    if ( status == FORCE5_STATES_COMMAND_MODE ) {
        log_printf( &logger, "      Command Mode \r\n" );
    }
    if ( status == FORCE5_STATES_STALE_DATA ) {
        log_printf( &logger, "       Stale Data \r\n" );
    }
    if ( status == FORCE5_STATES_DIAGNOSTIC_CONDITION ) {
        log_printf( &logger, "   Diagnostic Condition \r\n" );
    }
    log_printf( &logger, "-------------------------\r\n" );
    
    temperature = force5_get_temperature( &force5 );
    Delay_ms( 100 );
    
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    log_printf( &logger, "-------------------------\r\n" );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    force_n = force5_get_force( &force5, calib_data );
    log_printf( &logger, " Force : %.4f N \r\n", force_n );
    log_printf( &logger, "------------------\r\n" );
    Delay_ms( 500 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
