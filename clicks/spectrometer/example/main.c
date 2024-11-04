/*!
 * \file 
 * \brief Spectrometer Click example
 * 
 * # Description
 * This Click is an 11-channel spectrometer for spectral identification and color matching. The 
 * spectral response is defined in the wavelengths from approximately 350nm to 1000nm. 8 optical 
 * channels cover the visible spectrum, one channel can be used to measure near infra-red light
 * and one channel is a photo diode without filter (“clear”). The device also integrates a 
 * dedicated channel to detect 50Hz or 60Hz ambient light flicker. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes I2C driver, performs safety check and makes an initial log.
 * 
 * ## Application Task  
 * This example shows the capabilities of the Spectrometer Click
 * by reading out channels with SMUX configrations 1 and 2, detecting 
 * flicker for 100 and 120 Hz and displaying data via USART terminal.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "spectrometer.h"

// ------------------------------------------------------------------ VARIABLES

static spectrometer_t spectrometer;
static log_t logger;

static uint8_t id_val;
static uint16_t ch_0;
static uint16_t ch_1;
static uint16_t ch_2;
static uint16_t ch_3;
static uint16_t ch_4;
static uint8_t f_val;
static uint8_t adc_buf[ 13 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectrometer_cfg_t cfg;

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

    spectrometer_cfg_setup( &cfg );
    SPECTROMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectrometer_init( &spectrometer, &cfg );
    Delay_ms ( 100 );
    
    spectrometer_generic_read ( &spectrometer, SPECTROMETER_ID, &id_val, 1 );
    if ( id_val == SPECTROMETER_ID_VALUE )
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "   Spectrometer  Click   \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "-------------------------\r\n" );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n" );
        log_printf( &logger, "-------------------------\r\n" );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    spectrometer_def_cfg( &spectrometer );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    spectrometer_raw_rd_val_mode_1( &spectrometer, &adc_buf[ 0 ] );
    
    ch_0 = adc_buf[ 1 ];
    ch_0 <<= 8;
    ch_0 |= adc_buf[ 0 ];
    log_printf( &logger, " ADC0/F1 : %u\r\n", ch_0 );

    ch_1 = adc_buf[ 3 ];
    ch_1 <<= 8;
    ch_1 |= adc_buf[ 2 ];
    log_printf( &logger, " ADC1/F2 : %u\r\n", ch_1 );

    ch_2 = adc_buf[ 5 ];
    ch_2 <<= 8;
    ch_2 |= adc_buf[ 4 ];
    log_printf( &logger, " ADC2/F3 : %u\r\n", ch_2 );

    ch_3 = adc_buf[ 7 ];
    ch_3 <<= 8;
    ch_3 |= adc_buf[ 6 ];
    log_printf( &logger, " ADC3/F4 : %u\r\n", ch_3 );

    ch_4 = adc_buf[ 9 ];
    ch_4 <<= 8;
    ch_4 |= adc_buf[ 8 ];
    log_printf( &logger, " ADC4/Clear : %u\r\n", ch_4 );

    spectrometer_raw_rd_val_mode_2( &spectrometer, &adc_buf[ 0 ] );
    
    ch_0 = adc_buf[ 1 ];
    ch_0 <<= 8;
    ch_0 |= adc_buf[ 0 ];
    log_printf( &logger, " ADC0/F5 : %u\r\n", ch_0 );

    ch_1 = adc_buf[ 3 ];
    ch_1 <<= 8;
    ch_1 |= adc_buf[ 2 ];
    log_printf( &logger, " ADC1/F6 : %u\r\n", ch_1 );

    ch_2 = adc_buf[ 5 ];
    ch_2 <<= 8;
    ch_2 |= adc_buf[ 4 ];
    log_printf( &logger, " ADC2/F7 : %u\r\n", ch_2 );

    ch_3 = adc_buf[ 7 ];
    ch_3 <<= 8;
    ch_3 |= adc_buf[ 6 ];
    log_printf( &logger, " ADC3/F8 : %u\r\n", ch_3 );

    ch_4 = adc_buf[ 9 ];
    ch_4 <<= 8;
    ch_4 |= adc_buf[ 8 ];
    log_printf( &logger, " ADC4/Clear : %u\r\n", ch_4 );

    f_val = spectrometer_flicker_detection( &spectrometer );

    log_printf( &logger, " Flicker : " );
    if ( f_val == SPECTROMETER_UNKNOWN_FREQ )
    {
        log_printf( &logger, "unknown\r\n" );
    }
    else if ( f_val == SPECTROMETER_DETECTED_100_HZ )
    {
        log_printf( &logger, "100 Hz detected\r\n" );
    }
    else if ( f_val == SPECTROMETER_DETECTED_120_HZ )
    {
        log_printf( &logger, "120 Hz detected\r\n" );
    }
    else
    {
        log_printf( &logger, "Error in reading\r\n" );
    }

    log_printf( &logger, "-----------------\r\n" );
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
