/*!
 * \file 
 * \brief 4x4Key Click example
 * 
 * # Description
 * The library covers all the necessary functions to control the 4x4 Key Click.
 * 4x4 Key Click communicates with the target board via SPI interface. 
 * This library contains drivers for reading data from a sensor and get 
 * the position of the pressed button.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring Clicks and log objects.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of 4x4 Key Click board.
 * Detects and logs whether any of the buttons is pressed.
 * Results are being sent to the Usart Terminal
 * where you can track their changes.
 * All data logs on usb uart when the button is triggered.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c4x4key.h"

// ------------------------------------------------------------------ VARIABLES

static c4x4key_t c4x4key;
static log_t logger;

static uint16_t btn_data_old;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c4x4key_cfg_t cfg;

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

    c4x4key_cfg_setup( &cfg );
    C4X4KEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c4x4key_init( &c4x4key, &cfg );
    
    btn_data_old = 0;
    
    log_printf( &logger, "   4x4 Key Click\r\n" );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Press any button\r\n" );
    log_printf( &logger, "--------------------\r\n" );
}

void application_task ( void )
{
    uint16_t btn_data;
    
    btn_data = c4x4key_get_data( &c4x4key );

    if ( btn_data_old != btn_data )
    {
        if ( btn_data == C4X4KEY_BUTTON_0 )
        {
            log_printf( &logger, "         0\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_1 )
        {
            log_printf( &logger, "         1\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_2 )
        {
            log_printf( &logger, "         2\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_3 )
        {
            log_printf( &logger, "         3\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_4 )
        {
            log_printf( &logger, "         4\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_5 )
        {
            log_printf( &logger, "         5\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_6 )
        {
            log_printf( &logger, "         6\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_7 )
        {
            log_printf( &logger, "         7\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_8 )
        {
            log_printf( &logger, "         8\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_9 )
        {
            log_printf( &logger, "         9\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_A )
        {
            log_printf( &logger, "         A\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_B )
        {
            log_printf( &logger, "         B\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_C )
        {
            log_printf( &logger, "         C\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_D )
        {
            log_printf( &logger, "         D\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_STAR )
        {
            log_printf( &logger, "         *\r\n" );
        }
        
        if ( btn_data == C4X4KEY_BUTTON_HASH )
        {
            log_printf( &logger, "         #\r\n" );
        }

        btn_data_old = btn_data;
    }
    Delay_10ms();
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
