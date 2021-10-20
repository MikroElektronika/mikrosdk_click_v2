/*!
 * @file main.c
 * @brief Alcohol Click Example.
 *
 * # Description
 * The demo application shows the reading of the adc 
 * values given by the sensors.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring clicks and log objects.
 *
 * ## Application Task
 * Reads the adc value and prints in two forms (DEC and HEX).
 * 
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "alcohol.h"

static alcohol_t alcohol;   /**< Alcohol Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    alcohol_cfg_t alcohol_cfg;  /**< Click config object. */

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

    alcohol_cfg_setup( &alcohol_cfg );
    ALCOHOL_MAP_MIKROBUS( alcohol_cfg, MIKROBUS_5 );
    if ( alcohol_init( &alcohol, &alcohol_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {
    uint16_t alcohol_an_value = 0;

    if ( alcohol_read_an_pin_value ( &alcohol, &alcohol_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", alcohol_an_value );
    }

    float alcohol_an_voltage = 0;

    if ( alcohol_read_an_pin_voltage ( &alcohol, &alcohol_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", alcohol_an_voltage );
    }

    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
