/*!
 * \file 
 * \brief I2C1Wire Click example
 * 
 * # Description
 * This example showcases how to initialize, confiure and use the I2C 1-Wire click. The click
 * is a I2C (host) to 1-Wire interface (slave). In order for the example to work one or more 
 * 1-Wire (GPIO) click modules are required. Gnd goes to gnd, power goes to power and the cha-
 * nnels are there to read data from connected modules.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function reads all of the channels on the click module and displays any data it acqu-
 * ires from them with a 100 millisecond delay.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "i2c1wire.h"

// ------------------------------------------------------------------ VARIABLES

static i2c1wire_t i2c1wire;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    i2c1wire_cfg_t cfg;

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

    i2c1wire_cfg_setup( &cfg );
    I2C1WIRE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    i2c1wire_init( &i2c1wire, &cfg );
    Delay_1sec( );
}

void application_task ( )
{
    uint8_t chan_state;
    uint8_t cnt_chan;
    uint8_t cnt_val;
    uint8_t id_code[ 9 ];

    chan_state = 1;

    i2c1wire_soft_reset( &i2c1wire );
    Delay_10ms( );
    i2c1wire_set_config( &i2c1wire, I2CONEWIRE_CONFIG_1WS_HIGH |
                                    I2CONEWIRE_CONFIG_SPU_HIGH |
                                    I2CONEWIRE_CONFIG_APU_LOW );
    Delay_10ms( );

    for( cnt_chan = 0; cnt_chan < 8; cnt_chan++ )
    {
        i2c1wire_set_channel( &i2c1wire, cnt_chan );
        i2c1wire_one_wire_reset( &i2c1wire );
        Delay_10ms( );

        i2c1wire_write_byte_one_wire( &i2c1wire, I2CONEWIRE_WIRE_COMMAND_READ_ROM );
        Delay_10ms();

        for( cnt_val = 8; cnt_val > 0; cnt_val-- )
        {
            id_code[ cnt_val ] = i2c1wire_read_byte_one_wire( &i2c1wire );

            if ( id_code[ cnt_val ] == I2CONEWIRE_WIRE_RESULT_OK )
            {
                log_printf( &logger, "\r\n Channel %d : No device on the channel\r\n", ( uint16_t )cnt_chan );
                Delay_100ms( );
                break;
            }
            else if ( chan_state )
            {
                log_printf( &logger, " Channel %d : ID = 0x", ( uint16_t )cnt_chan );
                chan_state = 0;
            }

            log_printf( &logger, "%d", ( uint16_t )id_code[ cnt_val ] );
            Delay_100ms( );
        }

        log_printf( &logger, "\r\n---------------------------------------\r\n" );
    }

    log_printf( &logger, "***\r\n" );
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
