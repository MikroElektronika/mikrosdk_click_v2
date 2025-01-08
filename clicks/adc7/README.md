
---
# ADC 7 Click

> [ADC 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3115) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3115&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This example performs the reads of the converted voltage value.
> Results will be logged on uart terminal. Repeats operation every 200ms.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC7

### Example Key Functions

- `adc7_cfg_setup` Config Object Initialization function. 
```c
void adc7_cfg_setup ( adc7_cfg_t *cfg );
``` 
 
- `adc7_init` Initialization function. 
```c
err_t adc7_init ( adc7_t *ctx, adc7_cfg_t *cfg );
```

- `adc7_default_cfg` Click Default Configuration function. 
```c
void adc7_default_cfg ( adc7_t *ctx );
```

- `adc7_set_config` Function performs the device configuration by sending configuration data . 
```c
uint8_t adc7_set_config ( adc7_t* ctx, uint8_t gain_config, uint8_t down_samp_factor, uint8_t filter_type );
```
 
- `adc7_start_conv_cycle` Function generates clock signal on MCK pin and on that way starts conversion. 
```c
void adc7_start_conv_cycle ( adc7_t* ctx );
```

- `adc7_read_results` Function reads voltage value from AD converter and calculates this value to mV. 
```c
uint8_t adc7_read_results ( adc7_t* ctx, float* voltage );
```

### Application Init

> Initializes driver and performs configuration for conversion cycles.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    adc7_cfg_t cfg;

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

    adc7_cfg_setup( &cfg );
    ADC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc7_init( &adc7, &cfg );
    
    adc7_default_cfg( &adc7 );
}
```

### Application Task

> Performs the determined number of conversion cycles which are necessary for averaging.
> When all conversion cycles are done, it reads the converted voltage value.
> Results will be logged on UART terminal every second.

```c
void application_task ( void )
{
    adc7_start_conv_cycle( &adc7 );
    adc7_read_results( &adc7, &voltage_data );
    log_printf( &logger, "Voltage: %.2f mV\r\n", voltage_data );

    Delay_ms ( 1000 );
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
