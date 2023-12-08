/*!
 * \file 
 * \brief Driver Click example
 * 
 * # Description
 * This application offering a nine-pole spring terminal that can be used to implement and realize a wide range of different applications.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO driver and selects which inputs will be set in operation.
   Bits from 0 to 6 (selectIN) select inputs from IN1 to IN7, respectively.
 * 
 * ## Application Task  
 * Performs cycles in which selected inputs will be turned on for pulseWidth
   delay time one by one. When one input is turned on, it will be turned off after desired delay time before the next input be turned on.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "driver.h"

// ------------------------------------------------------------------ VARIABLES

static driver_t driver;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    driver_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    driver_cfg_setup( &cfg );
    DRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    driver_init( &driver, &cfg );
}

void application_task ( void )
{
    uint8_t select_in;
    uint8_t temp;
    uint8_t count;

    select_in = 0x7F;
    temp = 1;
    
    for (count = 0; count < 7; count++)
    {
        switch ( select_in & temp )
        {
            case 0x01 :
            {
                driver_set_in1( &driver, ENABLE_IN );
                log_printf( &logger, "OUT1 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in1( &driver, DISABLE_IN );
                log_printf( &logger, "OUT1 disabled\r\n" );
                break;
            }
            case 0x02 :
            {
                driver_set_in2( &driver, ENABLE_IN );
                log_printf( &logger, "OUT2 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in2( &driver, DISABLE_IN );
                log_printf( &logger, "OUT2 disabled\r\n" );
                break;
            }
            case 0x04 :
            {
                driver_set_in3( &driver, ENABLE_IN );
                log_printf( &logger, "OUT3 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in3( &driver, DISABLE_IN );
                log_printf( &logger, "OUT3 disabled\r\n" );
                break;
            }
            case 0x08 :
            {
                driver_set_in4( &driver, ENABLE_IN );
                log_printf( &logger, "OUT4 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in4( &driver, DISABLE_IN );
                log_printf( &logger, "OUT4 disabled\r\n" );
                break;
            }
            case 0x10 :
            {
                driver_set_in5( &driver, ENABLE_IN );
                log_printf( &logger, "OUT5 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in5( &driver, DISABLE_IN );
                log_printf( &logger, "OUT5 disabled\r\n" );
                break;
            }
            case 0x20 :
            {
                driver_set_in6( &driver, ENABLE_IN );
                log_printf( &logger, "OUT6 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in6( &driver, DISABLE_IN );
                log_printf( &logger, "OUT6 disabled\r\n" );
                break;
            }
            case 0x40 :
            {
                driver_set_in7( &driver, ENABLE_IN );
                log_printf( &logger, "OUT7 enabled\r\n" );
                Delay_ms( PULSE_WIDTH );
                driver_set_in7( &driver, DISABLE_IN );
                log_printf( &logger, "OUT7 disabled\r\n" );
                break;
            }
            default :
            {
                break;
            }
        }
        log_printf( &logger, "----------------------\r\n" );
        temp <<= 1;
        
        Delay_ms( 1000 );
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


// ------------------------------------------------------------------------ END
