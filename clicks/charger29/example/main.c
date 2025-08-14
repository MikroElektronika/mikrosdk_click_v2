/*!
 * @file main.c
 * @brief Charger 29 Click example
 *
 * # Description
 * This example demonstrates the use of the Charger 29 Click board.
 * The application initializes the device and periodically checks the charging status.
 * The status is displayed over the UART terminal and reflects whether the battery is 
 * charging in constant current (CC) mode, constant voltage (CV) mode, fully charged,
 * or not charging.
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Charger 29 Click driver and applies default configuration.
 *
 * ## Application Task
 * Periodically reads and logs the charging status once per second.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "charger29.h"

static charger29_t charger29;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger29_cfg_t charger29_cfg;  /**< Click config object. */

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
    charger29_cfg_setup( &charger29_cfg );
    CHARGER29_MAP_MIKROBUS( charger29_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger29_init( &charger29, &charger29_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER29_ERROR == charger29_default_cfg ( &charger29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint8_t chg_stat = 255;
    charger29_status_t status;
    if ( CHARGER29_OK == charger29_read_status ( &charger29, &status ) )
    {
        if ( chg_stat != ( status.stat0 & CHARGER29_STAT0_CHG_STAT_MASK ) )
        {
            chg_stat = ( status.stat0 & CHARGER29_STAT0_CHG_STAT_MASK );
            switch ( chg_stat )
            {
                case CHARGER29_STAT0_CHG_STAT_NOT_CHARGING:
                {
                    log_printf ( &logger, " Not Charging while charging is enabled\r\n\n" );
                    break;
                }
                case CHARGER29_STAT0_CHG_STAT_CC_CHARGING:
                {
                    log_printf ( &logger, " Constant Current Charging\r\n\n" );
                    break;
                }
                case CHARGER29_STAT0_CHG_STAT_CV_CHARGING:
                {
                    log_printf ( &logger, " Constant Voltage Charging\r\n\n" );
                    break;
                }
                case CHARGER29_STAT0_CHG_STAT_CHARGE_DONE:
                {
                    log_printf ( &logger, " Charge Done or charging is disabled\r\n\n" );
                    break;
                }
                default:
                {
                    log_printf ( &logger, " Unknown Charging Status\r\n\n" );
                    break;
                }
            }
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
