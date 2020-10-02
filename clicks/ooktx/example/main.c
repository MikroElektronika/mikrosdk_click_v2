/*!
 * \file 
 * \brief OOK TX Click example
 * 
 * # Description
 * This example showcases how to initialize and use the OOK TX click. The click encodes information
 * using the On-Off Keying modulation, embeds it in a 433 MHz radio signal and acts as a transmitter
 * for this signal. The OOK RX click should play the role of the receiver in this communication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function initiates the radio signal communication, sends an 8 byte preambule, 2 start
 * package bytes to help the receiver differentiate actual data packages from signal glitches,
 * sends the actual data byte and stops the communication in one iteration.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ooktx.h"

// ------------------------------------------------------------------ VARIABLES

static ooktx_t ooktx;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    ooktx_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    ooktx_cfg_setup( &cfg );
    OOKTX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ooktx_init( &ooktx, &cfg );
    Delay_100ms( ); 
}

void application_task ( )
{
    uint8_t cnt;
    uint8_t inc;

    ooktx_communication_init ( &ooktx, OOKTX_CALIBRATION_ENABLE, OOKTX_CONFIGURATION_ENABLE,
                                       OOKTX_CFG_DEFAULT );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        ooktx_communication_transmit ( &ooktx, OOKTX_PREAMBULE );
    }
    
    ooktx_communication_transmit( &ooktx, 0xCE );
    ooktx_communication_transmit( &ooktx, 0x35 );
    ooktx_communication_transmit( &ooktx, inc++ );

    ooktx_communication_stop( &ooktx );
    Delay_ms ( 1000 );
}

void main ( )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
