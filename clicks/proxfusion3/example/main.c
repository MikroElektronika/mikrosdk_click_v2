/*!
 * @file main.c
 * @brief ProxFusion3 Click example
 *
 * # Description
 * Display information about the last detected touch.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver, read and display version info value
 * and start to write log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the ProxFusion 3 click board.
 * In this example, we check the touch event and display the last detected touch. 
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "proxfusion3.h"

static proxfusion3_t proxfusion3;
static log_t logger;

static uint8_t product_number;
static uint8_t software_version;

void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proxfusion3_cfg_t proxfusion3_cfg;  /**< Click config object.  */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n---------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    proxfusion3_cfg_setup( &proxfusion3_cfg );
    PROXFUSION3_MAP_MIKROBUS( proxfusion3_cfg, MIKROBUS_1 );
    err_t init_flag = proxfusion3_init( &proxfusion3, &proxfusion3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    proxfusion3_default_cfg ( &proxfusion3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 500 );
    
    proxfusion3_get_version_info( &proxfusion3, &product_number, &software_version );
    log_printf( &logger, "  Product Number   : 0x%.2X \r\n", ( uint16_t ) product_number );
    log_printf( &logger, "  Software Version : 0x%.2X \r\n", ( uint16_t ) software_version );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "      Touch Detection      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}

void application_task ( void ) {
    if ( proxfusion3_check_touch_event( &proxfusion3 ) == PROXFUSION3_EVENT_TOUCH ) {        
        uint8_t touch_data = proxfusion3_get_touch( &proxfusion3 );
        Delay_ms( 100 );
        
        switch ( touch_data ) {
            case PROXFUSION3_TOUCH_POS_8: {
                log_printf( &logger, "       >>>   8   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_7: {
                log_printf( &logger, "       >>>   7   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_6: {
                log_printf( &logger, "       >>>   6   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_5: {
                log_printf( &logger, "       >>>   5   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_4: {
                log_printf( &logger, "       >>>   4   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_3: {
                log_printf( &logger, "       >>>   3   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_2: {
                log_printf( &logger, "       >>>   2   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_1: {
                log_printf( &logger, "       >>>   1   <<<       \r\n" );
                break;
            }
            default: {
                Delay_ms( 10 );
                break;
            }
        }
        
        Delay_ms( 10 );
    } else {
        Delay_ms( 10 );
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
