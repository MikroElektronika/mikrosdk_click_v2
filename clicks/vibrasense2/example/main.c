/*!
 * @file main.c
 * @brief VibraSense2 Click example
 *
 * # Description
 * This example shows capabilities of Vibra Sense 2 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes I2C driver and makes an initial log.
 *
 * ## Application Task
 * Demonstrates use of Vibra Sense 2 click board by checking
 * vibration levels and displaying changes via USART terminal.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "vibrasense2.h"

static vibrasense2_t vibrasense2;
static log_t logger;

int8_t old_val;
int8_t new_val;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vibrasense2_cfg_t vibrasense2_cfg;  /**< Click config object. */

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
    vibrasense2_cfg_setup( &vibrasense2_cfg );
    VIBRASENSE2_MAP_MIKROBUS( vibrasense2_cfg, MIKROBUS_1 );
    err_t init_flag = vibrasense2_init( &vibrasense2, &vibrasense2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    old_val = VIBRASENSE2_ERROR;
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------------------\r\n" );
}

void application_task ( void ) {
    new_val = vibrasense2_vibration_level( &vibrasense2 );
    Delay_ms( 100 );
    if ( new_val != old_val ) {
        switch ( new_val ) {
            case VIBRASENSE2_VIBRA_LVL_0: {
                log_printf( &logger, "            No Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_1: {
                log_printf( &logger, " Vibration level : Marginal Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_2: {
                log_printf( &logger, " Vibration level : Slight Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_3: {
                log_printf( &logger, " Vibration level : Enhanced Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_4: {
                log_printf( &logger, " Vibration level : Moderate Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_5: {
                log_printf( &logger, " Vibration level : High Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            case VIBRASENSE2_VIBRA_LVL_6: {
                log_printf( &logger, " Vibration level : Severe Vibration \r\n" );
                log_printf( &logger, "-------------------------------------\r\n" );
                break;
            }
            default: {
                log_printf( &logger, "Error occured!" );
                log_printf( &logger, "-------------------------------------\r\n" );
            }
        }
        old_val = new_val;
    }
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
