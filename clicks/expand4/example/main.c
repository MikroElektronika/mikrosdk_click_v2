/*!
 * \file 
 * \brief Expand4 Click example
 * 
 * # Description
 * Example demonstrates use of Expand 4 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - Clear TPIC6A595 register and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Expand 4 Click board.
 * In this example, the LED pin mask is transferred via SPI bus,
 * LEDs connected to D0-D7 pins are lit accordingly by turning ON LEDs from D0 to D7 for 3 sec.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 3 sec. when the change pin who is connected.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "expand4.h"

// ------------------------------------------------------------------ VARIABLES

static expand4_t expand4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    expand4_cfg_t cfg;

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

    expand4_cfg_setup( &cfg );
    EXPAND4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand4_init( &expand4, &cfg );
    expand4_reset( &expand4 );
}

void application_task ( void )
{
    uint8_t pin_position;

    for ( pin_position = 0; pin_position < 8; pin_position++ )
    {
        expand4_disable_output( &expand4 );
        Delay_ms( 100 );

        expand4_turn_on_by_position( &expand4, pin_position );
        Delay_ms( 100 );

        log_printf( &logger, " D%d", pin_position );

        expand4_enable_output( &expand4 );
        Delay_ms( 3000 );
    }

    log_printf( &logger, "\n----------------------------------\n");
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

// ------------------------------------------------------------------------ END
