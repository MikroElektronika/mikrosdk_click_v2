/*!
 * @file main.c
 * @brief Rotary B Click example
 *
 * # Description
 * The demo application controls led on Click with rotary on board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver, set initial states, 
 * set RST logic high and performs device configuration.
 *
 * ## Application Task
 * Show functionality of Rotary B Click, rotating and turn on/off led's,
 * using the SPI interface.
 *
 * @note
 * In orther to use all of the Clicks functionality, pull down INT pin.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "rotaryb.h"

static rotaryb_t rotaryb;
static log_t logger;

static uint8_t start_status;
static uint8_t old_state;
static uint8_t new_state;
static uint8_t old__rot_state;
static uint8_t new_rotate_state;
static uint8_t led_state;
static uint16_t led_data;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryb_cfg_t rotaryb_cfg;  /**< Click config object. */

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

    rotaryb_cfg_setup( &rotaryb_cfg );
    ROTARYB_MAP_MIKROBUS( rotaryb_cfg, MIKROBUS_1 );
    err_t init_flag  = rotaryb_init( &rotaryb, &rotaryb_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    
    led_data = 0x0001;
    old_state = 0;
    new_state = 1;
    old__rot_state = 0;
    new_rotate_state = 1;
}

void application_task ( void ) {
    rotaryb_turn_on_led_by_data( &rotaryb, led_data );

//     Push button
    if ( rotaryb_button_push( &rotaryb ) ) {
        new_state = 1;
        if ( new_state == 1 && old_state == 0 ) {
            old_state = 1;
            led_state = ( led_state + 1 ) % 5;
            if ( led_state == 4 ) {
                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryb_turn_on_led_by_data( &rotaryb, 0xAAAA );
                    Delay_ms ( 100 );
                    rotaryb_turn_on_led_by_data( &rotaryb, 0x5555 );
                    Delay_ms ( 100 );
                }

                for ( old_state = 0; old_state < 17; old_state++ ) {
                    rotaryb_turn_on_led_by_position( &rotaryb, old_state );
                    Delay_ms ( 100 );
                }

                led_state = 0;
                led_data = rotaryb_get_led_data( led_state );
            }
            else {
                led_data = rotaryb_get_led_data( led_state );
            }
        }
    }
    else {
        old_state = 0;
    }

//     Rotate Clockwise and CounterClockwise
    if ( rotaryb_get_eca_state( &rotaryb ) == rotaryb_get_ecb_state( &rotaryb ) ) {
        old__rot_state = 0;
        start_status = rotaryb_get_eca_state( &rotaryb ) && rotaryb_get_ecb_state( &rotaryb );
    }
    else {
        new_rotate_state = 1;
        if ( new_rotate_state != old__rot_state ) {
            old__rot_state = 1;
            if ( start_status != rotaryb_get_eca_state( &rotaryb ) ) {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
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
