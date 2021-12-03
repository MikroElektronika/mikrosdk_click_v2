/*!
 * @file main.c
 * @brief Turbidity Click example
 *
 * # Description
 * This library contains API for the Turbidity Click driver.
 * The demo application reads ADC value, ADC voltage and 
 * Nephelometric Turbidity Units ( NTU ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the Turbidity Click board™.
 * In this example, we monitor and display Nephelometric Turbidity Units ( NTU ).
 * Results are being sent to the Usart Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "turbidity.h"

static turbidity_t turbidity;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    turbidity_cfg_t turbidity_cfg;  /**< Click config object. */

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
    turbidity_cfg_setup( &turbidity_cfg );
    TURBIDITY_MAP_MIKROBUS( turbidity_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == turbidity_init( &turbidity, &turbidity_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( TURBIDITY_ERROR == turbidity_default_cfg ( &turbidity ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static float ntu;
    
    turbidity_get_ntu( &turbidity, &ntu );
    log_printf( &logger, "\tNTU : %.2f\r\n", ntu );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
