/*!
 * @file main.c
 * @brief DIGI Isolator 2 Click example
 *
 * # Description
 * This example demonstrates the use of DIGI Isolator 2 click board by reading
 * and displaying the state of 8 digital input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables isolator outputs.
 *
 * ## Application Task
 * Reads the state of 8 digital input channels in hex format where MSB represents
 * IN8 and LSB the channel IN1. The results are displayed on the USB UART every 500ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digiisolator2.h"

static digiisolator2_t digiisolator2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiisolator2_cfg_t digiisolator2_cfg;  /**< Click config object. */

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
    digiisolator2_cfg_setup( &digiisolator2_cfg );
    DIGIISOLATOR2_MAP_MIKROBUS( digiisolator2_cfg, MIKROBUS_1 );
    if ( DIGIISOLATOR2_OK != digiisolator2_init( &digiisolator2, &digiisolator2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    digiisolator2_enable_output( &digiisolator2 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t input_data = 0;
    if ( DIGIISOLATOR2_OK == digiisolator2_read_inputs ( &digiisolator2, &input_data ) )
    {
        log_printf( &logger, " INPUT: 0x%.2X\r\n\n", ( uint16_t ) input_data );
        Delay_ms ( 500 );
    }
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
