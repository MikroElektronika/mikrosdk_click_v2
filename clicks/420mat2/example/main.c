/*!
 * @file main.c
 * @brief 4-20mA T 2 Click example
 *
 * # Description
 * This example demonstrates the use of 4-20mA T 2 Click board™.
 * This driver provides functions to configure 
 * analog output current transfer over an industry standard 4-20mA current loop.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, default settings turn on the device.
 *
 * ## Application Task
 * This example demonstrates the use of the 4-20mA T 2 Click board™.
 * This example periodically changes the analog output current transfer 
 * from 4mA to 20mA and display status every 5 seconds.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c420mat2.h"

static c420mat2_t c420mat2;
static log_t logger;
static c420mat2_status_t status;

void display_status ( void )
{
    log_printf( &logger, " Status: \r\n" );
    if ( C420MAT2_STATUS_ERROR == status.ferr_sts )
    {
        log_printf( &logger, " - A frame error has occurred.\r\n" );
    }
    else
    {
        log_printf( &logger, " - No frame error occurred.\r\n" );
    }

    if ( C420MAT2_STATUS_ERROR == status.spi_timeout_err )
    {
        log_printf( &logger, " - The SPI interface has not received a valid command.\r\n" );
    }
    else
    {
        log_printf( &logger, " - The SPI interface has received a valid command.\r\n" );
    }

    if ( C420MAT2_STATUS_ERROR == status.loop_sts )
    {
        log_printf( &logger, " - A status loop error has occurred.\r\n" );
    }
    else
    {
        log_printf( &logger, " - No status loop error has occurred.\r\n" );
    }

    if ( C420MAT2_STATUS_ERROR == status.curr_loop_sts )
    {
        log_printf( &logger, " - A current loop error is occurring.\r\n" );
    }
    else
    {
        log_printf( &logger, " - No current loop error is occurring.\r\n" );
    }
    log_printf( &logger, " ----------------------------\r\n" );
}

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c420mat2_cfg_t c420mat2_cfg;  /**< Click config object. */

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
    c420mat2_cfg_setup( &c420mat2_cfg );
    C420MAT2_MAP_MIKROBUS( c420mat2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c420mat2_init( &c420mat2, &c420mat2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( C420MAT2_ERROR == c420mat2_default_cfg ( &c420mat2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, " -----------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 4.0 ) )
    {
        log_printf( &logger, " Loop Current:  4.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 10.0 ) )
    {
        log_printf( &logger, " Loop Current: 10.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 15.0 ) )
    {
        log_printf( &logger, " Loop Current: 15.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }

    if ( C420MAT2_OK == c420mat2_set_output_current( &c420mat2, 20.0 ) )
    {
        log_printf( &logger, " Loop Current: 20.0 mA \r\n" );
        log_printf( &logger, " - - - - - - - - - - - - - - -\r\n" );
        if ( C420MAT2_OK == c420mat2_get_status ( &c420mat2, &status ) )
        {
            display_status( );    
        }
        Delay_ms( 5000 );
    }
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
