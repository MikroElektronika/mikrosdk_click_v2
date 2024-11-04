/*!
 * \file 
 * \brief Rs232Spi Click example
 * 
 * # Description
 * This example showcases how to initialize and use the RS232 SPI Click. The Click has a uni-
 * versal asynchronous transceiver which uses a SPI serial interface to communicate with the 
 * MCU. In order for this example to work, 2 clicks are needed - a receiver and a transmitter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and Click modules. Additional configura-
 * ting is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function receives and displays UART data in the "read mode" and sends the predefined 
 * message in the "write mode".
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "rs232spi.h"

// ------------------------------------------------------------------ VARIABLES

static rs232spi_t rs232spi;
static log_t logger;

static const uint8_t message[ 9 ] = { 'M', 'i', 'k', 'r', 'o', 'E', 13, 10, 0 };

static const uint8_t RX_MODE = 1;
static const uint8_t TX_MODE = 0;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    rs232spi_cfg_t cfg;

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

    rs232spi_cfg_setup( &cfg );
    RS232SPI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rs232spi_init( &rs232spi, &cfg );
    Delay_ms ( 100 );
    rs232spi_digital_write_rst( &rs232spi, 1 );
    Delay_ms ( 100 );
    rs232spi_default_cfg( &rs232spi, 115200 );
    Delay_ms ( 100 );
    rs232spi_flush( &rs232spi );
    Delay_ms ( 100 );
    log_printf( &logger, "App init done...\r\n" );
}

void application_task ( )
{
    uint8_t mode = RX_MODE;
    uint8_t cnt;
    char txt;

    if ( mode == RX_MODE )
    {
        if ( rs232spi_data_ready( &rs232spi ) != 0 )
        {
            txt = rs232spi_transfer( &rs232spi, RS232SPI_CMD_READ_DATA );
            log_printf( &logger, "%c", txt );
        }
    }
    else if ( mode == TX_MODE )
    {
        for ( cnt = 0; cnt < 9; cnt++ )
        {
            rs232spi_data_write( &rs232spi, message[ cnt ] );
            Delay_ms ( 500 );
        }
    }
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
