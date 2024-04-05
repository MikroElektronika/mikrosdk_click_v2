/*!
 * @file 
 * @brief UvcLight Click example
 * 
 * # Description
 * This click has ultraviolet LEDs with 275nm wavelength. UVC radiation refers to wavelengths 
 * shorter than 280 nm. Because of the spectral sensitivity of DNA, only the UVC region 
 * demonstrates significant germicidal properties.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver.
 * 
 * ## Application Task  
 * Increases and decreases the pwm duty cycle.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * CAUTION! High intensity UV Light - avoid eye and skin exposure. Avoid looking direclty at light!
 * 
 * @author Nikola Peric
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uvclight.h"

// ------------------------------------------------------------------ VARIABLES

static uvclight_t uvclight;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uvclight_cfg_t cfg;

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

    uvclight_cfg_setup( &cfg );
    UVCLIGHT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uvclight_init( &uvclight, &cfg );

    uvclight_set_duty_cycle ( &uvclight, 0.0 );
    uvclight_pwm_start( &uvclight );
    Delay_ms ( 100 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{
    static int8_t duty_cnt = 1;
    static int8_t duty_inc = 1;
    float duty = duty_cnt / 10.0;

    uvclight_set_duty_cycle ( &uvclight, duty );
    log_printf( &logger, "Duty: %d%%\r\n", ( uint16_t )( duty_cnt * 10 ) );
    Delay_ms ( 500 );

    if ( 10 == duty_cnt ) 
    {
        duty_inc = -1;
    }
    else if ( 0 == duty_cnt ) 
    {
        log_printf( &logger, "Cooldown 2 SEC\r\n");
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
        duty_inc = 1;
    }
    duty_cnt += duty_inc;
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
