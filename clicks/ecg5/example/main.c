/*!
 * @file main.c
 * @brief ECG 5 Click Example.
 *
 * # Description
 * This is an example which demonstrates the use of ECG 5 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes ADC and GPIO.
 *
 * ## Application Task
 * Reads ADC value and sends results on serial plotter every 5 ms.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "ecg5.h"

static ecg5_t ecg5;   /**< ECG 5 Click driver object. */
static log_t logger;    /**< Logger object. */
static uint32_t time;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    ecg5_cfg_t ecg5_cfg;  /**< Click config object. */

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
    ecg5_cfg_setup( &ecg5_cfg );
    ECG5_MAP_MIKROBUS( ecg5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ecg5_init( &ecg5, &ecg5_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t ecg5_an = 0;
    if ( ADC_SUCCESS == ecg5_read_an_pin_value( &ecg5, &ecg5_an ) ) {
        log_printf( &logger, " %u,%lu\r\n ", ecg5_an, time );
    }
    time += 5;
    Delay_ms( 5 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
