/*!
 * \file 
 * \brief Joystick2 Click example
 * 
 * # Description
 * The demo application shows reading the joistick position ..
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Reset device and settings the click in the default configuration.
 * 
 * ## Application Task  
 * It reads the position of the joystick,
 * if it detects that the joystick has moved from the zero position,
 * it prints a message about the current position.
 *
 * @note: The I2C peripheral lines external pull up can be required.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "joystick2.h"

// ------------------------------------------------------------------ VARIABLES

static joystick2_t joystick2;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    joystick2_cfg_t cfg;

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

    joystick2_cfg_setup( &cfg );
    JOYSTICK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    joystick2_init( &joystick2, &cfg );

    joystick2_reset( &joystick2 );
    joystick2_default_cfg( &joystick2 );
    log_info( &logger, "---- JOYSTICK START ----" );
}

void application_task ( void )
{
    uint8_t joystick_pos;

    //  Task implementation.

    joystick_pos = joystick2_get_position( &joystick2 );

    switch ( joystick_pos )
    {
        case JOYSTICK2_BUTTON_ACTIVE:
        {
            log_info( &logger, "--- Button is pressed!!! ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_RIGHT:
        {
            log_info( &logger, "--- Joystick position [RIGHT] ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_LEFT:
        {
            log_info( &logger, "--- Joystick position [LEFT] ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_UP:
        {
            log_info( &logger, "--- Joystick position [UP] ---" );
            Delay_ms ( 300 );
            break;
        }
        case JOYSTICK2_POSITION_DOWN:
        {
            log_info( &logger, "--- Joystick position [DOWN] ---" );
            Delay_ms ( 300 );
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
