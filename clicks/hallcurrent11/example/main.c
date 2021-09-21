/*!
 * @file main.c
 * @brief HallCurrent11 Click example
 *
 * # Description
 * This library contains API for Hall Current 11 Click driver.
 * The demo application reads ADC value and current ( A ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Hall Current 11 Click board™.
 * In this example, we read and display the ADC values and current ( A ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent11.h"

static hallcurrent11_t hallcurrent11;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent11_cfg_t hallcurrent11_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    hallcurrent11_cfg_setup( &hallcurrent11_cfg );
    HALLCURRENT11_MAP_MIKROBUS( hallcurrent11_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent11_init( &hallcurrent11, &hallcurrent11_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hallcurrent11_default_cfg ( &hallcurrent11 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static uint16_t adc_data;
    static float current;
    
    hallcurrent11_get_adc( &hallcurrent11, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    log_printf( &logger, "- - - - - - - - - - -  - -\r\n" );
    Delay_ms( 100 );

    hallcurrent11_get_current ( &hallcurrent11, &current );
    log_printf( &logger, " Current     : %.3f A \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
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
