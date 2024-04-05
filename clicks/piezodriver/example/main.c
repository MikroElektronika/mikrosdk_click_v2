/*!
 * @file main.c
 * @brief Piezo Driver Click example
 *
 * # Description
 * This example demonstrates the use of Piezo Driver Click board.
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
 * In order to run this example and play all tones correctly, the user will need to decrease 
 * the MCU's main clock frequency in MCU Settings for certain architectures
 * in order to get the required PWM clock frequency.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "piezodriver.h"

static piezodriver_t piezodriver;
static log_t logger;

#define W           4*Q       // Whole 4/4 - 4 Beats
#define H           2*Q       // Half 2/4 - 2 Beats 
#define Q           250       // Quarter 1/4 - 1 Beat
#define E           Q/2       // Eighth 1/8 - 1/2 Beat
#define S           Q/4       // Sixteenth 1/16 - 1/4 Beat

#define VOLUME      100 

/**
 * @brief Piezo Driver play Imperial march function.
 * @details This function is used to play Imperial march on the buzzer.
 * @return Nothing.
 * @note None.
 */
static void imperial_march( );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    piezodriver_cfg_t piezodriver_cfg;  /**< Click config object. */

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
    piezodriver_cfg_setup( &piezodriver_cfg );
    PIEZODRIVER_MAP_MIKROBUS( piezodriver_cfg, MIKROBUS_1 );
    if ( PWM_ERROR == piezodriver_init( &piezodriver, &piezodriver_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIEZODRIVER_ERROR == piezodriver_default_cfg ( &piezodriver ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
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

static void imperial_march( ) 
{
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, H );
    Delay_ms ( 1 + H );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_AB6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, H );
    Delay_ms ( 1 + H );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_AB7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_G7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_GB7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_E7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_BB6, VOLUME, E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_EB7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_D7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_DB7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_B6, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_AB6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_E7, VOLUME, H );
    Delay_ms ( 1 + H );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_AB7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_G7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_GB7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_E7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_BB6, VOLUME, E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_EB7, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_D7, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_DB7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_B6, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, E );
    Delay_ms ( 1 + E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E );
    Delay_ms ( 1 + E );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_AB6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_A6, VOLUME, Q );
    Delay_ms ( 1 + Q );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_F6, VOLUME, E + S );
    Delay_ms ( 1 + E + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_C7, VOLUME, S );
    Delay_ms ( 1 + S );
    piezodriver_play_sound(&piezodriver, PIEZODRIVER_NOTE_AB6, VOLUME, H );
    Delay_ms ( 1 + H );
}

// ------------------------------------------------------------------------ END
