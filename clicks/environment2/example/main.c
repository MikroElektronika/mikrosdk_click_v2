/*!
 * @file main.c
 * @brief Environment2 Click example
 *
 * # Description
 * This library contains API for Environment 2 Click driver.
 * The library contains drivers for measuring air quality,
 * temperature and relative humidity.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and triggers the built-in self-test checking.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Environment 2 Click board.
 * Measured and display air quality ( raw data ), 
 * temperature ( degrees Celsius ) and relative humidity ( % ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB UART changes every 2 sec.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "environment2.h"

static environment2_t environment2;
static log_t logger;
static uint16_t air_quality;
static float humidity;
static float temperature;

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    environment2_cfg_t environment2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n    Application Init\r\n" );

    // Click initialization.

    environment2_cfg_setup( &environment2_cfg );
    ENVIRONMENT2_MAP_MIKROBUS( environment2_cfg, MIKROBUS_1 );
    err_t init_flag = environment2_init( &environment2, &environment2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_printf( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "    Application Task   \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "  Environment 2 Click  \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    
    if ( environment2_sgp40_measure_test( &environment2 ) == ENVIRONMENT2_SGP40_TEST_PASSED ) {
        log_printf( &logger, "    All tests passed\r\n" );
        log_printf( &logger, "      Successfully\r\n" );
    } else {
        log_printf( &logger, "    One or more tests have\r\n" );
        log_printf( &logger, "     Failed\r\n" );
    }
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 100 );
    
    environment2_sgp40_heater_off( &environment2 );
    Delay_ms( 100 );
}

void application_task ( void ) {
    environment2_get_temp_hum(  &environment2, &humidity, &temperature );
    log_printf( &logger, " Humidity    : %.2f %% \r\n", humidity );
    log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
    
    environment2_get_air_quality( &environment2, &air_quality );
    log_printf( &logger, " Air Quality : %d \r\n", air_quality );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
