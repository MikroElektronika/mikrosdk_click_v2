/*!
 * \file 
 * \brief Dac8 Click example
 * 
 * # Description
 * This click carries 12-bit buffered Digital-to-Analog Converter. It converts digital value to 
 * the corresponding voltage level using external voltage reference. 
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C.
 * Configure DAC60501: executes call software reset, disable sync and internal reference and 
 * disable Power-down mode, the set reference voltage is internally divided by a factor of 2,
 * amplifier for corresponding DAC has a gain of 2.
 * Initialization driver enables - SPI, enable DAC8554, also write log.
 * 
 * ## Application Task  
 * This is an example that demonstrates the use of the DAC 8 Click board.
 * DAC 8 board changeing output values:
 * Channel A ~ 2500 mV, Channel B ~ 1250 mV,
 * Channel C ~  625 mV, Channel D ~  312 mV.
 * All data logs write on USB uart changes every 5 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "dac8.h"

// ------------------------------------------------------------------ VARIABLES

static dac8_t dac8;
static log_t logger;

dac8_cfg_data_t cfg_dac;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac8_cfg_t cfg;

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

    dac8_cfg_setup( &cfg );
    DAC8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    
    dac8_init( &dac8, &cfg, DAC8_MASTER_I2C );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  I2C driver init.   \r\n" );
    Delay_ms( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      DAC60501       \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Soft reset      \r\n" );
    dac8_soft_reset( &dac8 );
    Delay_ms( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Disable sync. mode \r\n" );
    dac8_enable_sync( &dac8, DAC8_SYNC_DISABLE );
    Delay_ms( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Set config.:     \r\n" );
    log_printf( &logger, " Enable:             \r\n" );
    log_printf( &logger, " Internal reference  \r\n" );
    log_printf( &logger, " Disable:            \r\n" );
    log_printf( &logger, " Power-down mode     \r\n" );
    dac8_set_config( &dac8, DAC8_CONFIG_REF_PWDWN_ENABLE, DAC8_CONFIG_DAC_PWDWN_DISABLE );
    Delay_ms( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Vref divided by 2  \r\n" );
    log_printf( &logger, "  Set DAC gain of 2  \r\n" );
    dac8_set_gain( &dac8, DAC8_GAIN_REF_DIV_2, DAC8_GAIN_BUFF_GAIN_1 );
    Delay_ms( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " Set Vref ~ 2500 mV  \r\n" );
    dac8_set_vref( &dac8, 2500 );
    Delay_ms( 1000 );

    dac8_init( &dac8, &cfg, DAC8_MASTER_SPI );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  SPI driver init.   \r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "       DAC8554       \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Enable DAC8554   \r\n" );
    dac8_device_enable( &dac8, DAC8_DAC8554_ENABLE );
    Delay_ms( 100 );
}

void application_task ( void )
{
    log_printf( &logger, "---------------------\r\n" );
    
    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_A;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0xFFFF;
    
    log_printf( &logger, " Channel A ~ 2500 mV \r\n" );
    dac8_device_config( &dac8, cfg_dac );
    dac8_load_dac(  &dac8 );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---------------------\r\n" );

    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_B;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0x7FFF;

    log_printf( &logger, " Channel B ~ 1250 mV \r\n" );
    dac8_device_config(  &dac8, cfg_dac );
    dac8_load_dac( &dac8 );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---------------------\r\n" );
    
    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_C;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0x3FFF;

    log_printf( &logger, " Channel C ~  625 mV \r\n" );
    dac8_device_config(  &dac8, cfg_dac );
    dac8_load_dac( &dac8 );
    Delay_ms( 5000 );
    
    log_printf( &logger, "---------------------\r\n" );

    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_D;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0x1FFF;

    log_printf( &logger, " Channel D ~  312 mV\r\n" );
    dac8_device_config(  &dac8, cfg_dac );
    dac8_load_dac(  &dac8 );
    Delay_ms( 5000 );
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
