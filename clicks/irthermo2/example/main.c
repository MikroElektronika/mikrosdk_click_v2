/*!
 * @file main.c
 * @brief IrThermo2 Click example
 * 
 * # Description
 * IrThermo 2 is a non-contact temperature measurement click. The sensor absorbs the infrared 
 * radiation emitted by the target object (withing the sensor’s field of view) and 
 * the integrated math engine calculates its temperature by comparing it with the temperature 
 * of the silicon die. The measurement range of the sensor is between –40°C to 125°C.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enable's - I2C, set default configuration and start write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of IrThermo 2 Click board.
 * Measures the object temperature value from sensor and calculate temperature in degrees Celsius [ C ].
 * Results are being sent to the USART Terminal where you can track their changes.
 * All data logs on usb uart for aproximetly every 5 sec when the data value changes.
 * 
 *
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "irthermo2.h"


static irthermo2_t irthermo2;
static log_t logger;

static float temperature;


void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo2_cfg_t cfg;

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

    irthermo2_cfg_setup( &cfg );
    IRTHERMO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo2_init( &irthermo2, &cfg );

    irthermo2_default_cfg( &irthermo2 );
    Delay_ms( 100 );
    log_info( &logger, "---- Application Task ----" );
}

void application_task ( void )
{
    temperature = irthermo2_get_object_temperature_c( &irthermo2 );

    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );

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
