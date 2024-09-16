/*!
 * @file main.c
 * @brief Brushless 30 Click example
 *
 * # Description
 * This example configures the Brushless 30 click board and makes it ready for
 * the motor control over 6 PWM input signals.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Monitors the DIAG pin state, displays the STAT1 and STAT2 registers on the USB UART,
 * and clears the set flags.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "brushless30.h"

static brushless30_t brushless30;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    brushless30_cfg_t brushless30_cfg;  /**< Click config object. */

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
    brushless30_cfg_setup( &brushless30_cfg );
    BRUSHLESS30_MAP_MIKROBUS( brushless30_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == brushless30_init( &brushless30, &brushless30_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BRUSHLESS30_ERROR == brushless30_default_cfg ( &brushless30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, " Click is configured successfully.\r\n" );
    log_printf( &logger, " Apply a 6 PWM signals to UVW H/L pins to drive the motor.\r\n" );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint16_t status = 0;
    if ( !brushless30_get_diag_pin ( &brushless30 ) )
    {
        if ( BRUSHLESS30_OK == brushless30_read_reg ( &brushless30, BRUSHLESS30_REG_STAT1, &status ) )
        {
            if ( status )
            {
                log_printf( &logger, " STAT1: 0x%.4X\r\n", status );
                if ( BRUSHLESS30_OK == brushless30_write_reg ( &brushless30, BRUSHLESS30_REG_STAT1, status ) )
                {
                    log_printf( &logger, " STAT1: cleared\r\n" );
                }
            }
        }
        
        if ( BRUSHLESS30_OK == brushless30_read_reg ( &brushless30, BRUSHLESS30_REG_STAT2, &status ) )
        {
            if ( status )
            {
                log_printf( &logger, " STAT2: 0x%.4X\r\n", status );
                if ( BRUSHLESS30_OK == brushless30_write_reg ( &brushless30, BRUSHLESS30_REG_STAT2, status ) )
                {
                    log_printf( &logger, " STAT2: cleared\r\n" );
                }
            }
        }
        
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
