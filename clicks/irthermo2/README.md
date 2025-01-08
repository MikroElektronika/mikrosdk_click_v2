
---
# IrThermo 2 Click

> [IrThermo 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1888) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1888&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> IrThermo 2 is a non-contact temperature measurement Click. The sensor absorbs the infrared 
> radiation emitted by the target object (withing the sensor’s field of view) and 
> the integrated math engine calculates its temperature by comparing it with the temperature 
> of the silicon die. The measurement range of the sensor is between –40°C to 125°C.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IrThermo2

### Example Key Functions

- `irthermo2_cfg_setup` Config Object Initialization function.
```c
void irthermo2_cfg_setup ( irthermo2_cfg_t *cfg ); 
```

- `irthermo2_init` Initialization function.
```c
err_t irthermo2_init ( irthermo2_t *ctx, irthermo2_cfg_t *cfg );
```
- `irthermo2_default_cfg` Click Default Configuration function.
``` c
void irthermo2_default_cfg ( irthermo2_t *ctx );
```

- `irthermo2_get_raw_temperature` Function read 16-bit data from raw temperature register and calculate temperature in degrees Celsius.
```c
float irthermo2_get_raw_temperature ( irthermo2_t *ctx );
```

- `irthermo2_get_object_temperature_c` Function read 16-bit data from object temperature register and calculate temperature in degrees Celsius.
```c
float irthermo2_get_object_temperature_c ( irthermo2_t *ctx );
```

- `irthermo2_get_object_temperature_f` Function read 16-bit data from object temperature register and calculate temperature in degrees Fahrenheit.
```c
float irthermo2_get_object_temperature_f ( irthermo2_t *ctx );
```

### Application Init

> Initialization driver enable's - I2C, set default configuration and start write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo2_cfg_t cfg;

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

    irthermo2_cfg_setup( &cfg );
    IRTHERMO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo2_init( &irthermo2, &cfg );

    irthermo2_default_cfg( &irthermo2 );
    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of IrThermo 2 Click board.
> Measures the object temperature value from sensor and calculate temperature in degrees Celsius [ C ].
> Results are being sent to the USART Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 5 sec when the data value changes.

```c
void application_task ( void )
{
    temperature = irthermo2_get_object_temperature_c( &irthermo2 );

    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
