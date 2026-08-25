/*!
 * @file main.c
 * @brief DIGI Isolator 4 Click Example.
 *
 * # Description
 * This example demonstrates the use of the DIGI Isolator 4 Click board by
 * reading and displaying the state of two isolated digital input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables outputs.
 *
 * ## Application Task
 * Reads the state of both isolated digital input channels and displays
 * the results on the USB UART every 500ms.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "digiisolator4.h"

#ifndef MIKROBUS_POSITION_DIGIISOLATOR4
    #define MIKROBUS_POSITION_DIGIISOLATOR4 MIKROBUS_1
#endif

static digiisolator4_t digiisolator4;   /**< DIGI Isolator 4 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator4_cfg_t digiisolator4_cfg;  /**< Click config object. */

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
    digiisolator4_cfg_setup( &digiisolator4_cfg );
    DIGIISOLATOR4_MAP_MIKROBUS( digiisolator4_cfg, MIKROBUS_POSITION_DIGIISOLATOR4 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == digiisolator4_init( &digiisolator4, &digiisolator4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    digiisolator4_enable_output( &digiisolator4 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    digiisolator4_inputs_t input_data;

    if ( DIGIISOLATOR4_OK == digiisolator4_read_inputs( &digiisolator4, &input_data ) )
    {
        log_printf( &logger, " IN1: %u\r\n", ( uint16_t ) input_data.in1_state );
        log_printf( &logger, " IN2: %u\r\n\n", ( uint16_t ) input_data.in2_state );
    }

    Delay_ms ( 500 );
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
