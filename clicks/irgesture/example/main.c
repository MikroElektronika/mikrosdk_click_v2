/*!
 * \file 
 * \brief IrGesture Click example
 * 
 * # Description
 * This Click enables contactless gesture recognition: 
 * basic directional swipes (up, down, left or right). 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C,
 * set default configuration, enable geasture sensor and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IR Gesture Click board.
 * IR Gesture Click communicates with register via I2C by write to register and read from register,
 * dececting gesture and write log. Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 1 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irgesture.h"

// ------------------------------------------------------------------ VARIABLES

static irgesture_t irgesture;
static log_t logger;

static uint8_t position;
static uint8_t position_old = 0xFF;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irgesture_cfg_t cfg;

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

    irgesture_cfg_setup( &cfg );
    IRGESTURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irgesture_init( &irgesture, &cfg );
    irgesture_default_cfg( &irgesture );
}

void application_task ( void )
{
    position = irgesture_detect_gesture( &irgesture );

    if ( position_old != position )
    {
        if ( position == IRGESTURE_FAR )
        {
            log_printf( &logger, "       F A R        \r\n" );
        }
        if ( position == IRGESTURE_RIGHT )
        {
            log_printf( &logger, "     R I G H T      \r\n" );
        }
        if ( position == IRGESTURE_LEFT )
        {
            log_printf( &logger, "      L E F T       \r\n" );
        }
        if ( position == IRGESTURE_UP )
        {
            log_printf( &logger, "        U P         \r\n" );
        }
        if ( position == IRGESTURE_DOWN )
        {
            log_printf( &logger, "      D O W N       \r\n" );
        }
        if ( position == IRGESTURE_NEAR )
        {
            log_printf( &logger, "      N E A R       \r\n" );
        }

        position_old = position;
        log_printf( &logger, "--------------------\r\n" );

        Delay_ms( 1000 );
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


// ------------------------------------------------------------------------ END
