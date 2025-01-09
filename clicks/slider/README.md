
---
# Slider Click

> [Slider Click](https://www.mikroe.com/?pid_product=MIKROE-2702) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2702&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example detect even the smallest move, faithfully capturing the smoothness of the slider movement, while digitizing its position. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Slider

### Example Key Functions

- `slider_cfg_setup` Config Object Initialization function. 
```c
void slider_cfg_setup ( slider_cfg_t *cfg );
``` 
 
- `slider_init` Initialization function. 
```c
err_t slider_init ( slider_t *ctx, slider_cfg_t *cfg );
```

- `slider_default_cfg` Click Default Configuration function. 
```c
void slider_default_cfg ( slider_t *ctx );
```

- `slider_read_adc_and_ready` Function calls slider_readADC function, but first checks is ADC conversion finished. 
```c
uint32_t slider_read_adc_and_ready ( slider_t *ctx );
```
 
- `slider_enable_led_output` Function enables LED output to shows output laches when state is low, and disables LED output when state is high. 
```c
void slider_enable_led_output ( slider_t *ctx, uint8_t state );
```

- `slider_enable_output_laches` Function enables output laches to monitor converted ADC value, when state is high. 
```c
void slider_enable_output_laches ( slider_t *ctx, uint8_t state );
```

### Application Init

> Initializes Click driver

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    slider_cfg_t cfg;

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

    slider_cfg_setup( &cfg );
    SLIDER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    slider_init( &slider, &cfg );
    slider_default_cfg( &slider );
}
```

### Application Task

> Converts analog input voltage (VCC), witch value depends on the slider position, to digital output value, shows result of conversion on LED and logs result on USB UART. 

```c
void application_task ( void )
{
    adc_value = slider_write_output( &slider );
    log_printf( &logger, "%.0f\r\n", adc_value );
}
```

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
