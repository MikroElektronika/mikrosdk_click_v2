/*!
 * \file 
 * \brief LlcI2c Click example
 * 
 * # Description
 * This click can be utilized as the level converter for logic signals. The topology of this 
 * logic level conversion (LLC) circuit is perfectly suited for the bi-directional I2C communication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init
 * 
 * ## Application Task  
 * Reads the temperature from the Thermo 7 click board and logs data to UART.
 * 
 * *note:* 
 * <pre>
 * Connection between Thermo 7 and I2C-LLC is made through I2C interface.
 * You can connect a Thermo 7 click and I2C-LLC click with the wires to make connection between click boards.
 * We use the Thermo 7 click to demonstrate the functions of the I2C-LLC click.
 * </pre> 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "llci2c.h"

// ------------------------------------------------------------------ VARIABLES

static llci2c_t llci2c;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    llci2c_cfg_t cfg;

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

    llci2c_cfg_setup( &cfg );
    LLCI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    llci2c_init( &llci2c, &cfg );
}

void application_task ( void )
{
    // Thermo 7 measurement Temperature
    uint8_t write_reg = 0x00;
    uint8_t read_reg[ 2 ] = { 0 };
    
    float temp_msb;
    uint8_t temp_lsb;

    llci2c_generic_read ( &llci2c, write_reg, read_reg, 2 );
    
    temp_msb = read_reg[ 0 ];
    temp_lsb = read_reg[ 1 ] & 0xF0;

    if ( temp_lsb & 0x80 ) temp_msb += 0.50;
    if ( temp_lsb & 0x40 ) temp_msb += 0.25;
    if ( temp_lsb & 0x20 ) temp_msb += 0.125;
    if ( temp_lsb & 0x10 ) temp_msb += 0.0625;

    log_info( &logger, " Ambient temperature : %.2f C", temp_msb );
    Delay_ms( 1000 );
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
