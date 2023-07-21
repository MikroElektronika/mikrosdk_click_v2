/*!
 * \file 
 * \brief Opto 3 Click example
 * 
 * # Description
 * Opto 3 click to be used in applications that require reinforced galvanic 
 * isolation for both their input and output stages.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO interface.
 * 
 * ## Application Task 
 * Reads the input pins state and sets their respective output pins to the same logic state.
 * The output pins state will be displayed on the USB UART where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "opto3.h"

// ------------------------------------------------------------------ VARIABLES

static opto3_t opto3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    opto3_cfg_t cfg;

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
    opto3_cfg_setup( &cfg );
    OPTO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto3_init( &opto3, &cfg );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t out1_state = 0;
    static uint8_t out2_state = 0;
    uint8_t in1_state = 0;
    uint8_t in2_state = 0;

    in1_state = opto3_get_in1( &opto3 );
    in2_state = opto3_get_in2( &opto3 );
    
    if ( in1_state != out1_state )
    {
        out1_state = in1_state;
        opto3_set_out1( &opto3, out1_state );
        log_printf( &logger, " OUT1 state: %u\r\n", ( uint16_t ) out1_state );
    }
    
    if ( in2_state != out2_state )
    {
        out2_state = in2_state;
        opto3_set_out2( &opto3, out2_state );
        log_printf( &logger, " OUT2 state: %u\r\n", ( uint16_t ) out2_state );
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
