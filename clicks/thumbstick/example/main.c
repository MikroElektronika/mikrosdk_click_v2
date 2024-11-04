/*!
 * \file 
 * \brief Thumbstick Click example
 * 
 * # Description
 * The demo application shows clickboard axis postioning and button pressed.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization of Click board's and log's objects.
 * 
 * ## Application Task  
 * It reads the position of the thumbstick,
 *  - You will get data on log on every change of thumbstick axis position, or if you hold 
 *      thumbstick in one postion it will repeat the same log when timer reaches timeout.
 *  - You will get data on log whenever you press thumbstick button and release it.
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thumbstick.h"

// ------------------------------------------------------------------ VARIABLES

static thumbstick_t thumbstick;
static log_t logger;


static uint8_t old_butt_state;
static uint8_t button_state;

static thumbstick_position_t old_pos;
static thumbstick_position_t thumbstick_pos;

static uint16_t timer_cnt;
#define TIMER_FLAG 1000

static bool change_state;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thumbstick_cfg_t cfg;

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

    thumbstick_cfg_setup( &cfg );
    THUMBSTICK_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thumbstick_init( &thumbstick, &cfg );
    
    thumbstick_set_sensitivity( POSTION_SENS_DEFAULT );
    
    thumbstick_get_position( &thumbstick, &old_pos );
    old_butt_state = thumbstick_button_state( &thumbstick );
    timer_cnt = 0;
    change_state = false;
}

void application_task ( void )
{
    //Button pressed
    button_state = thumbstick_button_state( &thumbstick );

    if ( old_butt_state != button_state )
    {
        if ( button_state == THUMBSTICK_PRESS_BUTTON )
        {
            log_printf( &logger, ">> Button is pressed \r\n" );
            Delay_ms ( 100 );
        }
        else
        {
            log_printf( &logger, ">> Button is released \r\n" );
            Delay_ms ( 100 );
        }
        old_butt_state = button_state;
    }

    //Thumbstick postion
    thumbstick_get_position( &thumbstick, &thumbstick_pos );
    
    if ( ( old_pos.vertical != thumbstick_pos.vertical ) || ( timer_cnt >= TIMER_FLAG ) )
    {
        if ( thumbstick_pos.vertical == THUMBSTICK_POSITION_TOP )
        {
            log_printf( &logger, ">> TOP \r\n" );
            change_state = true;
        }
        else if ( thumbstick_pos.vertical == THUMBSTICK_POSITION_BOTTOM )
        {
            log_printf( &logger, ">> BOTTOM \r\n" );
            change_state = true;
        }
        
        old_pos = thumbstick_pos;
    }
    
    if ( (old_pos.horizontal != thumbstick_pos.horizontal ) || ( timer_cnt >= TIMER_FLAG )  )
    {
        if ( thumbstick_pos.horizontal == THUMBSTICK_POSITION_LEFT )
        {
            log_printf( &logger, ">> LEFT \r\n" );
            change_state = true;
        }
        else if ( thumbstick_pos.horizontal == THUMBSTICK_POSITION_RIGHT )
        {
            log_printf( &logger, ">> RIGHT \r\n" );
            change_state = true;
        }
        
        old_pos = thumbstick_pos;
    }
    
    if ( ( timer_cnt >= TIMER_FLAG ) || ( change_state == true )  )
    {
        timer_cnt = 0;
        change_state = false;
    }
    
    timer_cnt++;
    Delay_ms ( 1 );
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
