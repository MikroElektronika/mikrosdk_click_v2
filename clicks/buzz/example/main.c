/*!
 * @file main.c
 * @brief BUZZ Click example
 *
 * # Description
 * This example demonstrates the use of Buzz Click boards.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger.
 * 
 * ## Application Task  
 * Plays the Imperial March melody. Also logs an appropriate message on the USB UART.
 * 
 * ## Additional Functions
 * imperial_march( void ) - this function plays the Imperial March melody.
 * 
 * @note
 * The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
 * So, in order to run this example and play all tones correctly, the user will need to decrease 
 * the MCU's main clock frequency in MCU Settings for the certain architectures
 * in order to get the required PWM clock frequency.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "buzz.h"

#define W 4*Q // Whole 4/4 - 4 Beats
#define H 2*Q // Half 2/4 - 2 Beats 
#define Q 250 // Quarter 1/4 - 1 Beat
#define E Q/2 // Eighth 1/8 - 1/2 Beat
#define S Q/4 // Sixteenth 1/16 - 1/4 Beat

#define VOLUME 100 // goes up to 1000

static buzz_t buzz;
static log_t logger;

static void imperial_march( ) {
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, H );
    Delay_ms ( 1 + H );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_Ab6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, H );
    Delay_ms ( 1 + H );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_Ab7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_G7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_Gb7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_Bb6, VOLUME, E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_Eb7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_D7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_Db7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_B6, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_Ab6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_E7, VOLUME, H );
    Delay_ms ( 1 + H );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_Ab7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_G7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_Gb7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_E7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_F7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_Bb6, VOLUME, E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_Eb7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_D7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_Db7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_B6, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E );
    Delay_ms ( 1 + E );
    buzz_play_sound( &buzz, BUZZ_NOTE_Ab6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    buzz_play_sound( &buzz, BUZZ_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    buzz_play_sound( &buzz, BUZZ_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    buzz_play_sound( &buzz, BUZZ_NOTE_Ab6, VOLUME, H );
    Delay_ms ( 1 + H );
}


void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzz_cfg_t buzz_cfg;  /**< Click config object. */

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

    buzz_cfg_setup( &buzz_cfg );
    BUZZ_MAP_MIKROBUS( buzz_cfg, MIKROBUS_1 );
    err_t init_flag  = buzz_init( &buzz, &buzz_cfg );
    if ( init_flag == PWM_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    buzz_set_duty_cycle ( &buzz, 0.0 );
    buzz_pwm_start( &buzz );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    log_printf( &logger, "Playing the Imperial March melody ...\r\n" );
    imperial_march( ); 
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
