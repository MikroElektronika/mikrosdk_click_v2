/*!
 * @file main.c
 * @brief MUX 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of MUX 4 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables analog inputs.
 *
 * ## Application Task
 * Reads the voltage from all input channels and displays the values of 
 * each channel on the USB UART approximately every second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mux4.h"

static mux4_t mux4;       /**< MUX 4 Click driver object. */
static log_t logger;      /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;    /**< Logger config object. */
    mux4_cfg_t mux4_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    mux4_cfg_setup( &mux4_cfg );
    MUX4_MAP_MIKROBUS( mux4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == mux4_init( &mux4, &mux4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    mux4_enable_input( &mux4, MUX4_ENABLE_INPUT );
}

void application_task ( void ) 
{
    float mux4_an_voltage = 0;

    for ( uint8_t cnt = MUX4_SELECT_INPUT_1; cnt <= MUX4_SELECT_INPUT_8; cnt++ )
    {
        mux4_select_input( &mux4, cnt );
        Delay_ms ( 10 );
        if ( ADC_ERROR != mux4_read_an_pin_voltage ( &mux4, &mux4_an_voltage ) ) 
        {
            log_printf( &logger, " CH%u Voltage : %.3f V\r\n", ( uint16_t ) cnt, mux4_an_voltage );
        }
    }
    log_printf( &logger, " ----------------------------\r\n" );
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
