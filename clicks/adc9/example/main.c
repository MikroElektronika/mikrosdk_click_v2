/*!
 * \file 
 * \brief Adc9 Click example
 * 
 * # Description
 * This click is 8th channel analog to digital converter expansion board, usefull for projects 
 * where we have demand for multi channel ADC conversion such as microcontrollers with small 
 * number or none analog inputs. It offers integrated features, such as internal oscillator, 
 * temperature sensor and burnout sensor detection, in order to reduce system component count 
 * and total solution cost. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initalizes SPI driver, resets and starts the device, and makes an initial log.
 * 
 * ## Application Task  
 * This is an example that shows the capabilities of the ADC 9 click by calculating voltage level 
 * based on ADC from channels 0(positive) and 1(negative), and logs the result.
 * 
 * ## Additional Function
 * - void measurement_init ( adc9_t *ctx, adc9_rw_t *rw ) - Measurement Initialization function 
 * is used to easily apply desired settings, in this case device is set to read ADC value 
 * from channels 0 (positive) and 1 (negative) with default data format, gain, boost and internal clock.
 * 
 * ## NOTE
 * Depending on the VOLT SEL jumper position on the click board the user needs to set VREF 
 * macro value (mV) in the code.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "adc9.h"

#define VREF  2048

// ------------------------------------------------------------------ VARIABLES

static adc9_t adc9;
static adc9_rw_t adc9_rw;
static log_t logger;

int32_t adc_value;
float m_volts;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

// Measurement Initialization function
void measurement_init ( adc9_t *ctx, adc9_rw_t *rw )
{
    uint8_t cfg_data;
    uint32_t cfg_data_l;
    uint32_t dummy_data;

    rw->dev_adr = ADC9_DEVICE_ADR;
    rw->reg = ADC9_REG_ADC_DATA;
    rw->cmd = ADC9_CMD_INC_READ;
    adc9_read_u32( ctx, rw, &dummy_data );
    Delay_ms( 1 );

    rw->reg = ADC9_REG_CFG_0;
    cfg_data = ADC9_CFG_0_VREF_SEL_0 | ADC9_CFG_0_CLK_SEL_2 |
               ADC9_CFG_0_CS_SEL_0 | ADC9_CFG_0_MODE_CONV;
    adc9_write_u8( ctx, rw, cfg_data );
    Delay_ms( 1 );

    rw->reg = ADC9_REG_CFG_1;
    cfg_data = ADC9_CFG_1_PRE_1 | ADC9_CFG_1_OSR_32 | ADC9_CFG_1_DITHER_DEF;
    adc9_write_u8( ctx, rw, cfg_data );
    Delay_ms( 1 );

    rw->reg = ADC9_REG_CFG_2;
    cfg_data = ADC9_CFG_2_BOOST_X_1 | ADC9_CFG_2_GAIN_X_1 | ADC9_CFG_2_AZ_MUX_DIS | 
               ADC9_CFG_2_AZ_VREF_EN | ADC9_CFG_2_AZ_FREQ_HIGH;
    adc9_write_u8( ctx, rw, cfg_data );
    Delay_ms( 1 );

    rw->reg = ADC9_REG_CFG_3;
    cfg_data = ADC9_CFG_3_CONV_MODE_CONT | ADC9_CFG_3_DATA_FORMAT_DEF | 
               ADC9_CFG_3_CRC_FORMAT_16 | ADC9_CFG_3_CRC_COM_DIS | ADC9_CFG_3_CRC_OFF_CAL_EN |
               ADC9_CFG_3_CRC_GAIN_CAL_EN;
    adc9_write_u8( ctx, rw, cfg_data );
    Delay_ms( 1 );

    rw->reg = ADC9_REG_MUX;
    cfg_data = ADC9_MUX_VIN_POS_CH0 | ADC9_MUX_VIN_NEG_CH1;
    adc9_write_u8( ctx, rw, cfg_data );
    Delay_ms( 1 );

    cfg_data_l = 0;
    rw->reg = ADC9_REG_SCAN;
    adc9_write_u24( ctx, rw, cfg_data_l );
    Delay_ms( 1 );

    cfg_data_l = 0;
    rw->reg = ADC9_REG_OFFSET_CAL;
    adc9_write_u24( ctx, rw, cfg_data_l );
    Delay_ms( 1 );

    cfg_data_l = 0x00800000;
    rw->reg = ADC9_REG_GAIN_CAL;
    adc9_write_u24( ctx, rw, cfg_data_l );
    Delay_ms( 1 );

    cfg_data_l = 0x00900F00;
    rw->reg = ADC9_RSV_REG_W_A;
    adc9_write_u24( ctx, rw, cfg_data_l );
    Delay_ms( 1 );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    adc9_cfg_setup( &cfg );
    ADC9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uint8_t err_flag = adc9_init( &adc9, &cfg );
    if ( ADC9_INIT_ERROR == err_flag )
    {
        log_info( &logger, "---- Error Init ----" );
        for ( ; ; );
    }

    adc9_default_cfg( &adc9, &adc9_rw );
    
    Delay_ms( 1000 );
}

void application_task ( void )
{
    measurement_init( &adc9, &adc9_rw );
    
    while ( adc9_irq_pin_state( &adc9 ) );
    
    adc9_rw.reg = ADC9_DEVICE_ADR;
    adc9_read_def_adc ( &adc9, &adc9_rw, &adc_value );

    log_printf( &logger, "ADC Value : %ld\r\n" , adc_value );
    
    m_volts = adc9_volt_calc ( &adc9, adc_value, VREF, 1 );
    log_printf( &logger, "Voltage in milivolts : %.2f\r\n", m_volts );

    log_printf( &logger, "------------------------\r\n" );
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
