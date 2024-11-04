/*!
 * @file main.c
 * @brief Analog MUX 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of Analog MUX 4 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the analog inputs.
 *
 * ## Application Task
 * Reads and displays the voltage of all channels on the USB UART approximately once per second.
 *
 * @note
 * The channel's voltage will "float" when the voltage source is not connected to it.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "analogmux4.h"

static analogmux4_t analogmux4;   /**< Analog MUX 4 Click driver object. */
static log_t logger;              /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux4_cfg_t analogmux4_cfg;  /**< Click config object. */

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
    analogmux4_cfg_setup( &analogmux4_cfg );
    ANALOGMUX4_MAP_MIKROBUS( analogmux4_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == analogmux4_init( &analogmux4, &analogmux4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    analogmux4_enable_input ( &analogmux4 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float analogmux4_an_voltage = 0;
    
    for ( uint8_t cnt = ANALOGMUX4_CHANNEL_0; cnt <= ANALOGMUX4_CHANNEL_7; cnt++ )
    {
        analogmux4_set_input_channel ( &analogmux4, cnt );
        if ( ADC_ERROR != analogmux4_read_an_pin_voltage ( &analogmux4, &analogmux4_an_voltage ) ) 
        {
            log_printf( &logger, " AN%u voltage : %.3f V\r\n", ( uint16_t ) cnt, analogmux4_an_voltage );
        }
    }
    log_printf( &logger, "\r\n" );
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
