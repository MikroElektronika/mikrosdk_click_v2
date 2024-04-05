/*!
 * @file main.c
 * @brief Analog MUX 5 Click Example.
 *
 * # Description
 * This example showcases how to initialize, configure and use the Analog MUX 5 click module.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the analog inputs.
 *
 * ## Application Task
 * This is an example that shows the use of a Analog MUX 5 click board.
 * In this example, we switch from channel AN1 to channel AN4, 
 * read and display the voltage on the active channel.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 *
 * @author Nikola Peric
 *
 */

#include "board.h"
#include "log.h"
#include "analogmux5.h"

static analogmux5_t analogmux5;   /**< Analog MUX 5 Click driver object. */
static log_t logger;              /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux5_cfg_t analogmux5_cfg;  /**< Click config object. */

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
    analogmux5_cfg_setup( &analogmux5_cfg );
    ANALOGMUX5_MAP_MIKROBUS( analogmux5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == analogmux5_init( &analogmux5, &analogmux5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ANALOGMUX5_ERROR == analogmux5_default_cfg ( &analogmux5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float analogmux5_an_voltage = 0;

    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_1 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 1 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_2 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 2 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_3 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 3 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
    }
    
    analogmux5_select_ch( &analogmux5, ANALOGMUX5_SEL_CH_4 );
    Delay_ms ( 100 );
        
    if ( ADC_ERROR != analogmux5_read_an_pin_voltage ( &analogmux5, &analogmux5_an_voltage ) ) 
    {
        log_printf( &logger, " Channel [ 4 ] ---> AN Voltage : %.3f[V]\r\n\n", analogmux5_an_voltage );
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
