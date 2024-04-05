/*!
 * @file main.c
 * @brief Rotary R 2 Click example
 *
 * # Description
 * This library contains the API for the Rotary R 2 Click driver 
 * to control LEDs states and a rotary encoder position readings.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After the driver init, the app executes a default configuration and turn off all LEDs.
 *
 * ## Application Task
 * This example demonstrates the use of the Rotary R 2 Click board.
 * The demo example shows the functionality of a rotary encoder used to control LEDs.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rotaryr2.h"

#define ROTARYR2_ONE_LED          ROTARYR2_SET_LED_DATA_1
#define ROTARYR2_TWO_LED          ROTARYR2_SET_LED_DATA_1  | ROTARYR2_SET_LED_DATA_9
#define ROTARYR2_FOUR_LED         ROTARYR2_SET_LED_DATA_1  | ROTARYR2_SET_LED_DATA_5  | \
                                  ROTARYR2_SET_LED_DATA_9  | ROTARYR2_SET_LED_DATA_13 
#define ROTARYR2_EIGHT_LED        ROTARYR2_SET_LED_DATA_1  | ROTARYR2_SET_LED_DATA_3  | \
                                  ROTARYR2_SET_LED_DATA_5  | ROTARYR2_SET_LED_DATA_7  | \
                                  ROTARYR2_SET_LED_DATA_9  | ROTARYR2_SET_LED_DATA_11 | \
                                  ROTARYR2_SET_LED_DATA_13 | ROTARYR2_SET_LED_DATA_15
#define ROTARYR2_EIGHT_LED_INV    ROTARYR2_SET_LED_DATA_2  | ROTARYR2_SET_LED_DATA_4  | \
                                  ROTARYR2_SET_LED_DATA_6  | ROTARYR2_SET_LED_DATA_8  | \
                                  ROTARYR2_SET_LED_DATA_10 | ROTARYR2_SET_LED_DATA_12 | \
                                  ROTARYR2_SET_LED_DATA_14 | ROTARYR2_SET_LED_DATA_16

static rotaryr2_t rotaryr2;
static log_t logger;

static uint8_t start_rot_status = 0;
static uint8_t led_demo_state = 0;
static uint8_t old_state = 0;
static uint8_t new_state = 1;
static uint8_t old_rot_state = 0;
static uint8_t new_rot_state = 1;
static uint16_t led_data = 1;

/**
 * @brief Rotary R 2 select LED demo data function.
 * @details This function selects one of the four LED demo data 
 * based on the current state of the LED demo.
 * @return LED demo data:
 *         @li @c 0x0001 (ROTARYR2_ONE_LED)   - Turn ON LED[1],
 *         @li @c 0x0101 (ROTARYR2_TWO_LED)   - Turn ON LED[1,9],
 *         @li @c 0x0101 (ROTARYR2_FOUR_LED)  - Turn ON LED[1,5,9,13],
 *         @li @c 0x5555 (ROTARYR2_EIGHT_LED) - Turn ON LED[1,3,5,7,9,11,13,15].
 */
static uint16_t rotaryr2_sel_led_demo_data ( uint8_t led_demo_state );

/**
 * @brief Rotary R 2 switch detection function.
 * @details This function is used for the switch state detection.
 * @return Nothing.
 */
static void rotaryr2_switch_detection ( void );

/**
 * @brief Rotary R 2 encoder mechanism function.
 * @details This function is used to control the state of the LEDs 
 * by detecting the rotation direction of the rotary encoder.
 * @return Nothing.
 */
static void rotaryr2_encoder_mechanism ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryr2_cfg_t rotaryr2_cfg;  /**< Click config object. */

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
    rotaryr2_cfg_setup( &rotaryr2_cfg );
    ROTARYR2_MAP_MIKROBUS( rotaryr2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rotaryr2_init( &rotaryr2, &rotaryr2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYR2_ERROR == rotaryr2_default_cfg ( &rotaryr2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( ROTARYR2_OK == rotaryr2_set_led_data( &rotaryr2, led_data ) )
    {
        rotaryr2_switch_detection( );
        rotaryr2_encoder_mechanism( );
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

static uint16_t rotaryr2_sel_led_demo_data ( uint8_t led_demo_state ) 
{
    switch ( led_demo_state ) 
    {
        case 0: 
        {
            return ROTARYR2_ONE_LED;
            break;
        }
        case 1: 
        {
            return ROTARYR2_TWO_LED;
            break;
        }
        case 2: 
        {
            return ROTARYR2_FOUR_LED;
            break;
        }
        case 3: 
        {
            return ROTARYR2_EIGHT_LED;
            break;
        }
        default: 
        {
            return ROTARYR2_ONE_LED;
            break;
        }
    }
}

static void rotaryr2_switch_detection ( void )
{
    if ( rotaryr2_get_state_switch( &rotaryr2 ) ) 
    {
        new_state = 1;
        if ( (  1 == new_state ) && ( 0 == old_state ) ) 
        {
            old_state = 1;
            led_demo_state = ( led_demo_state + 1 ) % 5;
            if ( 4 == led_demo_state ) 
            {
                for ( uint8_t n_cnt = 0; n_cnt < 10; n_cnt++ )
                {
                    rotaryr2_set_led_data( &rotaryr2, ROTARYR2_EIGHT_LED_INV );
                    Delay_ms ( 100 );
                    rotaryr2_set_led_data( &rotaryr2, ROTARYR2_EIGHT_LED );
                    Delay_ms ( 100 );
                }
                
                for ( uint8_t led_p = ROTARYR2_SET_LED_POS_1; led_p <= ROTARYR2_SET_LED_POS_16; led_p++ ) 
                {
                    rotaryr2_set_led_pos( &rotaryr2, led_p );
                    Delay_ms ( 100 );
                }
                
                led_demo_state = 0;
                led_data = rotaryr2_sel_led_demo_data( led_demo_state );
            }
            else 
            {
                led_data = rotaryr2_sel_led_demo_data( led_demo_state );
            }
        }
    }
    else 
    {
        old_state = 0;
    }
}

static void rotaryr2_encoder_mechanism ( void )
{
    if ( rotaryr2_get_state_ena( &rotaryr2 ) == rotaryr2_get_state_enb( &rotaryr2 ) ) 
    {
        old_rot_state = 0;
        start_rot_status = rotaryr2_get_state_ena( &rotaryr2 ) && rotaryr2_get_state_enb( &rotaryr2 );
    }
    else 
    {
        new_rot_state = 1;
        if ( new_rot_state != old_rot_state ) 
        {
            old_rot_state = 1;
            if ( start_rot_status != rotaryr2_get_state_ena( &rotaryr2 ) ) 
            {
                led_data = ( led_data << 1 ) | ( led_data >> 15 );
            }
            else 
            {
                led_data = ( led_data >> 1 ) | ( led_data << 15 );
            }
        }
    }
}

// ------------------------------------------------------------------------ END
