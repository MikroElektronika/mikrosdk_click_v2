/*!
 * @file main.c
 * @brief Buzz3 Click example
 *
 * # Description
 * This example demonstrates the use of Buzz 3 Click boards with PAM8904 for play the Imperial March. 
 * PAM8904 is piezo-sounder driver with an integrated Multi-Mode charge pump boost converter from Diodes Incorporated. 
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes GPIO, set AN and RST pin as outputs, begins to write a log. 
 * Initialization driver enables - GPIO and configures the appropriate MCU pin for 
 * sound generation, also write log.
 *
 * ## Application Task
 * Plays the Imperial March melody. Also logs an appropriate message on the USB UART.
 *
 * Additional Functions :
 * - void buzz3_melody( void ) - This function plays the Imperial March melody.
 * 
 * @note
 * The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
 * So, in order to run this example and play all tones correctly, the user will need to decrease 
 * the MCU's main clock frequency in MCU Settings for the certain architectures
 * in order to get the required PWM clock frequency.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "buzz3.h"

#define W 4*Q         // Whole 4/4 - 4 Beats
#define H 2*Q         // Half 2/4 - 2 Beats 
#define Q 250         // Quarter 1/4 - 1 Beat
#define E Q/2         // Eighth 1/8 - 1/2 Beat
#define S Q/4         // Sixteenth 1/16 - 1/4 Beat
                      

static buzz3_t buzz3;
static log_t logger;

void buzz3_melody ( void ) {
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, H );
    Delay_ms ( 1 + H );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_E7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_E7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_E7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F7, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Ab6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, H );
    Delay_ms ( 1 + H );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Ab7, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_G7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Gb7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_E7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F7, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Bb6, E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Eb7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_D7, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Db7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_B6, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Ab6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_E7, H );
    Delay_ms ( 1 + H );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Ab7, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_G7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Gb7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_E7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F7, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Bb6, E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Eb7, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_D7, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Db7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_B6, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E );
    Delay_ms ( 1 + E );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Ab6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_A6, Q );
    Delay_ms ( 1 + Q );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_F6, E + S );
    Delay_ms ( 1 + E + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_C7, S );
    Delay_ms ( 1 + S );
    buzz3_play_sound(&buzz3, BUZZ3_NOTE_Ab6, H );
    Delay_ms ( 1 + H );
}

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    buzz3_cfg_t buzz3_cfg;      /**< Click config object. */

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

    buzz3_cfg_setup( &buzz3_cfg );
    BUZZ3_MAP_MIKROBUS( buzz3_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz3_init( &buzz3, &buzz3_cfg );
    if ( PWM_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz3_default_cfg ( &buzz3 );
    buzz3_set_duty_cycle ( &buzz3, 0.0 );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " Set the gain to x1  \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
    buzz3_pwm_start( &buzz3 );
    buzz3_set_gain_operating_mode( &buzz3, BUZZ3_OP_MODE_GAIN_x1 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, "   Play the music    \r\n" );
    buzz3_melody( );
    log_printf( &logger, "---------------------\r\n" );
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
