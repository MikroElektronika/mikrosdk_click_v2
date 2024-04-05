/*!
 * \file 
 * \brief Slider2 Click example
 * 
 * # Description
 * This click utilizes potentiometer with long travel distance of the wiper 
 * witch allows more accurate movements and combined with the high-quality 
 * manufacturing process it allows to dial-in the desired voltage with ease.
 * Its wiper terminal outputs voltage in the range from 0 to 4.096V. 
 * The used potentiometer is linear, so the wiper potential changes linearly with its position.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init and ADC init.
 * 
 * ## Application Task  
 * Read Slider data value and this data logs to USBUART every 500ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "slider2.h"

// ------------------------------------------------------------------ VARIABLES

static slider2_t slider2;
static log_t logger;


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    slider2_cfg_t cfg;

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

    slider2_cfg_setup( &cfg );
    SLIDER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    slider2_init( &slider2, &cfg );
    slider2_default_cfg( &slider2);

}

void application_task ( void )
{
    slider2_data_t tmp;
    
    //  Task implementation.
    
    tmp = slider2_generic_read ( &slider2 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    
    Delay_ms ( 500 );

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
