
---
# DAC 8 click

DAC 8 Click is a compact add-on board that contains a fully-featured, general-purpose voltage-output digital-to-analog converter. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac8_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/dac-8-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Dac8 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac8 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac8_cfg_setup ( dac8_cfg_t *cfg ); 
 
- Initialization function.
> DAC8_RETVAL dac8_init ( dac8_t *ctx, dac8_cfg_t *cfg );


#### Example key functions :

- The function set configuration of the DAC8554, 16-bit, quad-channel, ultra-low glitch, voltage 
- output digital-to-analog converter on DAC 8 Click board.
> void dac8_device_config ( dac8_t *ctx, dac8_cfg_data_t cfg_data );
 
- The function load DAC s are simultaneously updated with the contents of the corresponding data 
- buffers. Used as a positive edge triggered timing signal for asynchronous DAC updates. Data 
- buffers of all channels must be loaded with desired data before call Load DAC function.
> void dac8_load_dac ( dac8_t *ctx );

- The function set Vref ( mV ) by write 12-bit to the DAC data register of the DAC60501, 16-Bit, 
- 14-Bit, and 12-Bit, 1-LSB INL, Voltage-Output DACs
- With Precision Internal Reference on DAC 8 Click board.
> DAC8_RETVAL dac8_set_vref ( dac8_t *ctx, uint16_t vref_mv );

## Examples Description

> This click carries 12-bit buffered Digital-to-Analog Converter. It converts digital value to 
> the corresponding voltage level using external voltage reference. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C.
> Configure DAC60501: executes call software reset, disable sync and internal reference and 
> disable Power-down mode, the set reference voltage is internally divided by a factor of 2,
> amplifier for corresponding DAC has a gain of 2.
> Initialization driver enables - SPI, enable DAC8554, also write log.

```c

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
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "      DAC60501       \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Soft reset      \r\n" );
    dac8_soft_reset( &dac8 );
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Disable sync. mode \r\n" );
    dac8_enable_sync( &dac8, DAC8_SYNC_DISABLE );
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Set config.:     \r\n" );
    log_printf( &logger, " Enable:             \r\n" );
    log_printf( &logger, " Internal reference  \r\n" );
    log_printf( &logger, " Disable:            \r\n" );
    log_printf( &logger, " Power-down mode     \r\n" );
    dac8_set_config( &dac8, DAC8_CONFIG_REF_PWDWN_ENABLE, DAC8_CONFIG_DAC_PWDWN_DISABLE );
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Vref divided by 2  \r\n" );
    log_printf( &logger, "  Set DAC gain of 2  \r\n" );
    dac8_set_gain( &dac8, DAC8_GAIN_REF_DIV_2, DAC8_GAIN_BUFF_GAIN_1 );
    Delay_ms ( 100 );

    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, " Set Vref ~ 2500 mV  \r\n" );
    dac8_set_vref( &dac8, 2500 );
    Delay_ms ( 1000 );

    dac8_init( &dac8, &cfg, DAC8_MASTER_SPI );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  SPI driver init.   \r\n" );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "       DAC8554       \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Enable DAC8554   \r\n" );
    dac8_device_enable( &dac8, DAC8_DAC8554_ENABLE );
    Delay_ms ( 100 );
}
  
```

### Application Task

> This is an example that demonstrates the use of the DAC 8 Click board.
> DAC 8 board changeing output values:
> Channel A ~ 2500 mV, Channel B ~ 1250 mV,
> Channel C ~  625 mV, Channel D ~  312 mV.
> All data logs write on USB uart changes every 5 sec.

```c

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
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );

    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_B;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0x7FFF;

    log_printf( &logger, " Channel B ~ 1250 mV \r\n" );
    dac8_device_config(  &dac8, cfg_dac );
    dac8_load_dac( &dac8 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );
    
    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_C;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0x3FFF;

    log_printf( &logger, " Channel C ~  625 mV \r\n" );
    dac8_device_config(  &dac8, cfg_dac );
    dac8_load_dac( &dac8 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "---------------------\r\n" );

    cfg_dac.addr = DAC8_ADDR_DEFAULT;
    cfg_dac.ctrl_upd_an_out = DAC8_CTRL_UPD_AN_OUT_SINGLE_CH_STORE;
    cfg_dac.dac_sel = DAC8_DAC_SEL_CH_D;
    cfg_dac.pwr_mode = DAC8_PWR_MODE_POWER_UP;
    cfg_dac.dac_val = 0x1FFF;

    log_printf( &logger, " Channel D ~  312 mV\r\n" );
    dac8_device_config(  &dac8, cfg_dac );
    dac8_load_dac(  &dac8 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac8

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
