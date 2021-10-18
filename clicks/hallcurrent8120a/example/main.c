/*!
 * @file main.c
 * @brief Hall Current 8 120A Click Example.
 *
 * # Description
 * This library contains API for Hall Current 8 120A Click driver.
 * The library initializes and defines the ADC drivers.
 * The library also includes a function for calibration, 
 * current measurement and overcurrent detection.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes ADC driver, calibrate AD conversion 
 * of the AN pin and start to write log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Hall Current 8 120A click board.
 * In this example, we read and display current data [A], 
 * ADC value and AN pin voltage level [V]. 
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent8120a.h"

static hallcurrent8120a_t hallcurrent8120a;   /**< Hall Current 8 120A Click driver object. */
static log_t logger;                          /**< Logger object. */

hallcurrent8120a_offset_t offset_val;

void application_init ( void ) {
    log_cfg_t log_cfg;                            /**< Logger config object. */
    hallcurrent8120a_cfg_t hallcurrent8120a_cfg;  /**< Click config object. */

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

    hallcurrent8120a_cfg_setup( &hallcurrent8120a_cfg );
    HALLCURRENT8120A_MAP_MIKROBUS( hallcurrent8120a_cfg, MIKROBUS_1 );
    if ( hallcurrent8120a_init( &hallcurrent8120a, &hallcurrent8120a_cfg ) == ADC_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 1000 );
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, " Turn OFF the power supply \r\n" );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "     Start Calibration     \r\n" );
    hallcurrent8120a_calibration ( &hallcurrent8120a, &offset_val );
    Delay_ms( 1000 );
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, " Turn ON the power supply  \r\n" );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---------------------------\r\n");
    log_printf( &logger, "    Start measurements :   \r\n");
    log_printf( &logger, "---------------------------\r\n");
}

void application_task ( void ) {
    float hallcurrent8120a_current = 0;
    
    if ( hallcurrent8120a_get_current ( &hallcurrent8120a, &offset_val, &hallcurrent8120a_current ) != ADC_ERROR ) {
        log_printf( &logger, "   Current     : %.2f [A]\r\n", hallcurrent8120a_current );
    }
    
    uint16_t hallcurrent8120a_an_value = 0;

    if ( hallcurrent8120a_read_an_pin_value ( &hallcurrent8120a, &hallcurrent8120a_an_value ) != ADC_ERROR ) {
        log_printf( &logger, "   ADC Value   : %u\r\n", hallcurrent8120a_an_value );
    }

    float hallcurrent8120a_an_voltage = 0;

    if ( hallcurrent8120a_read_an_pin_voltage ( &hallcurrent8120a, &hallcurrent8120a_an_voltage ) != ADC_ERROR ) {
        log_printf( &logger, "   AN Voltage  : %.2f [V]\r\n", hallcurrent8120a_an_voltage );
    }
    log_printf( &logger, "---------------------------\r\n");
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
