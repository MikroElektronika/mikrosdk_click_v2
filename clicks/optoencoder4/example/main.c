/*!
 * @file main.c
 * @brief Opto Encoder 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of Opto Encoder 4 click board by processing
 * the encoder output pin state and incrementing the step counter on falling edge.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Increments the step counter on falling edge of the encoder output pin state
 * and displays it on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "optoencoder4.h"

static optoencoder4_t optoencoder4; /**< Opto Encoder 4 Click driver object. */
static log_t logger;                /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    optoencoder4_cfg_t optoencoder4_cfg;  /**< Click config object. */

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
    optoencoder4_cfg_setup( &optoencoder4_cfg );
    OPTOENCODER4_MAP_MIKROBUS( optoencoder4_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == optoencoder4_init( &optoencoder4, &optoencoder4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint32_t step_cnt = 0;

    log_printf( &logger, " Step counter : %lu\r\n", step_cnt );
    
    // Increment counter on falling edge of output pin
    while ( !optoencoder4_get_out_pin ( &optoencoder4 ) );
    while ( optoencoder4_get_out_pin ( &optoencoder4 ) );

    step_cnt++;
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
