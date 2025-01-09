/*!
 * \file 
 * \brief Knob Click example
 * 
 * # Description
 * The demo application displays different types of LED controls and encoder position readings.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring Clicks and log objects.
 * Settings the Click in the default configuration.
 * 
 * ## Application Task  
 * The Task application has 3 test modes:
 *  - The first example is setting BRIGHTNESS on all LEDs.
 *  - Other examples put the LED in the position read from the encoder.
 *  - The third example sets the LED to be read while the encoder registers the clockwise movement
 *    and turn off those LEDs that the encoder reads when moving in a counterclockwise direction.
 *  - The example is changed by pressing the SW button
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "knob.h"

// ------------------------------------------------------------------ VARIABLES

static knob_t knob;
static log_t logger;

static int32_t new_position = 0;
static int32_t old_position = 0;
static uint8_t sw_state = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    knob_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    knob_cfg_setup( &cfg );
    KNOB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    knob_init( &knob, &cfg );

    knob_reset( &knob );
    Delay_ms ( 300 );

    knob_default_cfg( &knob );
}

void application_task ( void )
{
    uint8_t cnt;
    uint8_t direction;

    //  Task implementation.

    knob_get_encoder_position( &knob, &new_position, &direction );

    if ( knob_get_sw_button_state( &knob ) == 0 )
    {
        sw_state++;
        if ( sw_state >= 3 ) sw_state = 0;

        knob_set_brightness( &knob, KNOB_BRIGHTNESS_ALL_LED, 0x00 );
        Delay_ms ( 300 );
    }

    // Logs position

    if ( new_position != old_position )
    {
        log_printf( &logger, "** EnCoder position : %d ", new_position );
    }
    old_position = new_position;

    switch ( sw_state )
    {
        // Brightness

        case 0:
        {
            cnt++;
            if ( cnt > 127 )
            {
                cnt = 0;
            }
            knob_set_brightness( &knob, KNOB_BRIGHTNESS_ALL_LED, cnt );
            Delay_ms ( 15 );

            break;
        }

        // Encoder with one led

        case 1:
        {
            if ( new_position > 24 )
            {
                knob_set_encoder_start_position( &knob, 1 );
            }
            if ( new_position < 1 )
            {
                knob_set_encoder_start_position( &knob, 24 );
            }

            if (direction == 1)
            {
                knob_set_led_state( &knob, new_position, KNOB_LED_ON );
                knob_set_led_state( &knob, new_position - 1, KNOB_LED_OFF );
            }
            else
            {
                knob_set_led_state( &knob, new_position, KNOB_LED_ON );
                knob_set_led_state( &knob, new_position + 1, KNOB_LED_OFF );
            }
            Delay_1ms();
            break;
        }

        // Encoder with all led

        case 2:
        {
            if ( new_position > 24 )
            {
                knob_set_encoder_start_position( &knob, 1 );
            }
            if ( new_position < 1 )
            {
                knob_set_encoder_start_position( &knob, 24 );
            }

            if ( direction == 1 )
            {
                knob_set_led_state( &knob, new_position, KNOB_LED_ON );
            }
            else
            {
                knob_set_led_state( &knob, new_position + 1, KNOB_LED_OFF);
            }
            Delay_1ms();
            break;
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
