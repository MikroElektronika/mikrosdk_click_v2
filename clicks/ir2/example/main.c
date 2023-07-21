/*!
 * @file main.c
 * @brief IR2 Click example
 *
 * # Description
 * This example demonstrates the use of an IR 2 click board by showing
 * the communication between the two click boards configured as a receiver and transmitter
 * using the NEC protocol.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and displays the selected application mode.
 *
 * ## Application Task
 * Depending on the selected mode, it sends a desired message using NEC protocol or
 * reads all the received data and displays them on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ir2.h"

#define IR2_TRANSMITTER_MODE    // Uncomment this line to switch to the transmitter mode

#define IR2_ADDRESS     0xAB
#define IR2_DATA        "MikroE - IR 2 click board\r\n"

static ir2_t ir2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ir2_cfg_t ir2_cfg;  /**< Click config object. */

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
    ir2_cfg_setup( &ir2_cfg );
    IR2_MAP_MIKROBUS( ir2_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == ir2_init( &ir2, &ir2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
#ifdef IR2_TRANSMITTER_MODE
    log_printf( &logger, "-  Transmitter mode   - \r\n" );
#else
    log_printf( &logger, "-    Receiver mode    - \r\n" );
#endif
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef IR2_TRANSMITTER_MODE
    log_printf( &logger, " Sending message." );
    
    for ( uint8_t cnt = 0; cnt < sizeof ( IR2_DATA ); cnt++ )
    {
        ir2_nec_send_data ( &ir2, IR2_ADDRESS, IR2_DATA[ cnt ] );
        log_printf( &logger, "." );
    }
    
    log_printf( &logger, "\r\n Message has been sent! \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - \r\n" );
    Delay_ms( 500 );
#else
    uint8_t address;
    uint8_t rx_data;
    
    if ( IR2_OK == ir2_nec_read_data ( &ir2, &address, &rx_data ) )
    {
        log_printf( &logger, "Address: 0x%.2X, Data: %c\r\n", ( uint16_t ) address, rx_data );
    }
#endif
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
