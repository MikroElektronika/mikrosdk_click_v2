
---
# Pressure 12 Click

> [Pressure 12 Click](https://www.mikroe.com/?pid_product=MIKROE-3466) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3466&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> Reads ADC value, convert ADC data to Voltage[ mV ] and pressure [ mBar ].

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure12

### Example Key Functions

- `pressure12_cfg_setup` Config Object Initialization function. 
```c
void pressure12_cfg_setup ( pressure12_cfg_t *cfg );
``` 
 
- `pressure12_init` Initialization function. 
```c
err_t pressure12_init ( pressure12_t *ctx, pressure12_cfg_t *cfg );
```

- `pressure12_default_cfg` Click Default Configuration function. 
```c
void pressure12_default_cfg ( pressure12_t *ctx );
```

- `pressure12_get_pressure` Get pressure function. 
```c
float pressure12_get_pressure ( pressure12_t *ctx );
```
 
- `pressure12_get_voltage` Get voltage function. 
```c
float pressure12_get_voltage ( pressure12_t *ctx );
```

- `pressure12_set_adc_resolution` Set ADC resolution function. 
```c
void pressure12_set_adc_resolution ( pressure12_t *ctx, float adc_res );
```

### Application Init

> Initializes ADC and LOG for logging data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure12_cfg_t cfg;

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

    pressure12_cfg_setup( &cfg );
    PRESSURE12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( pressure12_init( &pressure12, &cfg ) == ADC_ERROR )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );

        for ( ; ; );
    }
    log_info( &logger, "---- Application Init Done ----\r\n" );

    pressure_val = 0;
    voltage_val = 0;
}
```

### Application Task

> Reads ADC value, convert ADC data to Voltage[ mV ] on the AN pin and
> convert to Pressure data in mBar. All data logs to the USBUART each second.

```c
void application_task ( void )
{
    if ( pressure12_read_pin_voltage( &pressure12, &voltage_val ) != ADC_ERROR )
    {
        log_printf( &logger, " Voltage [V] : %.2f\r\n", voltage_val );
    }

    if ( pressure12_get_pressure( &pressure12, &pressure_val ) != ADC_ERROR )
    {
        log_printf( &logger, " Pressure [mBar] : %u\r\n", pressure_val );
    }

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

### Note

> Output is proportional to the difference between applied pressure and atmospheric (ambient) pressure.

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
