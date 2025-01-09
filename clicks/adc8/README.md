
---
# ADC 8 Click

> [ADC 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3394) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3394&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The demo app shows voltage measurement across all singles and different channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Adc8

### Example Key Functions

- `adc8_cfg_setup` Config Object Initialization function. 
```c
void adc8_cfg_setup ( adc8_cfg_t *cfg );
``` 
 
- `adc8_init` Initialization function. 
```c
err_t adc8_init ( adc8_t *ctx, adc8_cfg_t *cfg );
```

- `adc8_default_cfg` Click Default Configuration function. 
```c
void adc8_default_cfg ( adc8_t *ctx );
```

- `adc8_get_diff_channel` Get [Package] Diff channel voltage. 
```c
void adc8_get_diff_channel ( adc8_t *ctx, adc8_diff_volt_t *volt );
```
 
- `adc8_get_single_channel` Get [Package] Single channel voltage. 
```c
void adc8_get_single_channel ( adc8_t *ctx, adc8_single_volt_t *volt );
```

- `adc8_get_interrupt_state` Get interrupt pin state. 
```c
uint8_t adc8_get_interrupt_state ( adc8_t *ctx );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc8_cfg_t cfg;

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

    adc8_cfg_setup( &cfg );
    ADC8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc8_init( &adc8, &cfg );

    adc8_default_cfg( &adc8 );
    log_info( &logger, "---- ADC start ----" );
}
```

### Application Task

> Reads voltage from each channel one by one and the voltage difference 
> between specified channels.

```c
void application_task ( void )
{
    adc8_single_volt_t single_volt;
    adc8_diff_volt_t diff_volt;

    log_printf( &logger, "\r\n-----------------------------------" );

    // Single channel
    adc8_get_single_channel( &adc8, &single_volt );

    log_printf( &logger, "\r\n>>> SINGLE CHANNEL <<<<\r\n" );
    log_printf( &logger, "- CH 0: %.2f\r\n", single_volt.ch_0 );
    log_printf( &logger, "- CH 1: %.2f\r\n", single_volt.ch_1 );
    log_printf( &logger, "- CH 2: %.2f\r\n", single_volt.ch_2 );
    log_printf( &logger, "- CH 3: %.2f\r\n", single_volt.ch_3 );

    // Diff channel

    adc8_get_diff_channel( &adc8, &diff_volt );

    log_printf( &logger, "\r\n>>> DIFF CHANNEL <<<<\r\n" );
    log_printf( &logger, "- CH(0-1): %.2f\r\n", diff_volt.ch_0_1 );
    log_printf( &logger, "- CH(0-3): %.2f\r\n", diff_volt.ch_0_3 );
    log_printf( &logger, "- CH(1-3): %.2f\r\n", diff_volt.ch_1_3 );
    log_printf( &logger, "- CH(2-3): %.2f\r\n", diff_volt.ch_2_3 );

    Delay_ms ( 1000 );
}
```

### Note

> On the input channel AIN0, AIN1, AIN2 and AIN3 sets maximum voltage 
> GND - 0.3V < VIN > VDD + 0.3V

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
