/*!
 * \file 
 * \brief Boost Click example
 *
 * # Description
 * Boost click provides an adjustable output voltage through the onboard DAC that drives the FB 
 * pin of the MIC2606 to set desired output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver for serial communication and puts the device to power ON state.
 * Also, initializes logger module for message and results sending.
 *
 * ## Application Task
 * This is a example which demonstrates the use of Boost Click board.
 * Boost Click communicates with register via SPI by reading from MCP3551 chip and writing DAC value to the MCP4921 chip.
 * This example periodicaly increases and decreases voltage in range between 15 and 30 Volts.
 * All data logs write on usb uart for aproximetly every 1 sec.
 *
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "boost.h"

// ------------------------------------------------------------------ VARIABLES

static boost_t boost;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;

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
    log_info( &logger, "---- Application Init... ----" );

    boost_cfg_t boost_cfg;

    //  Click initialization.

    boost_cfg_setup( &boost_cfg );
    BOOST_MAP_MIKROBUS( boost_cfg, MIKROBUS_1 );

    if ( boost_init( &boost, &boost_cfg ) == BOOST_ERROR )
    {
        log_info( &logger, "---- Application Init Error. ----" );
        log_info( &logger, "---- Please, run program again... ----" );

        for ( ; ; );
    }

    log_info( &logger, "---- Application Init Done. ----" );

    boost_device_enable( &boost );

    log_info( &logger, "---- Application Running... ----\n" );
}

void application_task ( void )
{
    for ( uint16_t dac_value = 0; ; dac_value += 100 )
    {
        if ( boost_dac_write( &boost, dac_value ) == BOOST_ERROR )
        {
            break;
        }

        log_printf( &logger, " DAC value [12-bit] : %u\r\n", dac_value );
        Delay_ms( 1000 );

        log_printf( &logger, " VOUT value [V] : %.3f\r\n\n", boost_vout_read( &boost ) );
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
