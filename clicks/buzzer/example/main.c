/*!
 * @file main.c
 * @brief Buzzer Click example
 *
 * # Description
 * This example demonstrates the use of Buzzer click board by playing
 * the Imperial March melody on the buzzer.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and logger.
 * 
 * ## Application Task  
 * Plays the Imperial March melody. Also logs an appropriate message on the USB UART.
 * 
 * @note
 * The minimal PWM Clock frequency required for this example is the frequency of tone C6 - 1047 Hz. 
 * So, in order to run this example and play all tones correctly, the user will need to decrease 
 * the MCU's main clock frequency in MCU Settings for the certain architectures
 * in order to get the required PWM clock frequency.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buzzer.h"

static buzzer_t buzzer;
static log_t logger;

/**
 * @brief Buzzer imperial march function.
 * @details This function plays the Imperial March melody on the buzzer
 * at the selected volume level.
 * @param[in] volume : Buzz sound level. ( min = 1, max = 100 )
 * @return None.
 * @note None.
 */
static void buzzer_imperial_march ( uint8_t volume );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buzzer_cfg_t buzzer_cfg;  /**< Click config object. */

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
    buzzer_cfg_setup( &buzzer_cfg );
    BUZZER_MAP_MIKROBUS( buzzer_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == buzzer_init( &buzzer, &buzzer_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    log_printf( &logger, " Playing the Imperial March melody...\r\n" );
    buzzer_imperial_march( BUZZER_VOLUME_MAX ); 
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

static void buzzer_imperial_march ( uint8_t volume )
{
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_HALF );
    Delay_ms ( BUZZER_NOTE_LEN_HALF );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_E7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_E7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_E7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F7, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Ab6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_HALF );
    Delay_ms ( BUZZER_NOTE_LEN_HALF );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Ab7, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_G7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Gb7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_E7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F7, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Bb6, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Eb7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_D7, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Db7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_B6, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Ab6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_E7, volume, BUZZER_NOTE_LEN_HALF );
    Delay_ms ( BUZZER_NOTE_LEN_HALF );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Ab7, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_G7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Gb7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_E7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F7, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Bb6, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Eb7, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_D7, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Db7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_B6, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Ab6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    
    buzzer_play_sound( &buzzer, BUZZER_NOTE_A6, volume, BUZZER_NOTE_LEN_QUARTER );
    Delay_ms ( BUZZER_NOTE_LEN_QUARTER );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_F6, volume, BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_EIGHTH + BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_C7, volume, BUZZER_NOTE_LEN_SIXTEENTH );
    Delay_ms ( BUZZER_NOTE_LEN_SIXTEENTH );
    buzzer_play_sound( &buzzer, BUZZER_NOTE_Ab6, volume, BUZZER_NOTE_LEN_HALF );
    Delay_ms ( BUZZER_NOTE_LEN_HALF );
}

// ------------------------------------------------------------------------ END
