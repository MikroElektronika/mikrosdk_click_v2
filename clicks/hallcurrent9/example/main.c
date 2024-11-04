/*!
 * @file main.c
 * @brief HallCurrent9 Click example
 *
 * # Description
 * This library contains API for Hall Current 9 Click driver.
 * The library contains drivers for measuring ADC values 
 * and for calculation current. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and triggers the built-in calibration.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Hall Current 9 Click board.
 * In this example, we read and display the ADC and current ( mA ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent9.h"

static hallcurrent9_t hallcurrent9;
static log_t logger;

static uint16_t adc_data;
static float current;
hallcurrent9_calibration_data_t avg_adc_data;

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    hallcurrent9_cfg_t hallcurrent9_cfg;  /**< Click config object.  */

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
    log_printf( &logger, "\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "   Hall Current 9 Click   \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    hallcurrent9_cfg_setup( &hallcurrent9_cfg );
    HALLCURRENT9_MAP_MIKROBUS( hallcurrent9_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent9_init( &hallcurrent9, &hallcurrent9_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "        Calibration        \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "> Turn OFF the Power unit <\r\n" );
    log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    log_printf( &logger, "  In the following 5 sec.  \r\n" );
    log_printf( &logger, " turn OFF the Power Supply \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "    Start calibration    \r\n" );
    
    if ( hallcurrent9_set_calibration( &hallcurrent9, &avg_adc_data ) == HALLCURRENT9_OK ) {
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "    Calibration  Done    \r\n" );
        Delay_ms ( 1000 );    
    }
    
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "    Start measurements :   \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}

void application_task ( void ) {   
    log_printf( &logger, "--------------------------\r\n", adc_data );
    hallcurrent9_read_adc( &hallcurrent9, &adc_data );
    log_printf( &logger, "   ADC     : %d \r\n", adc_data );

    current = hallcurrent9_get_current( &hallcurrent9, &avg_adc_data );
    log_printf( &logger, "   Current : %.2f mA \r\n", current );
    Delay_ms ( 1000 );
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
