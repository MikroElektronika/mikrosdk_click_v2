/*!
 * @file main.c
 * @brief Balancer4 Click example
 *
 * # Description
 * This example demonstrates the use of Balancer 4 click board by configuring
 * the click board for charging and then reading the status and fault registers.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board for charging.
 *
 * ## Application Task
 * Reads and displays the status and fault registers on the USB UART every 500ms approximately.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "balancer4.h"

static balancer4_t balancer4;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    balancer4_cfg_t balancer4_cfg;  /**< Click config object. */

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
    balancer4_cfg_setup( &balancer4_cfg );
    BALANCER4_MAP_MIKROBUS( balancer4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == balancer4_init( &balancer4, &balancer4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BALANCER4_ERROR == balancer4_default_cfg ( &balancer4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t status, fault;
    if ( BALANCER4_OK == balancer4_read_register ( &balancer4, BALANCER4_REG_STATUS, &status ) )
    {
        log_printf ( &logger, "\r\n - STATUS - \r\n", status );
        log_printf ( &logger, " Battery status: " );
        if ( status & BALANCER4_STATUS_BATTERY_MISSING )
        {
            log_printf ( &logger, "missing\r\n" );
        }
        else
        {
            log_printf ( &logger, "present\r\n" );
            log_printf ( &logger, " Charging status: " );
            switch ( status & BALANCER4_STATUS_CHG_STAT_MASK )
            {
                case BALANCER4_STATUS_NOT_CHARGING:
                {
                    log_printf ( &logger, "not charging\r\n" );
                    break;
                }
                case BALANCER4_STATUS_PRE_CHARGE:
                {
                    log_printf ( &logger, "pre-charge\r\n" );
                    break;
                }
                case BALANCER4_STATUS_CONSTANT_CHARGE:
                {
                    log_printf ( &logger, "constant current or constant voltage charge\r\n" );
                    break;
                }
                case BALANCER4_STATUS_CHARGING_COMPLETE:
                {
                    log_printf ( &logger, "charging complete\r\n" );
                    break;
                }
            }
        }
    }
    if ( BALANCER4_OK == balancer4_read_register ( &balancer4, BALANCER4_REG_FAULT, &fault ) )
    {
        if ( fault )
        {
            log_printf ( &logger, "\r\n - FAULT - \r\n" );
            if ( fault & BALANCER4_FAULT_WD )
            {
                log_printf ( &logger, " The watchdog timer has expired\r\n" );
            }
            if ( fault & BALANCER4_FAULT_INPUT )
            {
                log_printf ( &logger, " Input OVP has occured\r\n" );
            }
            if ( fault & BALANCER4_FAULT_THERMAL_SD )
            {
                log_printf ( &logger, " Thermal shutdown\r\n" );
            }
            if ( fault & BALANCER4_FAULT_TIMER )
            {
                log_printf ( &logger, " The safety timer has expired\r\n" );
            }
            if ( fault & BALANCER4_FAULT_BAT )
            {
                log_printf ( &logger, " Battery OVP has occured\r\n" );
            }
            switch ( fault & BALANCER4_FAULT_NTC_MASK )
            {
                case BALANCER4_FAULT_NTC_COLD:
                {
                    log_printf ( &logger, " An NTC cold fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_COOL:
                {
                    log_printf ( &logger, " An NTC cool fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_WARM:
                {
                    log_printf ( &logger, " An NTC warm fault has occured\r\n" );
                    break;
                }
                case BALANCER4_FAULT_NTC_HOT:
                {
                    log_printf ( &logger, " An NTC hot fault has occured\r\n" );
                    break;
                }
            }
        }
    }
    Delay_ms ( 500 );
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
