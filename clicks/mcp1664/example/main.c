/*!
 * \file 
 * \brief Mcp1664 Click example
 * 
 * # Description
 * This application turn on and turn off white LEDs.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Enables GPIO and PWM, sets the frequency and duty cycle and enables PWM.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of MCP1664 Click board.
 * It shows how to enable the device and gradualy increase the duty cycle.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mcp1664.h"

// ------------------------------------------------------------------ VARIABLES

static mcp1664_t mcp1664;
static log_t logger;

static float duty_cycle = 0.5;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mcp1664_cfg_t cfg;

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

    mcp1664_cfg_setup( &cfg );
    MCP1664_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mcp1664_init( &mcp1664, &cfg );

    mcp1664_set_duty_cycle( &mcp1664, duty_cycle );
    mcp1664_pwm_start( &mcp1664 );
    Delay_ms ( 1000 );
    log_printf( &logger, "------------------ \r\n" );
    log_printf( &logger, "  MCP1664  Click   \r\n" );
    log_printf( &logger, "------------------ \r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    //  Task implementation.
    
    if ( duty_cycle > 1 )
    {
        duty_cycle = 0.1;
    }
    
    mcp1664_set_duty_cycle ( &mcp1664, duty_cycle );
    duty_cycle += 0.1;
    Delay_100ms();

    log_printf( &logger,  "  Duty cycle is : %d  \r\n", duty_cycle );
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
