/*!
 * @file main.c
 * @brief Daq3 Click example
 *
 * # Description
 * The demo application reads ADC value, calculate and display voltage ( mV ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver and start to write log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the DAQ 3 Click board.
 * In this example, we read ADC value, calculate and display the voltage ( mV ) data.
 * The maximum output voltage ( Vout ) is 4V and  
 * depends on the gain that is set at the Click.
 * The formula used to calculate is Vin = Vout / gain. 
 * Keep in mind that Vout should not exceed 4V.
 * For example, if the gain is set to 2 the maximum Vin is 2V ( 2V = 4V / 2 ). 
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "daq3.h"

static daq3_t daq3;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;    /**< Logger config object. */
    daq3_cfg_t daq3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.

    daq3_cfg_setup( &daq3_cfg );
    DAQ3_MAP_MIKROBUS( daq3_cfg, MIKROBUS_1 );
    err_t init_flag  = daq3_init( &daq3, &daq3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    daq3_default_cfg ( &daq3 );
    log_info( &logger, " Application Task \r\n" );
    Delay_ms ( 100 );
    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "         DAQ 3 Click       \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}

void application_task ( void ) {   
    float voltage = daq3_get_voltage( &daq3 );
    log_printf( &logger, "   Voltage : %.3f mV       \r\n", voltage );
    log_printf( &logger, "---------------------------\r\n" );
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
