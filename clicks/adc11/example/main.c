/*!
 * @file main.c
 * @brief Adc11 Click example
 *
 * # Description
 * This library contains API for ADC 11 Click driver.
 * The library contains drivers for measuring ADC values  
 * and for calculation voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver and triggers the built-in calibration.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the ADC 11 Click board.
 * In this example, we monitor and display voltage [ V ].
 * Results are being sent to the Usart Terminal, where you can track their changes.
 * All data logs write on USB UART changes every 2 sec.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adc11.h"

static adc11_t adc11;
static log_t logger;

adc11_calibration_data_t avg_adc_data;
float voltage;

uint16_t adc_data;

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    adc11_cfg_t adc11_cfg;  /**< Click config object. */

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

    // Click initialization.

    adc11_cfg_setup( &adc11_cfg );
    ADC11_MAP_MIKROBUS( adc11_cfg, MIKROBUS_1 );
    err_t init_flag  = adc11_init( &adc11, &adc11_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "        Calibration        \r\n");
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n");
    log_printf( &logger, "> Turn OFF the Power unit <\r\n");
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n");
    log_printf( &logger, "  In the following 5 sec.  \r\n");
    log_printf( &logger, " turn OFF the Power Supply \r\n");
    Delay_ms( 5000 );
    
    log_printf( &logger, "-------------------------\r\n");
    log_printf( &logger, "    Start calibration    \r\n");
    
    if ( adc11_set_calibration( &adc11, &avg_adc_data ) == ADC11_OK ) {
        log_printf( &logger, "---------------------------\r\n");
        log_printf( &logger, "    Calibration  Done    \r\n");
        Delay_ms( 1000 );    
    }
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "    Start measurements :   \r\n");
    log_printf( &logger, "---------------------------\r\n");
}

void application_task ( void ) {
    adc11_get_voltage( &adc11, &avg_adc_data, &voltage );
    log_printf( &logger, "     Volatge : %.3f V      \r\n", voltage );
    log_printf( &logger, "---------------------------\r\n");
    Delay_ms( 2000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
