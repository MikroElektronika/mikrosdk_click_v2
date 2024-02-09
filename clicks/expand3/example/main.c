/*!
 * @file main.c
 * @brief Expand 3 Click Example.
 *
 * # Description
 * This example demonstrates the use of Expand 3 click board by setting and
 * reading the port state.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Writes a counter data to the port output pins and reads the status of the same port
 * input pins approximately every 500ms. All data are displayed on the USB UART.
 * 
 * @note
 * The PIO pins are in the open-drain mode, therefore a pull-up resistor must be added
 * to each pin. This click board can be used in a combination with an EasyLED [MIKROE-571]
 * and EasyPULL [MIKROE-575] boards.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "expand3.h"

static expand3_t expand3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand3_cfg_t expand3_cfg;  /**< Click config object. */

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
    expand3_cfg_setup( &expand3_cfg );
    EXPAND3_MAP_MIKROBUS( expand3_cfg, MIKROBUS_1 );
    if ( ONE_WIRE_ERROR == expand3_init( &expand3, &expand3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND3_ERROR == expand3_default_cfg ( &expand3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t out_state = 0;
    static uint8_t in_state = 0;
    if ( ( EXPAND3_OK == expand3_write_state ( &expand3, out_state ) ) && 
         ( EXPAND3_OK == expand3_read_last_state ( &expand3, &out_state ) ) )
    {
        log_printf( &logger, " Output state: 0x%.2X\r\n\n", out_state++ );
    }
    if ( EXPAND3_OK == expand3_read_current_state ( &expand3, &in_state ) )
    {
        log_printf( &logger, " Input state: 0x%.2X\r\n\n", in_state );
    }
    Delay_ms ( 500 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
