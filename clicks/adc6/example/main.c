/*!
 * \file 
 * \brief ADC6 Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates the voltage to a
 * digital value and then logs it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and sets configuration which enables channel 0,
 * puts AIN0 on positive analog input and AIN1 on negative analog input,
 * enables internal reference voltage (approximately 2.65V (AVDD = 3.3V)),
 * and also enables bipolar operation mode and puts device on full power mode.
 * When the ADC is configured for unipolar operation, the output code is natural
 * (straight) binary with a zero differential input voltage 
 * resulting in a code of 0x00000000, a midscale voltage resulting in a code 
 * of 0x00800000, and a full-scale input voltage resulting in a code of 0x00FFFFFF.
 * When the ADC is configured for bipolar operation, the output code is offset
 * binary with a negative full-scale voltage resulting in a code of 0x00000000, 
 * a zero differential input voltage resulting in a code of 0x00800000, 
 * and a positive full-scale input voltage resulting in a code of 0x00FFFFFF.
 * 
 * ## Application Task  
 * Gets 24-bit converted data in single read mode and logs data on USB UART.
 * Repeats operation every 500 ms.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc6.h"

// ------------------------------------------------------------------ VARIABLES

static adc6_t adc6;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc6_cfg_t cfg;

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

    adc6_cfg_setup( &cfg );
    ADC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc6_init( &adc6, &cfg );
    adc6_default_cfg( &adc6 );
}

void application_task ( void )
{
    uint32_t adc_value = 0;

    adc_value = adc6_get_adc_data( &adc6 );

    log_printf( &logger, "The ADC value is: 0x%.6LX\r\n", adc_value );

    Delay_ms( 500 );
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
