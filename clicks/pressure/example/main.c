/*!
 * \file main.c
 * \brief Pressure Click example
 *
 * # Description
 * This is a example which demonstrates the use of Pressure Click board.
 * Measured pressure and temperature data from the LPS331AP sensor on Pressure
 * click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C/SPI serial interface and puts a device to the initial state.
 * Also initializes UART console module for results logging.
 *
 * ## Application Task
 * Reads the pressure and temperature results in standard units when
 * measurement was done and sends results to the console (usb uart terminal).
 * Repeats operation every 500ms.
 *
 * \author Nemanja Medakovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "pressure.h"


// ------------------------------------------------------------------ VARIABLES

static pressure_t pressure;
static log_t console;
static const uint8_t deg_cels[ 3 ] = { 176, 'C', 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init( void )
{
    pressure_cfg_t pressure_cfg;
    log_cfg_t console_cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_info( &console, "---- Application Init ----" );

    //  Click initialization.
    pressure_cfg_setup( &pressure_cfg );
    PRESSURE_MAP_MIKROBUS( pressure_cfg, MIKROBUS_1 );
    pressure_init( &pressure, &pressure_cfg );
    pressure_sw_reset( &pressure );
    pressure_default_cfg( &pressure );
}

void application_task( void )
{
    uint8_t status;
    float press;
    float temp;

    status = pressure_get_status( &pressure, PRESSURE_FLAG_MASK_P_DATA_RDY |
                                             PRESSURE_FLAG_MASK_T_DATA_RDY );

    while ( !status )
    {
        status = pressure_get_status( &pressure, PRESSURE_FLAG_MASK_P_DATA_RDY |
                                                 PRESSURE_FLAG_MASK_T_DATA_RDY );
    }

    press = pressure_get_pressure( &pressure );
    temp = pressure_get_temperature( &pressure );

    log_printf( &console, "** Pressure is %.2f mbar\r\n", press );
    log_printf( &console, "** Temperature is %.2f ", temp );
    log_printf( &console, "%s\r\n", deg_cels );
    log_printf( &console, "**************************************\r\n" );

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
