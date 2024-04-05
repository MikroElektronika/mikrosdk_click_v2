/*!
 * @file main.c
 * @brief IrThermo3V3 Click example
 *
 * # Description
 * This application collects data from the sensor, and logs the results.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes IrThermo 3V3 Driver.
 * 
 * ## Application Task  
 * Reading Ambient and Object Temperature and displaying the value periodically.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "irthermo3v3.h"

static irthermo3v3_t irthermo3v3;
static log_t logger;

static float measured_temperature;
static float object_temperature;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo3v3_cfg_t irthermo3v3_cfg;  /**< Click config object. */

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
    log_printf( &logger, " -------------------------------\r\n " );
    Delay_ms ( 100 );

    // Click initialization.
    irthermo3v3_cfg_setup( &irthermo3v3_cfg );
    IRTHERMO3V3_MAP_MIKROBUS( irthermo3v3_cfg, MIKROBUS_1 );
    err_t init_flag = irthermo3v3_init( &irthermo3v3, &irthermo3v3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task \r\n" );
    log_printf( &logger, "------------------------------\r\n " );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    measured_temperature = irthermo3v3_get_t_ambient( &irthermo3v3 );
    object_temperature = irthermo3v3_get_t_object( &irthermo3v3 );
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
