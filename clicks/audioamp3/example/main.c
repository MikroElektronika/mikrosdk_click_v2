/*!
 * \file 
 * \brief AudioAmp3 Click example
 * 
 * # Description
 * AudioAmp 3 Click is a stereo audio amplifier, capable of delivering
 * up to 79W per channel with the 4Ω load.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of AudioAmp 3 click board.
 * In application task function is used that will increase volume of the sound
 * from MIN to MAX and reverse.
 * Results are being sent to the UART Terminal where you can track their changes.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "audioamp3.h"

uint8_t cnt;
uint8_t data_out[ 10 ];
uint8_t status_flag;

// ------------------------------------------------------------------ VARIABLES

static audioamp3_t audioamp3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    audioamp3_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    audioamp3_cfg_setup( &cfg );
    AUDIOAMP3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    audioamp3_init( &audioamp3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "--- AudioAmp  3  Click ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    audioamp3_power_up( &audioamp3 );
    log_printf( &logger, "          Power Up          \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_set_channel_low_to_low( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_CH_1 );
    log_printf( &logger, " Set channel 1 low-low state \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_set_channel_low_to_low( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_CH_2 );
    log_printf( &logger, " Set channel 2 low-low state \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_set_channel_mute_mode( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_ALL_CH );
    log_printf( &logger, "      Mute All Channels     \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_run_channel_diagnostics( &audioamp3, AUDIOAMP3_MASK_BIT_SEL_ALL_CH );
    log_printf( &logger, "       Run Diagnostics      \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_hw_reset( &audioamp3 );
    log_printf( &logger, "       Hardware Reset       \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    audioamp3_read_all_diagnostics( &audioamp3, &data_out[ 0 ] );
    log_printf( &logger, "      Read Diagnostics      \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, "    Initialization  done  \r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 1000 );
    
    audioamp3_set_play_mode( &audioamp3 );
    log_printf( &logger, " ---------------------------\r\n\n" );
    log_printf( &logger, "            Play            \r\n" );
    log_printf( &logger, " ---------------------------\r\n\n" );
    Delay_100ms();
}

void application_task ( void )
{
    for ( cnt = AUDIOAMP3_GAIN_VAL_MIN; cnt < AUDIOAMP3_GAIN_VAL_5; cnt++ )
    {
        status_flag = audioamp3_set_gain_lvl( &audioamp3, cnt );
        log_printf( &logger, "    -  Volume Up  -  \r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " ---------------------------\r\n\n" );
    
    for ( cnt = AUDIOAMP3_GAIN_VAL_MAX; cnt > AUDIOAMP3_GAIN_VAL_0; cnt-- )
    {
        status_flag = audioamp3_set_gain_lvl( &audioamp3, cnt );
    
        log_printf( &logger, "    -  Volume Down  -  \r\n" );
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
    
    log_printf( &logger, " ---------------------------\r\n\n" );
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
