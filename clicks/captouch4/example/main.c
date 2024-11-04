/*!
 * @file main.c
 * @brief Cap Touch 4 Click example
 *
 * # Description
 * This example demonstrates the use of Cap Touch 4 Click board by reading
 * the proximity, touch, and movement events.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the proximity, touch, and movement events and approximately displays
 * the results on the USB UART every 200ms. The capacitance counts and the long-term
 * average values are also displayed.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "captouch4.h"

static captouch4_t captouch4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    captouch4_cfg_t captouch4_cfg;  /**< Click config object. */

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
    captouch4_cfg_setup( &captouch4_cfg );
    CAPTOUCH4_MAP_MIKROBUS( captouch4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == captouch4_init( &captouch4, &captouch4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CAPTOUCH4_ERROR == captouch4_default_cfg ( &captouch4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t sys_flags = 0;
    uint8_t movement = 0;
    uint16_t cap_counts = 0;
    uint16_t lta = 0;
    if ( CAPTOUCH4_OK == captouch4_read_system_flags ( &captouch4, &sys_flags ) )
    {
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_PROX )
        {
            log_printf( &logger, " Proximity detected\r\n" );
        }
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_TOUCH )
        {
            log_printf( &logger, " Touch detected\r\n" );
        }
        if ( sys_flags & CAPTOUCH4_SYSFLAGS0_MOVEMENT )
        {
            if ( CAPTOUCH4_OK == captouch4_read_movement ( &captouch4, &movement ) )
            {
                log_printf( &logger, " Movement detected: %u\r\n", ( uint16_t ) movement );
            }
        }
        if ( ( sys_flags & CAPTOUCH4_SYSFLAGS0_MOVEMENT ) || 
             ( sys_flags & CAPTOUCH4_SYSFLAGS0_PROX ) || 
             ( sys_flags & CAPTOUCH4_SYSFLAGS0_TOUCH ) )
        {
            if ( CAPTOUCH4_OK == captouch4_read_cap_counts ( &captouch4, &cap_counts ) )
            {
                log_printf( &logger, " Capacitance counts: %u\r\n", cap_counts );
            }
            if ( CAPTOUCH4_OK == captouch4_read_lta ( &captouch4, &lta ) )
            {
                log_printf( &logger, " Long-term average: %u\r\n\n", lta );
            }
        }
        else
        {
            log_printf( &logger, " No detected events\r\n\n" );
        }
    }
    Delay_ms ( 200 );
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
