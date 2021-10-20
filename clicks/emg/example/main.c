/*!
 * @file main.c
 * @brief EMG Click Example.
 *
 * # Description
 * This is an example which demonstrates the use of EMG Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes ADC and timer counter.
 *
 * ## Application Task
 * Reads ADC value and sends results on serial plotter every 5 ms.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "emg.h"

static emg_t emg;   /**< EMG Click driver object. */
static log_t logger;    /**< Logger object. */
uint32_t time;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    emg_cfg_t emg_cfg;  /**< Click config object. */

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
    emg_cfg_setup( &emg_cfg );
    EMG_MAP_MIKROBUS( emg_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == emg_init( &emg, &emg_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    time = 0;
    log_info( &logger, " Application Task " );
}

void application_task ( void )  {
    uint16_t emg_an = 0;
    if ( emg_read_an_pin_value( &emg, &emg_an ) == ADC_SUCCESS ){
        log_printf( &logger, " %u,%lu\r\n ", emg_an, time );
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
