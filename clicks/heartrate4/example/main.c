/*!
 * \file 
 * \brief HeartRate4 Click example
 * 
 * # Description
 * This example demonstrates the use of Heart rate 4 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, applies default settings, and makes an initial log.
 * 
 * ## Application Task  
 * Reads data from Red diode and displays the results on USB UART if the measured data
 * is above defined threshold, otherwise, it displays desired message on the terminal.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "heartrate4.h"

// ------------------------------------------------------------------ VARIABLES

static heartrate4_t heartrate4;
static log_t logger;

static uint32_t red_samp = 0;
static uint8_t counter = 200;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    heartrate4_cfg_t cfg;

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

    heartrate4_cfg_setup( &cfg );
    HEARTRATE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heartrate4_init( &heartrate4, &cfg );

    Delay_ms( 100 );
    heartrate4_default_cfg( &heartrate4 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( heartrate4_get_intrrupt( &heartrate4, 1 ) & 0x40 )
    {
        red_samp = heartrate4_get_red_val( &heartrate4 );
        counter++;
        
        // If sample pulse amplitude is not under threshold value 0x8000
        if ( red_samp > 0x8000 )
        {
            log_printf( &logger, "%lu\r\n", red_samp );
            Delay_ms( 1 );
            counter = 200;
        }
        else if ( counter > 200 )
        {
            log_printf( &logger, "Place Finger On Sensor\r\n" );
            Delay_ms( 100 );
            counter = 0;
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


// ------------------------------------------------------------------------ END
