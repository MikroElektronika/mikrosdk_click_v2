/*!
 * @file main.c
 * @brief LPG Click Example.
 *
 * # Description
 * The demo application shows the reading of the adc 
 * values given by the sensors.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Configuring Clicks and log objects.
 *
 * ## Application Task
 * Reads the adc value and prints in two forms (DEC and HEX).
 *  
 * @author Jelena Milosavljevic
 *
 */

// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lpg.h"

// ------------------------------------------------------------------ VARIABLES

static lpg_t lpg;   /**< LPG Click driver object. */
static log_t logger;    /**< Logger object. */

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    lpg_cfg_t lpg_cfg;  /**< Click config object. */

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

    lpg_cfg_setup( &lpg_cfg );
    LPG_MAP_MIKROBUS( lpg_cfg, MIKROBUS_1 );
    if ( lpg_init( &lpg, &lpg_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

       for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t lpg_an_value = 0;

    if ( lpg_read_an_pin_value ( &lpg, &lpg_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " ADC Value : %u\r\n", lpg_an_value );
    }

    float lpg_an_voltage = 0;

    if ( lpg_read_an_pin_voltage ( &lpg, &lpg_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", lpg_an_voltage );
    }

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
