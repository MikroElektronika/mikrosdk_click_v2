/*!
 * \file 
 * \brief Adc3 Click example
 * 
 * # Description
 * ADC 3 Click represent 16-bit multichannel analog-to-digital converter. 
 * The click has four pairs of screw terminals onboard, letting you access the chip’s four differential input channels.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the ADC 3 Click 
 * by taking voltage measurements from all four channel. Results are being sent to the UART Terminal 
 * where you can track their changes. All data logs write on USB UART and changes for every 1 sec.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc3.h"

// ------------------------------------------------------------------ VARIABLES

static adc3_t adc3;
static log_t logger;

static float read_volt;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc3_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    adc3_cfg_setup( &cfg );
    ADC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc3_init( &adc3, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ------ ADC 3 Click ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    adc3_default_cfg( &adc3 );
    Delay_ms ( 100 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{

    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_1, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 1 : %0.2f  V \r\n", read_volt );

    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_2, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 2 : %0.2f  V \r\n", read_volt );
    
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_3, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 3 : %0.2f  V \r\n", read_volt );
    
    read_volt = adc3_read_voltage( &adc3, ADC3_SELECT_CHANNEL_4, ADC3_SAMPLE_RATE_12, ADC3_PGA_GAIN_X1 );
    Delay_ms ( 100 );
    log_printf( &logger, "Channel 4 : %0.2f  V \r\n", read_volt );
    
    log_printf( &logger, "--------------------------\r\n" );
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
