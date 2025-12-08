/*!
 * @file main.c
 * @brief UART I2C SPI 2 Click example
 *
 * # Description
 * This example demonstrates the use of the UART I2C SPI 2 Click board.
 * It sends a predefined demo message to both UART0 and UART1 interfaces,
 * then reads back any received data and logs the results on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and UART I2C SPI 2 Click, and applies the default 
 * configuration which sets the UART0 to 115200-8N1 and UART1 to 9600-8N1.
 *
 * ## Application Task
 * Alternately selects UART0 and UART1, sends the demo message, 
 * reads back data from the RX FIFO, and logs the transmitted 
 * and received strings every second.
 *
 * @note
 * Ensure that the connected devices on UART0 and UART1 are properly 
 * configured to communicate at the same baud rate and parameters. 
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "uarti2cspi2.h"

#define DEMO_MESSAGE "UART I2C/SPI 2 Click - demo message\r\n"

static uarti2cspi2_t uarti2cspi2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uarti2cspi2_cfg_t uarti2cspi2_cfg;  /**< Click config object. */

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
    uarti2cspi2_cfg_setup( &uarti2cspi2_cfg );
    UARTI2CSPI2_MAP_MIKROBUS( uarti2cspi2_cfg, MIKROBUS_1 );
    err_t init_flag = uarti2cspi2_init( &uarti2cspi2, &uarti2cspi2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UARTI2CSPI2_ERROR == uarti2cspi2_default_cfg ( &uarti2cspi2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t fifo_data[ UARTI2CSPI2_FIFO_LEN ] = { 0 };
    uint8_t fifo_lvl = 0;
    uarti2cspi2_select_uart_0 ( &uarti2cspi2 );
    if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, "U0: ", 4 ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, DEMO_MESSAGE, strlen ( DEMO_MESSAGE ) ) )
        {
            log_printf ( &logger, "\r\nSend to U0: %s", DEMO_MESSAGE );
        }
    }
    if ( UARTI2CSPI2_OK == uarti2cspi2_read_reg ( &uarti2cspi2, UARTI2CSPI2_REG_RXFIFOLVL, &fifo_lvl ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_read_data ( &uarti2cspi2, fifo_data, fifo_lvl ) )
        {
            log_printf ( &logger, "Read from U0: %s\r\n", fifo_data );
        }
    }
    uarti2cspi2_select_uart_1 ( &uarti2cspi2 );
    if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, "U1: ", 4 ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_write_data ( &uarti2cspi2, DEMO_MESSAGE, strlen ( DEMO_MESSAGE ) ) )
        {
            log_printf ( &logger, "Send to U1: %s", DEMO_MESSAGE );
        }
    }
    if ( UARTI2CSPI2_OK == uarti2cspi2_read_reg ( &uarti2cspi2, UARTI2CSPI2_REG_RXFIFOLVL, &fifo_lvl ) )
    {
        if ( UARTI2CSPI2_OK == uarti2cspi2_read_data ( &uarti2cspi2, fifo_data, fifo_lvl ) )
        {
            log_printf ( &logger, "Read from U1: %s\r\n", fifo_data );
        }
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
