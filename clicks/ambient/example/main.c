/*!
 * \file 
 * \brief Ambient Click example
 * 
 * # Description
 * This application turns light intensity into voltage.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables GPIO,initializationADC, also write log.
 * 
 * ## Application Task  
 *  This is an example which demonstrates the use of Ambient click board.
 *  Ambient click reads ADC value and converts to light intensity [ uW/cm2 ].
 *  Results are being sent to the Usart Terminal where you can track their changes.
 *  All data logs on USB uart change for every 1 sec.
 *
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient.h"

// ------------------------------------------------------------------ VARIABLES

static ambient_t ambient;
static log_t logger;

uint16_t value_adc;
uint16_t light;

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient_cfg_t cfg;

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

    ambient_cfg_setup( &cfg );
    AMBIENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient_init( &ambient, &cfg );

    log_printf( &logger, "      Initialization ADC      " );
    Delay_ms( 100 );
}

void application_task ( void )
{
    ambient_data_t tmp;
    
    //  Task implementation.
    
    tmp = ambient_generic_read ( &ambient );
    light = ambient_calculate_light_intensity( &ambient, tmp, AMBIENT_VCC_3_3, AMBIENT_RES_12_BIT );

    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    log_printf( &logger, "Light Intensity: %d uW/cm2 \r\n", light );

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
