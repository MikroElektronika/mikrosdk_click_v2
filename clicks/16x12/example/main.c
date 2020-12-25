/*!
 * \file 
 * \brief 16x12 Click example
 * 
 * # Description
 * This application draw image on the led matrics.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization default device configuration, sets LED mode, 
 * configuration ABM and display one character.
 * 
 * ## Application Task  
 * Clear display, display one by one leds, display one character,
 * display image and display text with scroll.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c16x12.h"

// ------------------------------------------------------------------ VARIABLES

static c16x12_t c16x12;
static log_t logger;

static uint8_t scroll_speed = 50;
static c16x12_abm_t abm_1;
static c16x12_abm_t abm_2;


char demo_text[ 7 ] = "MikroE";
uint16_t demo_image_light[ 12 ] = 
{ 0x0000, 0x0666, 0x0CCC, 0x1998, 0x3330, 0x6660, 0x3330, 0x1998, 0x0CCC, 0x0666, 0x0000, 0x0000 };
uint16_t demo_image_dark[ 12 ]  = 
{ 0xFFFF, 0xF999, 0xF333, 0xE667, 0xCCCF, 0x999F, 0xCCCF, 0xE667, 0xF333, 0xF999, 0xFFFF, 0xFFFF };

char name[] = "16x12";


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c16x12_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 9600;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c16x12_cfg_setup( &cfg );
    C16X12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c16x12_init( &c16x12, &cfg );

    c16x12g_device_reset( &c16x12 );
    Delay_ms( 1000 );

    c16x12_default_cfg( &c16x12 );
    c16x12g_set_global_current_control( &c16x12, 255 );
    c16x12g_set_leds_mode( &c16x12, C16X12G_LED_MODE_ABM1 );

    abm_1.time_1     = C16X12G_ABM_T1_840MS;
    abm_1.time_2     = C16X12G_ABM_T2_840MS;
    abm_1.time_3     = C16X12G_ABM_T3_840MS;
    abm_1.time_4     = C16X12G_ABM_T4_840MS;
    abm_1.loop_begin = C16X12G_ABM_LOOP_BEGIN_T1;
    abm_1.loop_end   = C16X12G_ABM_LOOP_END_T3;
    abm_1.loop_times = C16X12G_ABM_LOOP_FOREVER;
    
    abm_2.time_1     = C16X12G_ABM_T1_210MS;
    abm_2.time_2     = C16X12G_ABM_T2_0MS;
    abm_2.time_3     = C16X12G_ABM_T3_210MS;
    abm_2.time_4     = C16X12G_ABM_T4_0MS;
    abm_2.loop_begin = C16X12G_ABM_LOOP_BEGIN_T1;
    abm_2.loop_end   = C16X12G_ABM_LOOP_END_T3;
    abm_2.loop_times = C16X12G_ABM_LOOP_FOREVER;
    
    c16x12g_config_abm( &c16x12, C16X12G_ABM_NUM_1, &abm_2 );
    c16x12g_start_abm( &c16x12 );
    c16x12g_display_text( &c16x12, &name[ 0 ], 5, scroll_speed );

    c16x12g_config_abm( &c16x12, C16X12G_ABM_NUM_1, &abm_1 );
    c16x12g_start_abm( &c16x12 );
    c16x12g_display_byte( &c16x12, 'G' );
    Delay_ms( 5000 );
    
    c16x12g_config_abm( &c16x12, C16X12G_ABM_NUM_1, &abm_2 );
    c16x12g_start_abm( &c16x12 );
}

void application_task ( void )
{
    uint8_t cnt = 0;
    
    c16x12g_display_text( &c16x12, &demo_text[ 0 ], 6, scroll_speed );

    c16x12g_clear_display( &c16x12 );

    // Display point
    for ( cnt = 1; cnt <= 12; cnt++ )
    {
        c16x12g_set_led( &c16x12, cnt, cnt, C16X12G_LED_STATE_ON, C16X12G_STOP_SETTINGS );
        Delay_ms( 100 );
    }
    Delay_ms( 2000 );

    c16x12g_display_image( &c16x12, &demo_image_light[ 0 ] );
    Delay_ms( 2000 );
     
    c16x12g_display_image( &c16x12, &demo_image_dark[ 0 ] );
    Delay_ms( 2000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}


// ------------------------------------------------------------------------ END
