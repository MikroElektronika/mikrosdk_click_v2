/*!
 * @file main.c
 * @brief Touchpad4 Click example
 *
 * # Description
 * This example showcases ability of the device to read touch coordinates, 
 * active/inactive channels, and gesture informations.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize host communication modules(UART and I2C)  and additional pins,
 * for device control. Then resets device and set default configuration where
 * Channels and pins are mapped and configured, and set communication with device
 * only on touch/event. In the end one of 3 examples is set;
 *
 * ## Application Task
 * There are 3 examples that shocaes ability of the device: 
 *  - Reading touch coorinates and addinal informations of touch strength, 
 *    and touch area and logging them,
 *  - Reading channel statuses and show them by logging them,
 *  - Reading gesture events and logging them;
 *
 * ### Additional Functions
 *  - void touchpad4_touch_reading ( void );
 *  - void touchpad4_channel_reading ( void );
 *  - void touchpad4_gesture_reading ( void );
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "touchpad4.h"

#define TOUCHPAD4_EXAMPLE_TOUCH     1
#define TOUCHPAD4_EXAMPLE_CHANNEL   2
#define TOUCHPAD4_EXAMPLE_GESTURE   3

static touchpad4_t touchpad4;
static log_t logger;

static uint8_t example_selector = 0;

/**
 * @brief Touchpad 4 touch info example.
 * @details This function reads touch informations and logs them.
 * @return Nothing
 */
void touchpad4_touch_reading ( void );

/**
 * @brief Touchpad 4 channel example.
 * @details This function reads channel informations and logs them.
 * @return Nothing
 */
void touchpad4_channel_reading ( void );

/**
 * @brief Touchpad 4 gesture info example.
 * @details This function reads gesture informations and logs them.
 * @return Nothing
 */
void touchpad4_gesture_reading ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    touchpad4_cfg_t touchpad4_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    touchpad4_cfg_setup( &touchpad4_cfg );
    TOUCHPAD4_MAP_MIKROBUS( touchpad4_cfg, MIKROBUS_1 );
    err_t init_flag = touchpad4_init( &touchpad4, &touchpad4_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    touchpad4_reset( &touchpad4 );

    init_flag = touchpad4_default_cfg ( &touchpad4 );
    if ( TOUCHPAD4_ERROR == init_flag ) 
    {
        log_error( &logger, " Configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    example_selector = TOUCHPAD4_EXAMPLE_TOUCH;
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( !touchpad4_get_ready( &touchpad4 ) )
    {
        switch ( example_selector )
        {
            case TOUCHPAD4_EXAMPLE_TOUCH:
            {
                touchpad4_touch_reading( );
                break;
            }
            case TOUCHPAD4_EXAMPLE_CHANNEL:
            {
                touchpad4_channel_reading( );
                break;
            }
            case TOUCHPAD4_EXAMPLE_GESTURE:
            {
                touchpad4_gesture_reading( );
                break;
            }
            default:
            {
                log_error( &logger, " Select Example" );
                break;
            }
        } 
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}


void touchpad4_touch_reading ( void )
{
    touchpad4_info_t ti;
    
    touchpad4_get_touch ( &touchpad4, &ti );
    
    if ( ( ti.number_of_touches > 0 ) && ( ti.number_of_touches <= 2 ) )
    {        
        log_printf( &logger, "> X->%d\r\n> Y->%d\r\n> Strength->%u\r\n> Area->%u\r\n",  
                    ti.touches[ 0 ].x, ti.touches[ 0 ].y, ti.touches[ 0 ].strength, ti.touches[ 0 ].area );
        
        log_printf( &logger, "**************\r\n" );
    }
}

void touchpad4_channel_reading ( void )
{
    uint32_t ch_status = 0;
        
    touchpad_get_channels( &touchpad4, &ch_status );
    
    uint8_t shift = 19;
    char row[ 10 ] = { 0 };
    for ( uint8_t r = 0; r < 5; r++ )
    {
        uint8_t row_char_cnt = 6;
        for ( uint8_t y = 0; y < 4; y++ )
        {
            if (y)
                row[ row_char_cnt-- ] = '|';
            
            if ( ( ch_status >> shift ) & 1 )
            {
                row[ row_char_cnt-- ] = 'x';
            }
            else
            {
                row[ row_char_cnt-- ] = 'o';
            }
            
            shift--;
        }
        log_printf( &logger, "%s\r\n", row );
    }
    log_printf( &logger, "\r\n" );
}

void touchpad4_gesture_reading ( void )
{
    uint16_t gesture_data = 0;
    
    touchpad4_generic_read( &touchpad4, TOUCHPAD4_REG_GESTURES, &gesture_data );
    gesture_data &= 0x002F;
    
    if ( gesture_data & 0x0001 )
    {
        log_printf( &logger, " > Single Tap <\r\n" );
    }
    if ( gesture_data & 0x0002 )
    {
        log_printf( &logger, " > SPress And Hold <\r\n" );
    }
    if ( gesture_data & 0x0004 )
    {
        log_printf( &logger, " > Swipe X - <\r\n" );
    }
    if ( gesture_data & 0x0008 )
    {
        log_printf( &logger, " > Swipe X + <\r\n" );
    }
    if ( gesture_data & 0x0010 )
    {
        log_printf( &logger, " > Swipe Y + <\r\n" );
    }
    if ( gesture_data & 0x0020 )
    {
        log_printf( &logger, " > Swipe Y - <\r\n" );
    }
    
    if ( gesture_data )
    {
        log_printf( &logger, "**************\r\n" );
    }
}

// ------------------------------------------------------------------------ END
