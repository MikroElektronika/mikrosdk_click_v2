/*!
 * \file 
 * \brief Gaussmeter Click example
 * 
 * # Description
 * This example showcases how to configure and use the Gaussmeter Click. This Click measures
 * magnetic fields around the device using a 3 axis measurement system. Alongside the magnetometer,
 * the Click contains an integrated temperature sensor which provides data for the thermal compensation.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the Click and logger modules. 
 * Additional configuring is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function reads data from the magnetometer and the temperature sensor and displays that
 * data using the UART console every 400 milliseconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gaussmeter.h"

// ------------------------------------------------------------------ VARIABLES

static gaussmeter_t gaussmeter;
static log_t logger;
static uint8_t buf_idx;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    gaussmeter_cfg_t cfg;

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

    gaussmeter_cfg_setup( &cfg );
    GAUSSMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gaussmeter_init( &gaussmeter, &cfg );
    Delay_ms ( 100 );
    gaussmeter_default_cfg( &gaussmeter );
    Delay_ms ( 500 );
}

void application_task ( )
{
    float temp_buf[ 4 ] = { 0 };
    uint8_t error_bit;
    uint8_t axis_check;
    uint8_t cnt;

    error_bit = gaussmeter_get_data( &gaussmeter, temp_buf );

    if ( !error_bit )
    {
        axis_check = 1;
        buf_idx = 0;
    }

    for ( cnt = 0; cnt < 4; cnt++ )
    {
        switch ( gaussmeter.aux.command_byte_low & axis_check )
        {
            case 1:
            {
                log_printf( &logger, " * Temperature: %.2f C\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 2:
            {
                log_printf( &logger, " * X-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 4:
            {
                log_printf( &logger, " * Y-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
                break;
            }
            case 8:
            {
                log_printf( &logger, " * Z-axis: %.2f microT\r\n", temp_buf[ buf_idx++ ] );
            }
        }
        axis_check <<= 1;
    }
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms ( 400 );
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
