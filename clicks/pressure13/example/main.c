/*!
 * @file main.c
 * @brief Pressure 13 Click Example.
 *
 * # Description
 * This is an example which demonstrates the use of Pressure 13 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - GPIO, initializes ADC, also write log.
 *
 * ## Application Task
 * Measure and display pressure ( mBar ). Results are being sent to the 
 * Usart Terminal where you can track their changes.
 * All data logs on usb uart approximately every sec.
 *
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure13.h"

static pressure13_t pressure13;   /**< Pressure 13 Click driver object. */
static log_t logger;    /**< Logger object. */

static uint16_t adc_val;
static float pressure_val;
static float voltage_val;


void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure13_cfg_t pressure13_cfg;  /**< Click config object. */

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
    pressure13_cfg_setup( &pressure13_cfg );
    PRESSURE13_MAP_MIKROBUS( pressure13_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == pressure13_init( &pressure13, &pressure13_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n", voltage_val );
}

void application_task ( void ) {
    if ( pressure13_get_pressure( &pressure13, &pressure_val ) != ADC_ERROR ) {
        log_printf( &logger, " Pressure: %.3f [mBar]\r\n", pressure_val );
    }
    log_printf( &logger, "-------------------------\r\n" );
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
