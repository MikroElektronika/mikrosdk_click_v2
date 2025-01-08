
---
# Thermo 15 Click

> [Thermo 15 Click](https://www.mikroe.com/?pid_product=MIKROE-3658) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3658&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo-app shows the temperature measurement procedure using Thermo 15 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo15

### Example Key Functions

- `thermo15_cfg_setup` Config Object Initialization function. 
```c
void thermo15_cfg_setup ( thermo15_cfg_t *cfg );
``` 
 
- `thermo15_init` Initialization function. 
```c
err_t thermo15_init ( thermo15_t *ctx, thermo15_cfg_t *cfg );
```

- `thermo15_default_cfg` Click Default Configuration function. 
```c
void thermo15_default_cfg ( thermo15_t *ctx );
```

- `thermo15_get_temperature_data` Ambient temperature data. 
```c
float thermo15_get_temperature_data ( thermo15_t *ctx,  uint8_t temp_format );
```
 
- `thermo15_set_temp_register` Set temperature register. 
```c
void thermo15_set_temp_register ( thermo15_t *ctx, uint8_t temp_reg, float temp_data );
```

- `thermo15_get_interrupt_state` Interrupt state. 
```c
uint8_t thermo15_get_interrupt_state ( thermo15_t *ctx );
```

### Application Init

> Configuring Clicks and log objects. 
> Setting the Click in the default configuration to start the measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo15_cfg_t cfg;

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

    thermo15_cfg_setup( &cfg );
    THERMO15_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo15_init( &thermo15, &cfg );

    thermo15_default_cfg ( &thermo15 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads ambient temperature data and this data logs to USBUART every 1500ms.

```c
void application_task ( void )
{
    float temperature;

    temperature = thermo15_get_temperature_data( &thermo15, THERMO15_TEMP_IN_CELSIUS );
    log_printf( &logger, "** Temperature: %.2f C \r\n", temperature );

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
