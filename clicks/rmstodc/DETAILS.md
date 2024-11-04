
# RMS to DC Click

RMS to DC Click is a Click board™ that is used to convert the RMS of the input signal into a DC voltage, with a value directly readable over the I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/rmstodc_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/rms-to-dc-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the RmstoDc Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RmstoDc Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void rmstodc_cfg_setup ( rmstodc_cfg_t *cfg ); 
 
- Initialization function.
> RMSTODC_RETVAL rmstodc_init ( rmstodc_t *ctx, rmstodc_cfg_t *cfg );

- Generic write function.
> void rmstodc_generic_write ( rmstodc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


#### Example key functions :

- ADC Read function.
> uint16_t rms2dc_read_adc ( rmstodc_t *ctx );
 
- Get Output Voltage function.
> uint16_t rms2dc_vout_adc ( rmstodc_t *ctx, uint16_t vcc_sel );

- Enable function.
> void rms2dc_enable ( rmstodc_t *ctx, uint8_t state );

## Examples Description

> This application convert the RMS of the input signal into a DC voltage.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C interface and turns ON the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    rmstodc_cfg_t cfg;

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

    rmstodc_cfg_setup( &cfg );
    RMSTODC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rmstodc_init( &rmstodc, &cfg );
    
    rms2dc_enable( &rmstodc, RMS2DC_DEVICE_EN );
}
  
```

### Application Task

> Reads DC output voltage calculated to mV and
   sends results to the serial terminal.

```c

void application_task ( void )
{
    out_volt_dc = rms2dc_vout_adc( &rmstodc, RMS2DC_VCC_3V3 );
    
    log_printf(&logger,"%u mV\r\n",out_volt_dc);
    
    Delay_ms ( 300 );
} 

```

## Note

> Note : The input voltage frequency should be in the range from 50Hz to 250kHz.
> Also the input voltage amplitude must be lower than 5V.
> In this conditions the device can convert the RMS signal, in every form, to DC signal.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RmstoDc

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
