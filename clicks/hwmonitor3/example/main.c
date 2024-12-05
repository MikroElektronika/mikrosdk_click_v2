/*!
 * @file main.c
 * @brief HW Monitor 3 Click example
 *
 * # Description
 * This example demonstrates the use of HW Monitor 3 Click board by reading and
 * displaying the voltage level from 6 analog input channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the voltage level from all 6 analog input channels and displays
 * the results on the USB UART once per second approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hwmonitor3.h"

static hwmonitor3_t hwmonitor3;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hwmonitor3_cfg_t hwmonitor3_cfg;  /**< Click config object. */

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
    hwmonitor3_cfg_setup( &hwmonitor3_cfg );
    HWMONITOR3_MAP_MIKROBUS( hwmonitor3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hwmonitor3_init( &hwmonitor3, &hwmonitor3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HWMONITOR3_ERROR == hwmonitor3_default_cfg ( &hwmonitor3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    hwmonitor3_ch_mon_t ch_mon;
    if ( HWMONITOR3_OK == hwmonitor3_read_voltage ( &hwmonitor3, &ch_mon ) )
    {
        log_printf ( &logger, " CH1: %.3f V\r\n", ch_mon.ch1_v );
        log_printf ( &logger, " CH2: %.3f V\r\n", ch_mon.ch2_v );
        log_printf ( &logger, " CH3: %.3f V\r\n", ch_mon.ch3_v );
        log_printf ( &logger, " CH4: %.3f V\r\n", ch_mon.ch4_v );
        log_printf ( &logger, " CH5: %.3f V\r\n", ch_mon.ch5_v );
        log_printf ( &logger, " CH6: %.3f V\r\n\n", ch_mon.ch6_v );
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
