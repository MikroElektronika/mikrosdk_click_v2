/*!
 * @file main.c
 * @brief IrThermo5V Click example
 *
 * # Description
 * This application collects data from the sensor, and logs the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes IrThermo 5V Driver.
 * 
 * ## Application Task  
 * Reading Ambient and Object Temperature and displaying the value periodically.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "irthermo5v.h"

static irthermo5v_t irthermo5v;
static log_t logger;

static float measured_temperature;
static float object_temperature;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo5v_cfg_t irthermo5v_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init \r\n " );
    log_printf( &logger, "------------------------------\r\n " );

    // Click initialization.
    irthermo5v_cfg_setup( &irthermo5v_cfg );
    IRTHERMO5V_MAP_MIKROBUS( irthermo5v_cfg, MIKROBUS_1 );
    err_t init_flag = irthermo5v_init( &irthermo5v, &irthermo5v_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task \r\n" );
    log_printf( &logger, "------------------------------\r\n " );
}

void application_task ( void ) {
    measured_temperature = irthermo5v_get_t_ambient( &irthermo5v );
    object_temperature = irthermo5v_get_t_object( &irthermo5v );
    log_printf( &logger, " Ambient Temperature: %.2f C\r\n ", measured_temperature );
    log_printf( &logger, " Object  Temperature: %.2f C\r\n ", object_temperature );
    log_printf( &logger, "------------------------------\r\n " );
    Delay_ms ( 1000 );
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
