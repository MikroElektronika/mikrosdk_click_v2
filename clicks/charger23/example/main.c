/*!
 * @file main.c
 * @brief Charger 23 Click Example.
 *
 * # Description
 * This example demonstrates the use of Charger 23 click board by enabling the device
 * and then reading and displaying the charger status.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device.
 *
 * ## Application Task
 * Reads the charger state and displays it on the USB UART on change.
 *
 * @note
 * Depending on the CURR SEL onboard jumper position this click board is able to
 * charge batteries of 250mAh or 500mAh rated capacity.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger23.h"

static charger23_t charger23;   /**< Charger 23 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger23_cfg_t charger23_cfg;  /**< Click config object. */

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
    charger23_cfg_setup( &charger23_cfg );
    CHARGER23_MAP_MIKROBUS( charger23_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger23_init( &charger23, &charger23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger23_enable_device ( &charger23 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t chg_state_old = CHARGER23_STATE_UNKNOWN;
    uint8_t chg_state = charger23_get_charger_state ( &charger23 );
    if ( chg_state_old != chg_state )
    {
        chg_state_old = chg_state;
        log_printf( &logger, "\r\n Charger state: " );
        switch ( chg_state )
        {
            case CHARGER23_STATE_IDLE:
            {
                log_printf( &logger, "Charge completed with no fault (Inhibit) or Standby\r\n" );
                break;
            }
            case CHARGER23_STATE_CHARGING:
            {
                log_printf( &logger, "Charging in one of the three modes\r\n" );
                break;
            }
            case CHARGER23_STATE_FAULT:
            {
                log_printf( &logger, "Fault\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "Unknown\r\n" );
                break;
            }
        }
        Delay_ms ( 100 );
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
