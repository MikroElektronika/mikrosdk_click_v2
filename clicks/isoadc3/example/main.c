/*!
 * @file main.c
 * @brief ISOADC3 Click example
 *
 * # Description
 * This example shows the capabilities of the ISO ADC 3 Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes I2C driver and makes an initial log.
 *
 * ## Application Task
 * Measures ADC voltage level and prints it via USB UART terminal.

 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "isoadc3.h"

static isoadc3_t isoadc3;
static log_t logger;

uint16_t voltage;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc3_cfg_t isoadc3_cfg;  /**< Click config object. */

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
    isoadc3_cfg_setup( &isoadc3_cfg );
    ISOADC3_MAP_MIKROBUS( isoadc3_cfg, MIKROBUS_1 );
    err_t init_flag = isoadc3_init( &isoadc3, &isoadc3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    voltage = isoadc3_read_voltage( &isoadc3, ISOADC3_VREF_3V3 );
    log_printf( &logger, " ADC voltage Level: %d mV \r\n", voltage );
    log_printf( &logger, "------------------------\r\n" );
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
