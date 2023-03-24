/*!
 * @file main.c
 * @brief Color 16 Click example
 *
 * # Description
 * This example demonstrates the use of Color 16 click by reading and displaying
 * the values from all 14 channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Waits for the spectral measurement complete flag and then reads data from all 14 channels
 * in 3 cycles, and displays the results on the USB UART every 300ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "color16.h"

static color16_t color16;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color16_cfg_t color16_cfg;  /**< Click config object. */

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
    color16_cfg_setup( &color16_cfg );
    COLOR16_MAP_MIKROBUS( color16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color16_init( &color16, &color16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR16_ERROR == color16_default_cfg ( &color16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    color16_data_t color_data;
    if ( COLOR16_OK == color16_read_data ( &color16, &color_data ) )
    {
        log_printf ( &logger, " STATUS:          0x%.2X\r\n", ( uint16_t ) color_data.status );
        log_printf ( &logger, " ASTATUS:         0x%.2X\r\n", ( uint16_t ) color_data.astatus );
        log_printf ( &logger, " ------- Cycle 1 -------\r\n" );
        log_printf ( &logger, " Channel FZ:      %u\r\n", color_data.ch_fz );
        log_printf ( &logger, " Channel FY:      %u\r\n", color_data.ch_fy );
        log_printf ( &logger, " Channel FXL:     %u\r\n", color_data.ch_fxl );
        log_printf ( &logger, " Channel NIR:     %u\r\n", color_data.ch_nir );
        log_printf ( &logger, " Channel 2xVIS_1: %u\r\n", color_data.ch_2x_vis_1 );
        log_printf ( &logger, " Channel FD_1:    %u\r\n", color_data.ch_fd_1 );
        log_printf ( &logger, " ------- Cycle 2 -------\r\n" );
        log_printf ( &logger, " Channel F2:      %u\r\n", color_data.ch_f2 );
        log_printf ( &logger, " Channel F3:      %u\r\n", color_data.ch_f3 );
        log_printf ( &logger, " Channel F4:      %u\r\n", color_data.ch_f4 );
        log_printf ( &logger, " Channel F6:      %u\r\n", color_data.ch_f6 );
        log_printf ( &logger, " Channel 2xVIS_2: %u\r\n", color_data.ch_2x_vis_2 );
        log_printf ( &logger, " Channel FD_2:    %u\r\n", color_data.ch_fd_2 );
        log_printf ( &logger, " ------- Cycle 3 -------\r\n" );
        log_printf ( &logger, " Channel F1:      %u\r\n", color_data.ch_f1 );
        log_printf ( &logger, " Channel F5:      %u\r\n", color_data.ch_f5 );
        log_printf ( &logger, " Channel F7:      %u\r\n", color_data.ch_f7 );
        log_printf ( &logger, " Channel F8:      %u\r\n", color_data.ch_f8 );
        log_printf ( &logger, " Channel 2xVIS_3: %u\r\n", color_data.ch_2x_vis_3 );
        log_printf ( &logger, " Channel FD_3:    %u\r\n", color_data.ch_fd_3 );
        log_printf ( &logger, " -----------------------\r\n\n" );
        Delay_ms ( 300 );
    }
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
