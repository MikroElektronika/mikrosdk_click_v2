/*!
 * @file main.c
 * @brief Rotary O 2 Click example
 *
 * # Description
 * This library contains the API for the Rotary O 2 Click driver 
 * to control LEDs states and a rotary encoder position readings.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After the driver init, the app executes a default configuration and turn off all LEDs.
 *
 * ## Application Task
 * This example demonstrates the use of the Rotary O 2 Click board.
 * The demo example shows the functionality of a rotary encoder used to control LEDs.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rotaryo2.h"

#define ROTARYO2_ONE_LED          ROTARYO2_SET_LED_DATA_1
#define ROTARYO2_TWO_LED          ROTARYO2_SET_LED_DATA_1  | ROTARYO2_SET_LED_DATA_9
#define ROTARYO2_FOUR_LED         ROTARYO2_SET_LED_DATA_1  | ROTARYO2_SET_LED_DATA_5  | \
                                  ROTARYO2_SET_LED_DATA_9  | ROTARYO2_SET_LED_DATA_13 
#define ROTARYO2_EIGHT_LED        ROTARYO2_SET_LED_DATA_1  | ROTARYO2_SET_LED_DATA_3  | \
                                  ROTARYO2_SET_LED_DATA_5  | ROTARYO2_SET_LED_DATA_7  | \
                                  ROTARYO2_SET_LED_DATA_9  | ROTARYO2_SET_LED_DATA_11 | \
                                  ROTARYO2_SET_LED_DATA_13 | ROTARYO2_SET_LED_DATA_15
#define ROTARYO2_EIGHT_LED_INV    ROTARYO2_SET_LED_DATA_2  | ROTARYO2_SET_LED_DATA_4  | \
                                  ROTARYO2_SET_LED_DATA_6  | ROTARYO2_SET_LED_DATA_8  | \
                                  ROTARYO2_SET_LED_DATA_10 | ROTARYO2_SET_LED_DATA_12 | \
                                  ROTARYO2_SET_LED_DATA_14 | ROTARYO2_SET_LED_DATA_16

static rotaryo2_t rotaryo2;
static log_t logger;

static uint8_t start_rot_status = 0;
static uint8_t led_demo_state = 0;
static uint8_t old_state = 0;
static uint8_t new_state = 1;
static uint8_t old_rot_state = 0;
static uint8_t new_rot_state = 1;
static uint16_t led_data = 1;

/**
 * @brief Rotary O 2 select LED demo data function.
 * @details This function selects one of the four LED demo data 
 * based on the current state of the LED demo.
 * @return LED demo data:
 *         @li @c 0x0001 (ROTARYO2_ONE_LED)   - Turn ON LED[1],
 *         @li @c 0x0101 (ROTARYO2_TWO_LED)   - Turn ON LED[1,9],
 *         @li @c 0x0101 (ROTARYO2_FOUR_LED)  - Turn ON LED[1,5,9,13],
 *         @li @c 0x5555 (ROTARYO2_EIGHT_LED) - Turn ON LED[1,3,5,7,9,11,13,15].
 */
static uint16_t rotaryo2_sel_led_demo_data ( uint8_t led_demo_state );

/**
 * @brief Rotary O 2 switch detection function.
 * @details This function is used for the switch state detection.
 * @return Nothing.
 */
static void rotaryo2_switch_detection ( void );

/**
 * @brief Rotary O 2 encoder mechanism function.
 * @details This function is used to control the state of the LEDs 
 * by detecting the rotation direction of the rotary encoder.
 * @return Nothing.
 */
static void rotaryo2_encoder_mechanism ( void );

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rotaryo2_cfg_t rotaryo2_cfg;  /**< Click config object. */

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
    rotaryo2_cfg_setup( &rotaryo2_cfg );
    ROTARYO2_MAP_MIKROBUS( rotaryo2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == rotaryo2_init( &rotaryo2, &rotaryo2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ROTARYO2_ERROR == rotaryo2_default_cfg ( &rotaryo2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( ROTARYO2_OK == rotaryo2_set_led_data( &rotaryo2, led_data ) )
    {
        rotaryo2_switch_detection( );
        rotaryo2_encoder_mechanism( );
    }
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

static uint16_t rotaryo2_sel_led_demo_data ( uint8_t led_demo_state ) 
{
    switch ( led_demo_state ) 
    {
        case 0: 
        {
            return ROTARYO2_ONE_LED;
            break;
        }
        case 1: 
        {
            return ROTARYO2_TWO_LED;
            break;
        }
        case 2: 
        {
            return ROTARYO2_FOUR_LED;
            break;
        }
        case 3: 
        {
            return ROTARYO2_EIGHT_LED;
            break;
        }
        default: 
        {
            return ROTARYO2_ONE_LED;
            break;
        }
    }
}

static void rotaryo2_switch_detection ( void )
{
    if ( rotaryo2_get_state_switch( &rotaryo2 ) ) 
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
                    rotaryo2_set_led_data( &rotaryo2, ROTARYO2_EIGHT_LED_INV );
                    Delay_ms( 100 );
                    rotaryo2_set_led_data( &rotaryo2, ROTARYO2_EIGHT_LED );
                    Delay_ms( 100 );
                }
                
                for ( uint8_t led_p = ROTARYO2_SET_LED_POS_1; led_p <= ROTARYO2_SET_LED_POS_16; led_p++ ) 
                {
                    rotaryo2_set_led_pos( &rotaryo2, led_p );
                    Delay_ms( 100 );
                }
                
                led_demo_state = 0;
                led_data = rotaryo2_sel_led_demo_data( led_demo_state );
            }
            else 
            {
                led_data = rotaryo2_sel_led_demo_data( led_demo_state );
            }
        }
    }
    else 
    {
        old_state = 0;
    }
}

static void rotaryo2_encoder_mechanism ( void )
{
    if ( rotaryo2_get_state_ena( &rotaryo2 ) == rotaryo2_get_state_enb( &rotaryo2 ) ) 
    {
        old_rot_state = 0;
        start_rot_status = rotaryo2_get_state_ena( &rotaryo2 ) && rotaryo2_get_state_enb( &rotaryo2 );
    }
    else 
    {
        new_rot_state = 1;
        if ( new_rot_state != old_rot_state ) 
        {
            old_rot_state = 1;
            if ( start_rot_status != rotaryo2_get_state_ena( &rotaryo2 ) ) 
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
