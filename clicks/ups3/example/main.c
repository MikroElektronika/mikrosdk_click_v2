/*!
 * @file main.c
 * @brief UPS 3 Click Example.
 *
 * # Description
 * This application demonstrates the use of UPS 3 click board. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enable's - GPIO, also write log.
 *
 * ## Application Task
 * With this example we show the operation of UPS 3 clicks.
 * This example shows an autonomously transition from charge to backup mode.
 * Results are being sent to the Usart Terminal where you can track their changes. 
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ups3.h"

#define UPS3_STATUS_OLD         0x00
#define UPS3_STATUS_NEW         0x01

static ups3_t ups3;    /**< UPS 3 Click driver object. */
static log_t logger;   /**< Logger object. */

static uint8_t cok_status = UPS3_STATUS_OLD;
static uint8_t new_status = UPS3_STATUS_NEW;

void application_init ( void ) {
    log_cfg_t log_cfg;    /**< Logger config object. */
    ups3_cfg_t ups3_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ups3_cfg_setup( &ups3_cfg );
    UPS3_MAP_MIKROBUS( ups3_cfg, MIKROBUS_1 );
    if ( ups3_init( &ups3, &ups3_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    ups3_default_cfg ( &ups3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) {      
    if ( ups3_get_error( &ups3 ) == UPS3_GET_ERROR_CMPIN_OK ) {
        if ( ups3_get_cap_ok( &ups3 ) != cok_status ) {
            new_status = UPS3_STATUS_NEW; 
            cok_status = ups3_get_cap_ok( &ups3 );
        } else {
            new_status = UPS3_STATUS_OLD;    
        }
    
        if ( new_status == UPS3_STATUS_NEW ) {
            ups3_hw_reset( &ups3 );
            new_status = UPS3_STATUS_OLD;
        }
        
        if ( ( ups3_get_chrg( &ups3 ) == UPS3_GET_CHRG_BACKUP_MODE ) && 
             ( ups3_get_cap_ok( &ups3 ) == UPS3_GET_CAP_OK_FBV_LOW ) ) {
            log_printf( &logger, "      Backup Mode ON      \r\n" );
        }
        
        if ( ups3_get_cap_ok( &ups3 ) == UPS3_GET_CAP_OK_FBV_HIGH ) {
            log_printf( &logger, "       Vcap charged       \r\n" );
        }
    } else {
        log_printf( &logger, "      Backup Mode OFF     \r\n" );
        log_printf( &logger, " Turn ON the Power Supply \r\n" );
            
        while ( ups3_get_error( &ups3 ) == UPS3_GET_ERROR_CMPIN_EMPTY ) {
            Delay_ms( 100 );   
        }
            
        ups3_hw_reset( &ups3 );
        Delay_ms( 100 );
    }
    
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
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
