
---
# RMS to DC Click

> [RMS to DC Click](https://www.mikroe.com/?pid_product=MIKROE-3311) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3311&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application convert the RMS of the input signal into a DC voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RmstoDc

### Example Key Functions

- `rmstodc_cfg_setup` Config Object Initialization function. 
```c
void rmstodc_cfg_setup ( rmstodc_cfg_t *cfg );
``` 
 
- `rmstodc_init` Initialization function. 
```c
err_t rmstodc_init ( rmstodc_t *ctx, rmstodc_cfg_t *cfg );
```

- `rmstodc_generic_write` Generic write function. 
```c
void rmstodc_generic_write ( rmstodc_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

- `rms2dc_read_adc` ADC Read function. 
```c
uint16_t rms2dc_read_adc ( rmstodc_t *ctx );
```
 
- `rms2dc_vout_adc` Get Output Voltage function. 
```c
uint16_t rms2dc_vout_adc ( rmstodc_t *ctx, uint16_t vcc_sel );
```

- `rms2dc_enable` Enable function. 
```c
void rms2dc_enable ( rmstodc_t *ctx, uint8_t state );
```

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

### Note

> Note : The input voltage frequency should be in the range from 50Hz to 250kHz.
> Also the input voltage amplitude must be lower than 5V.
> In this conditions the device can convert the RMS signal, in every form, to DC signal.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
