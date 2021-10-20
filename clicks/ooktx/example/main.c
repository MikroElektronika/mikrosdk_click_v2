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
 * This application consists 2 types:
 *  - BYTE_TRANSMIT: Transmiting one by one byte of data
 *  - DATA_TRANSMIT: Transmiting package of data ( 6 bytes in this example )
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ooktx.h"

#define BYTE_TRANSMIT
// #define DATA_TRANSMIT

#define PREABLE_WORD 0xCE35

// ------------------------------------------------------------------ VARIABLES

static ooktx_t ooktx;
static log_t logger;

static uint8_t tx_data[] = "MikroE\r\n";
static uint8_t tx_index = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    ooktx_cfg_t cfg;

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
    log_info(&logger, "Application Init");

    //  Click initialization.

    ooktx_cfg_setup( &cfg );
    OOKTX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ooktx_init( &ooktx, &cfg );
    Delay_100ms( ); 
    
    tx_index = 0;
#ifdef BYTE_TRANSMIT
    log_info(&logger, "Application Task\r\n BYTE TRANSMIT DEMO");
#endif
    
#ifdef DATA_TRANSMIT
    log_info(&logger, "Application Task\r\n DATA TRANSMIT DEMO");
#endif
}

void application_task ( )
{
    uint8_t cnt;
    
    ooktx_communication_init ( &ooktx, OOKTX_CALIBRATION_ENABLE, OOKTX_CONFIGURATION_ENABLE,
                                       OOKTX_CFG_DEFAULT );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        ooktx_communication_transmit ( &ooktx, OOKTX_PREAMBULE );
    }
#ifdef BYTE_TRANSMIT
    ooktx_transmit_byte( &ooktx, 0xCE35, tx_data[ tx_index ] );
    tx_index++;
    if ( tx_data[ tx_index ] == '\0' )
        tx_index = 0;
#endif
    
#ifdef DATA_TRANSMIT
    ooktx_transmit_data( &ooktx, 0xCE35, tx_data, 6 );
#endif

    ooktx_communication_stop( &ooktx );
    
#ifdef BYTE_TRANSMIT
    Delay_ms ( 100 );
#endif
    
#ifdef DATA_TRANSMIT
    Delay_ms ( 2000 );
#endif
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
