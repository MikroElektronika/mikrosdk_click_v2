/*!
 * @file main.c
 * @brief 8800Retro Click example
 *
 * # Description
 * This example demonstrates the use of 8800 Retro click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and issues the click default configuration, 
 * then asks the user to select the demo example using the on-board KeyPad.
 *
 * ## Application Task
 * There are 4 different demo examples: KeyPad 4x4, Full charset, Text, and Image.
 * This function will run the previously selected demo example in the loop. 
 * The user can always switch the example by pressing the button D4 three times in a row. 
 * In order to run the demo examples successfully, please follow the instructions logged
 * on the USB UART.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "c8800retro.h"

/**
 * @brief 8800 Retro Click demo example values.
 * @details Enum values for demo examples selection.
 */
typedef enum
{
    DEMO_KEYPAD4x4,
    DEMO_FULL_CHARSET,
    DEMO_TEXT,
    DEMO_IMAGE,

} c8800retro_demo_example_t;

static c8800retro_t c8800retro;
static log_t logger;

static c8800retro_demo_example_t demo_example = DEMO_KEYPAD4x4;
uint8_t c8800retro_demo_string[ 9 ] = { ' ', 'M', 'i', 'k', 'r', 'o', 'E', ' ', 0 };
uint8_t c8800retro_demo_logo_mikroe[ 8 ] = { 0x7F, 0xFF, 0xC0, 0xFF, 0xFF, 0xC0, 0xFF, 0x7F };

/**
 * @brief 8800 Retro select demo example function.
 * @details This function asks the user to select the demo example via desired buttons.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Follow the procedure written on the USB UART to select the desired demo example.
 */
static err_t c8800retro_select_demo_example( c8800retro_t *ctx );

/**
 * @brief 8800 Retro demo KeyPad 4x4 example function.
 * @details This function executes the KeyPad 4x4 demo example.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Follow the procedure written on the USB UART to jump out the function.
 */
static err_t c8800retro_demo_keypad4x4( c8800retro_t *ctx );

/**
 * @brief 8800 Retro demo Full charset example function.
 * @details This function executes the Full charset demo example.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Follow the procedure written on the USB UART to jump out the function.
 */
static err_t c8800retro_demo_full_charset( c8800retro_t *ctx );

/**
 * @brief 8800 Retro demo text example function.
 * @details This function executes the Text demo example.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] scroll_mode : @li @c 0 - Horizontal left.
 *                          @li @c 1 - Horizontal right.
 *                          @li @c 2 - Vertical up.
 *                          @li @c 3 - Vertical down.
 * @param[in] scroll_speed_ms : Scroll speed in miliseconds.
 * @param[in] text : Text string (up to 32 characters).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Follow the procedure written on the USB UART to jump out the function.
 */
static err_t c8800retro_demo_text( c8800retro_t *ctx, uint8_t scroll_mode, uint16_t scroll_speed_ms, uint8_t *text );

/**
 * @brief 8800 Retro demo image example function.
 * @details This function executes the Image demo example.
 * @param[in] ctx : Click context object.
 * See #c8800retro_t object definition for detailed explanation.
 * @param[in] p_image : Pointer to image buffer (array of 8 bytes).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note Follow the procedure written on the USB UART to jump out the function.
 */
static err_t c8800retro_demo_image( c8800retro_t *ctx, uint8_t *p_image );

void application_init ( void ) 
{
    log_cfg_t log_cfg;                /**< Logger config object. */
    c8800retro_cfg_t c8800retro_cfg;  /**< Click config object. */
    
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
    c8800retro_cfg_setup( &c8800retro_cfg );
    C8800RETRO_MAP_MIKROBUS( c8800retro_cfg, MIKROBUS_1 );
    err_t init_flag = c8800retro_init( &c8800retro, &c8800retro_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c8800retro_default_cfg( &c8800retro );
    c8800retro_select_demo_example( &c8800retro );
}

void application_task ( void ) 
{
    switch ( demo_example )
    {
        case DEMO_KEYPAD4x4:
        {
            c8800retro_demo_keypad4x4 ( &c8800retro );
            break;
        }
        case DEMO_FULL_CHARSET:
        {
            c8800retro_demo_full_charset ( &c8800retro );
            break;
        }
        case DEMO_TEXT:
        {
            c8800retro_demo_text ( &c8800retro, C8800RETRO_SCROLL_HORIZONTAL_LEFT, 
                                                C8800RETRO_SCROLL_SPEED_MEDIUM, 
                                                c8800retro_demo_string );
            break;
        }
        case DEMO_IMAGE:
        {
            c8800retro_demo_image ( &c8800retro, c8800retro_demo_logo_mikroe );
            break;
        }
        default:
        {
            break;
        }
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

static err_t c8800retro_select_demo_example( c8800retro_t *ctx )
{
    err_t error_flag = c8800retro_clear_display( ctx );
    error_flag |= c8800retro_clear_interrupt( ctx );
    
    for ( ; ; )
    {
        uint16_t keypad = C8800RETRO_KEY_NONE;
        
        log_printf( &logger, "\r\n Press one of the following buttons to select the demo example: \r\n" );
        log_printf( &logger, " A1: KeyPad 4x4 \r\n" );
        log_printf( &logger, " A2: Full charset \r\n" );
        log_printf( &logger, " A3: Text \r\n" );
        log_printf( &logger, " A4: Image \r\n" );
        
        // Pressed button
        while( c8800retro_get_int_pin( ctx ) );
        error_flag |= c8800retro_get_keypad( ctx, &keypad );
        while( !c8800retro_get_int_pin( ctx ) );
        
        // Released button
        while( c8800retro_get_int_pin( ctx ) );
        error_flag |= c8800retro_clear_interrupt( ctx );
        while( !c8800retro_get_int_pin( ctx ) );
        
        switch ( keypad )
        {
            case C8800RETRO_KEY_A1:
            {
                demo_example = DEMO_KEYPAD4x4;
                return error_flag;
            }
            case C8800RETRO_KEY_A2:
            {
                demo_example = DEMO_FULL_CHARSET;
                return error_flag;
            }
            case C8800RETRO_KEY_A3:
            {
                demo_example = DEMO_TEXT;
                return error_flag;
            }
            case C8800RETRO_KEY_A4:
            {
                demo_example = DEMO_IMAGE;
                return error_flag;
            }
            default:
            {
                log_printf( &logger, " Wrong button! \r\n" );
                break;
            }
        }
    }
}

static err_t c8800retro_demo_keypad4x4( c8800retro_t *ctx )
{
    log_printf( &logger, "\r\n ---- KeyPad 4x4 demo example ---- \r\n" );
    log_printf( &logger, " Keypad layout: \r\n" );
    log_printf( &logger, " 1  2  3  A \r\n" );
    log_printf( &logger, " 4  5  6  B \r\n" );
    log_printf( &logger, " 7  8  9  C \r\n" );
    log_printf( &logger, " *  0  #  D \r\n" );
    log_printf( &logger, " Press the button D4 three times to switch the example \r\n " );
    uint8_t d4_cnt = 0;
    
    err_t error_flag = c8800retro_clear_display( ctx );
    error_flag |= c8800retro_clear_interrupt( ctx );
    
    for ( ; ; )
    {
        uint16_t keypad = C8800RETRO_KEY_NONE;
        
        // Pressed button
        while( c8800retro_get_int_pin( ctx ) );
        error_flag |= c8800retro_get_keypad( ctx, &keypad );
        while( !c8800retro_get_int_pin( ctx ) );
        
        // Released button
        while( c8800retro_get_int_pin( ctx ) );
        error_flag |= c8800retro_clear_interrupt( ctx );
        while( !c8800retro_get_int_pin( ctx ) );
        
        if ( keypad & C8800RETRO_KEY_D4 )
        {
            d4_cnt++;
        }
        else
        {
            d4_cnt = 0;
        }
        switch ( keypad )
        {
            case C8800RETRO_KEY_A1:
            {
                error_flag |= c8800retro_display_char( ctx, '1' );
                log_printf( &logger, "1" );
                break;
            }
            case C8800RETRO_KEY_A2:
            {
                error_flag |= c8800retro_display_char( ctx, '2' );
                log_printf( &logger, "2" );
                break;
            }
            case C8800RETRO_KEY_A3:
            {
                error_flag |= c8800retro_display_char( ctx, '3' );
                log_printf( &logger, "3" );
                break;
            }
            case C8800RETRO_KEY_A4:
            {
                error_flag |= c8800retro_display_char( ctx, 'A' );
                log_printf( &logger, "A" );
                break;
            }
            case C8800RETRO_KEY_B1:
            {
                error_flag |= c8800retro_display_char( ctx, '4' );
                log_printf( &logger, "4" );
                break;
            }
            case C8800RETRO_KEY_B2:
            {
                error_flag |= c8800retro_display_char( ctx, '5' );
                log_printf( &logger, "5" );
                break;
            }
            case C8800RETRO_KEY_B3:
            {
                error_flag |= c8800retro_display_char( ctx, '6' );
                log_printf( &logger, "6" );
                break;
            }
            case C8800RETRO_KEY_B4:
            {
                error_flag |= c8800retro_display_char( ctx, 'B' );
                log_printf( &logger, "B" );
                break;
            }
            case C8800RETRO_KEY_C1:
            {
                error_flag |= c8800retro_display_char( ctx, '7' );
                log_printf( &logger, "7" );
                break;
            }
            case C8800RETRO_KEY_C2:
            {
                error_flag |= c8800retro_display_char( ctx, '8' );
                log_printf( &logger, "8" );
                break;
            }
            case C8800RETRO_KEY_C3:
            {
                error_flag |= c8800retro_display_char( ctx, '9' );
                log_printf( &logger, "9" );
                break;
            }
            case C8800RETRO_KEY_C4:
            {
                error_flag |= c8800retro_display_char( ctx, 'C' );
                log_printf( &logger, "C" );
                break;
            }
            case C8800RETRO_KEY_D1:
            {
                error_flag |= c8800retro_display_char( ctx, '*' );
                log_printf( &logger, "*" );
                break;
            }
            case C8800RETRO_KEY_D2:
            {
                error_flag |= c8800retro_display_char( ctx, '0' );
                log_printf( &logger, "0" );
                break;
            }
            case C8800RETRO_KEY_D3:
            {
                error_flag |= c8800retro_display_char( ctx, '#' );
                log_printf( &logger, "#" );
                break;
            }
            case C8800RETRO_KEY_D4:
            {
                error_flag |= c8800retro_display_char( ctx, 'D' );
                log_printf( &logger, "D" );
                break;
            }
            default:
            {
                break;
            }
        }
        
        if ( d4_cnt == 3 )
        {
            error_flag |= c8800retro_select_demo_example( ctx );
            return error_flag;
        }
    }
    
    return error_flag;
}

static err_t c8800retro_demo_full_charset( c8800retro_t *ctx )
{
    log_printf( &logger, "\r\n ---- Full charset demo example ---- \r\n" );
    log_printf( &logger, " Press the button D4 three times to switch the example \r\n" );
    
    err_t error_flag = c8800retro_clear_display( ctx );
    error_flag |= c8800retro_clear_interrupt( ctx );
    
    for ( ; ; )
    {
        for ( uint8_t cnt = 0; cnt <= 255; cnt++ )
        {
            if ( cnt == 128 )
            {
                cnt = 160;
            }
            error_flag |= c8800retro_display_char( ctx, cnt );
            
            Delay_ms( 200 );
            if ( !c8800retro_get_int_pin( ctx ) )
            {
                uint16_t keypad = C8800RETRO_KEY_NONE;
                uint8_t d4_cnt = 0;
                while ( d4_cnt < 3 )
                {
                    // Pressed button
                    while( c8800retro_get_int_pin( ctx ) );
                    error_flag |= c8800retro_get_keypad( ctx, &keypad );
                    while( !c8800retro_get_int_pin( ctx ) );
                    
                    // Released button
                    while( c8800retro_get_int_pin( ctx ) );
                    error_flag |= c8800retro_clear_interrupt( ctx );
                    while( !c8800retro_get_int_pin( ctx ) );
                    
                    if ( ( keypad & C8800RETRO_KEY_D4 ) != C8800RETRO_KEY_D4 )
                    {
                        break;
                    }
                    d4_cnt++;
                }
                if ( d4_cnt == 3 )
                {
                    error_flag |= c8800retro_select_demo_example( ctx );
                    return error_flag;
                }
            }
            if ( C8800RETRO_ERROR == error_flag )
            {
                log_printf( &logger, "\r\n Error occured. \r\n" );
                return error_flag;
            }
        }
    }
}

static err_t c8800retro_demo_text( c8800retro_t *ctx, uint8_t scroll_mode, uint16_t scroll_speed_ms, uint8_t *text )
{
    log_printf( &logger, "\r\n ---- Text demo example ---- \r\n" );
    log_printf( &logger, " Once it finish scrolling, press the button D4 three times in the next" );
    log_printf( &logger, " 3 seconds to switch the example \r\n" );
    
    err_t error_flag = c8800retro_clear_display( ctx );
    error_flag |= c8800retro_clear_interrupt( ctx );
    
    for ( ; ; )
    {
        uint16_t timeout = 3000;
        
        log_printf( &logger, "\r\n Text scrolling has started. \r\n" );
        error_flag |= c8800retro_display_string( ctx, scroll_mode, scroll_speed_ms, text );
        
        error_flag |= c8800retro_clear_interrupt( ctx );
        
        log_printf( &logger, "\r\n Text scrolling has finished. Press the button D4 three times in the next" );
        log_printf( &logger, " 3 seconds to switch the example. Otherwise, scrolling will start over. \r\n" );
        
        while ( timeout-- > 0 )
        {
            if ( !c8800retro_get_int_pin( ctx ) )
            {
                uint16_t keypad = C8800RETRO_KEY_NONE;
                uint8_t d4_cnt = 0;
                while ( d4_cnt < 3 )
                {
                    // Pressed button
                    while( c8800retro_get_int_pin( ctx ) );
                    error_flag |= c8800retro_get_keypad( ctx, &keypad );
                    while( !c8800retro_get_int_pin( ctx ) );
                    
                    // Released button
                    while( c8800retro_get_int_pin( ctx ) );
                    error_flag |= c8800retro_clear_interrupt( ctx );
                    while( !c8800retro_get_int_pin( ctx ) );
                    
                    if ( ( keypad & C8800RETRO_KEY_D4 ) != C8800RETRO_KEY_D4 )
                    {
                        break;
                    }
                    d4_cnt++;
                }
                if ( d4_cnt == 3 )
                {
                    error_flag |= c8800retro_select_demo_example( ctx );
                    return error_flag;
                }
            }
            Delay_ms ( 1 );
        }
        
        if ( C8800RETRO_ERROR == error_flag )
        {
            log_printf( &logger, "\r\n Error occured. \r\n" );
            return error_flag;
        }
    }
}

static err_t c8800retro_demo_image( c8800retro_t *ctx, uint8_t *p_image )
{
    log_printf( &logger, "\r\n ---- Image demo example ---- \r\n" );
    log_printf( &logger, " Press the button D4 three times to switch the example \r\n" );
    
    err_t error_flag = c8800retro_clear_display( ctx );
    error_flag |= c8800retro_clear_interrupt( ctx );
    
    error_flag |= c8800retro_display_image( ctx, p_image );
            
    for ( ; ; )
    {
        if ( !c8800retro_get_int_pin( ctx ) )
        {
            uint16_t keypad = C8800RETRO_KEY_NONE;
            uint8_t d4_cnt = 0;
            while ( d4_cnt < 3 )
            {
                // Pressed button
                while( c8800retro_get_int_pin( ctx ) );
                error_flag |= c8800retro_get_keypad( ctx, &keypad );
                while( !c8800retro_get_int_pin( ctx ) );
                
                // Released button
                while( c8800retro_get_int_pin( ctx ) );
                error_flag |= c8800retro_clear_interrupt( ctx );
                while( !c8800retro_get_int_pin( ctx ) );
                
                if ( ( keypad & C8800RETRO_KEY_D4 ) != C8800RETRO_KEY_D4 )
                {
                    break;
                }
                d4_cnt++;
            }
            if ( d4_cnt == 3 )
            {
                error_flag |= c8800retro_select_demo_example( ctx );
                return error_flag;
            }
        }
        if ( C8800RETRO_ERROR == error_flag )
        {
            log_printf( &logger, "\r\n Error occured. \r\n" );
            return error_flag;
        }
    }
}

// ------------------------------------------------------------------------ END
