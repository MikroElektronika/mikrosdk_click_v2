/*!
 * \file 
 * \brief Water Detect Click example
 * 
 * # Description
 * Water Detect click is used for detecting water and other electroconductive liquids. If the detection area is wet the output of Microchip's MCP606 CMOS op-amp will go positive, signaling the presence of liquid.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO and LOG structures, set INT pins as input and starts to write log.
 * 
 * ## Application Task  
 * Reads device status and determines if there are water presence or not.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "waterdetect.h"

// ------------------------------------------------------------------ VARIABLES

static waterdetect_t waterdetect;
static log_t logger;

uint8_t wd_state = 0;
uint8_t wd_state_old = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    waterdetect_cfg_t cfg;

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

    waterdetect_cfg_setup( &cfg );
    WATERDETECT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    waterdetect_init( &waterdetect, &cfg );
    Delay_100ms();
    
    log_printf( &logger, "  Initialization Driver   \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
    log_printf( &logger, "  Wait to detect water... \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
}

void application_task ( void )
{
    wd_state = waterdetect_get_status( &waterdetect );

    if ( wd_state > wd_state_old )
    {
        log_printf( &logger, " >  Water is detected  < \r\n" );
        log_printf( &logger, "------------------------- \r\n" );
        wd_state_old = 1;
    }

    if ( wd_state < wd_state_old )
    {
        log_printf( &logger, " There is no water \r\n" );
        log_printf( &logger, "------------------- \r\n" );
        wd_state_old = 0;
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
