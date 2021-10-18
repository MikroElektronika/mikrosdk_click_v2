/*!
 * \file 
 * \brief 8pinI2c Click example
 * 
 * # Description
 * This demo example reads temperature detected by Surface temp click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures a Surface temp click board.
 * 
 * ## Application Task  
 * Reads the temperature detected by Surface temp click board and 
 * logs it on the USB UART each second.
 * 
 * @note
 * In order to run this example successfully, a Surface temp click board needs to be 
 * connected properly to an 8-pin I2C click board.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c8pini2c.h"

// ------------------------------------------------------------------ VARIABLES

static c8pini2c_t c8pini2c;
static log_t logger;

// Surface temp click - example
#define SURFACE_TEMP_DEVICE_SLAVE_ADDRESS 0x48
#define SURFACE_TEMP_REG_SOFT_RESET       0x2F
#define SURFACE_TEMP_REG_ID               0x0B
#define SURFACE_TEMP_REG_CONFIG           0x03
#define SURFACE_TEMP_REG_TEMP_MSB         0x00

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void surfacetemp_soft_reset (  )
{
    uint8_t tx_data;

    tx_data = SURFACE_TEMP_REG_SOFT_RESET;

    c8pini2c_generic_write ( &c8pini2c, SURFACE_TEMP_DEVICE_SLAVE_ADDRESS, 
                                        0, &tx_data, 1 );
}

uint8_t surfacetemp_setup (  )
{
    uint8_t tmp;

    surfacetemp_soft_reset( );
    Delay_100ms( );
    c8pini2c_generic_read( &c8pini2c, SURFACE_TEMP_DEVICE_SLAVE_ADDRESS, 
                                      SURFACE_TEMP_REG_ID, &tmp, 1 );

    if ( tmp != 0xCB )
    {
        return 1;
    }
    tmp = 0x93;
    c8pini2c_generic_write( &c8pini2c, SURFACE_TEMP_DEVICE_SLAVE_ADDRESS, 
                                       SURFACE_TEMP_REG_CONFIG, &tmp, 1 );

    return 0;
}

float surfacetemp_get_temperature (  )
{
    uint8_t rx_buff[ 2 ];
    int16_t temp;
    float temperature;

    c8pini2c_generic_read( &c8pini2c, SURFACE_TEMP_DEVICE_SLAVE_ADDRESS, 
                                      SURFACE_TEMP_REG_TEMP_MSB, &rx_buff[ 0 ], 2 );

    temp = rx_buff[ 0 ];
    temp <<= 8;
    temp |= rx_buff[ 1 ];
    temp &= 0xFFF8;

    temperature = (float)(temp);
    temperature *= 0.0078;

    return temperature;
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c8pini2c_cfg_t cfg;

    uint8_t status;

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

    c8pini2c_cfg_setup( &cfg );
    C8PINI2C_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c8pini2c_init( &c8pini2c, &cfg );

    status = surfacetemp_setup( );
    if ( status == 0 )
    {
        log_printf( &logger, "--- INIT DONE --- \r\n" );
    }
    else
    {
        log_printf( &logger, "--- INIT ERROR --- \r\n" );
        for( ; ; );
    }
}

void application_task ( void )
{
    float temperature;

    temperature = surfacetemp_get_temperature( );
    log_printf( &logger, "> Temperature : %.2f Celsius\r\n", temperature );
    Delay_ms( 1000 );
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
