/*!
 * @file main.c
 * @brief PHT Click example
 *
 * # Description
 * This is an example that demonstrates the use of the PHT Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C, 
 * performs the device reset and determines the oversampling ratio, 
 * also write log.
 *
 * ## Application Task
 * PHT Click board can be used to measure Pressure, Temperature 
 * and Relative Humidity.
 * All data logs write on USB uart changes every 3 sec.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "pht.h"

static pht_t pht;
static log_t logger;

float pressure;
float humidity;
float temperature;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    pht_cfg_t pht_cfg;  /**< Click config object. */

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
    pht_cfg_setup( &pht_cfg );
    PHT_MAP_MIKROBUS( pht_cfg, MIKROBUS_1 );
    err_t init_flag = pht_init( &pht, &pht_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------- \r\n " );
    log_printf( &logger, " Device reset \r\n" );
    pht_reset( &pht );
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------- \r\n " );
    log_printf( &logger, " Set Oversampling Ratio \r\n" );
    pht_set_ratio( &pht, PHT_PT_CMD_RATIO_2048, PHT_PT_CMD_RATIO_2048);
    Delay_ms( 100 );
    log_printf( &logger, "---------------------------- \r\n " );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------- \r\n " );
}

void application_task ( void ) {
    pht_get_temperature_pressure( &pht, &temperature, &pressure );
    Delay_ms( 10 );
    pht_get_relative_humidity( &pht, &humidity );
    Delay_ms( 10 );
    
    log_printf( &logger, " Preassure   : %.2f mbar \r\n ", pressure );
    log_printf( &logger, " Humidity    :  %.2f %% \r\n ", humidity );
    log_printf( &logger, " Temperature :  %.2f C \r\n ", temperature );
    log_printf( &logger, "---------------------------- \r\n " );
    Delay_ms( 3000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
