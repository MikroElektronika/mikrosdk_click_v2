/*!
 * \file 
 * \brief ADAC Click example
 * 
 * # Description
 * This example showcases how to initialize, configure and use the ADAC click module. The click
 * has an ADC and a DAC. An external power supply sets the maximum voltage of the input analog
 * signal, which is bound to 2.5 V by default. For the input any external analog signal will
 * suffice and a multimeter is needed to read the output on one of the channels. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the click and logger modules. It does a hardware 
 * reset first and after that configures the click module using default settings.
 * 
 * ## Application Task  
 * This function first writes digital values ranging from 0 to 256 to output channel 3 with a 
 * 10 millisecond delay between iterations and after that reads analog values from channel 4 
 * 10 times and displays results in the UART console.  
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adac.h"

// ------------------------------------------------------------------ VARIABLES

static adac_t adac;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    adac_cfg_t cfg;

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

    adac_cfg_setup( &cfg );
    ADAC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adac_init( &adac, &cfg );
    Delay_ms( 100 );
    adac_hardware_reset( &adac );
    Delay_ms( 100 );
    adac_set_configuration( &adac, ADAC_POWER_REF_CTRL, ADAC_VREF_ON, ADAC_NO_OP );
    Delay_ms( 100 );
    log_printf( &logger, "\r\n Click module initialized \r\n" );
    Delay_ms( 500 );
}

void application_task ( )
{
    uint16_t adc_val;
    uint16_t cnt;
    uint8_t chan;

    log_printf( &logger, "\r\n *** DAC : write ***\r\n" );
    adac_set_configuration( &adac, ADAC_DAC_CONFIG, ADAC_NO_OP, ADAC_IO3 );
    Delay_ms( 100 );

    for ( cnt = 0; cnt < 0xFF; cnt +=4 )
    {
        adac_write_dac( &adac, ADAC_PB_PIN3, cnt / 0x100, cnt % 0x100 );
        Delay_ms( 10 );
        log_printf( &logger, " > write... \r\n" );
    }
    
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms( 1000 );

    log_printf( &logger, "\r\n *** ADC : read ***\r\n" );
    adac_set_configuration( &adac, ADAC_ADC_CONFIG, ADAC_NO_OP, ADAC_IO4 );
    Delay_ms( 100 );
    adac_set_configuration( &adac, ADAC_ADC_SEQUENCE, ADAC_SEQUENCE_ON, ADAC_IO4 );

    for( cnt = 0; cnt < 10; cnt++ )
    {
        adc_val = adac_read_adc( &adac, &chan );
        log_printf( &logger, "   channel : %d\r\n", ( uint16_t ) chan );
        log_printf( &logger, "       val : %d\r\n", adc_val ); 
        Delay_ms( 2000 );
    }

    log_printf( &logger, "-------------------\r\n" );
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
