/*!
 * @file main.c
 * @brief Serializer Click example
 *
 * # Description
 * This example demonstrates the use of a Serializer Click board by reading
 * the state of all inputs and displaying the results on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the state of all inputs and displays the results on the USB UART
 * approximately once per second. Also, if there's any fault indication detected,
 * it will be displayed accordingly.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "serializer.h"

static serializer_t serializer;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    serializer_cfg_t serializer_cfg;  /**< Click config object. */

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
    serializer_cfg_setup( &serializer_cfg );
    SERIALIZER_MAP_MIKROBUS( serializer_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == serializer_init( &serializer, &serializer_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t input_data = 0;
    err_t status = serializer_read_input ( &serializer, &input_data );
    
    if ( SERIALIZER_ERROR != status )
    {
        for ( uint8_t cnt = 0; cnt < 8; cnt++ )
        {
            log_printf( &logger, " IN%u: %s\r\n", ( uint16_t ) cnt + 1, 
                                                  ( char * ) ( ( input_data & ( 1 << cnt ) ) ? "High" : "Low" ) );
        }
        if ( status & SERIALIZER_STATUS_UNDERVOLTAGE )
        {
            log_info( &logger, "Undervoltage fault" );
        }
        if ( status & SERIALIZER_STATUS_OVERTEMPERATURE )
        {
            log_info( &logger, "Overtemperature fault" );
        }
        log_printf( &logger, "\r\n" );
        Delay_ms ( 1000 );
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
