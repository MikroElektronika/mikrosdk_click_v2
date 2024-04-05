/*!
 * \file 
 * \brief Voltmeter Click example
 * 
 * # Description
 * This application reads the voltage measurement and displays the results on the USB UART.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization the driver and logger.
 * 
 * ## Application Task  
 * Reads the raw ADC measurement once per second and converts it to the proportional voltage level.
 * All data are being displayed on the USB UART where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "voltmeter.h"

// ------------------------------------------------------------------ VARIABLES

static voltmeter_t voltmeter;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    voltmeter_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    //  Click initialization.
    voltmeter_cfg_setup( &cfg );
    VOLTMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    voltmeter_init( &voltmeter, &cfg );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    int16_t adc_value = 0;
    float voltage = 0;

    adc_value = voltmeter_read_raw_data( &voltmeter );
    log_printf( &logger, " ADC Value: %d\r\n", adc_value );

    voltage = voltmeter_calculate_voltage( &voltmeter, adc_value, VOLTMETER_GND_ISO );
    log_printf( &logger, " Voltage  : %.3f V\r\n", voltage );
    log_printf( &logger, "------------------------\r\n");
    Delay_ms ( 1000 );
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
