
---
# Thermo 8 Click

> [Thermo 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3290) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3290&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo8

### Example Key Functions

- `thermo8_cfg_setup` Config Object Initialization function. 
```c
void thermo8_cfg_setup ( thermo8_cfg_t *cfg );
``` 
 
- `thermo8_init` Initialization function. 
```c
err_t thermo8_init ( thermo8_t *ctx, thermo8_cfg_t *cfg );
```

- `thermo8_default_cfg` Click Default Configuration function. 
```c
void thermo8_default_cfg ( thermo8_t *ctx );
```

- `thermo8_get_temperature` This function returns the temperature value in �C. 
```c
float thermo8_get_temperature ( thermo8_t *ctx );
```
 
- `thermo8_set_resolution` This function sets the conversion resoult temperature step depending on the passed constant. 
```c
void thermo8_set_resolution ( thermo8_t *ctx, uint8_t r_cfg );
```

- `thermo8_limit_set` This function setting the temperature alarm levels for the lower, upper and critical alert levels. 
```c
void thermo8_limit_set ( thermo8_t *ctx, uint8_t limit_reg_addr, float limit );
```

### Application Init

> Initialize device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo8_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    thermo8_cfg_setup( &cfg );
    THERMO8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo8_init( &thermo8, &cfg );
    Delay_ms ( 100 );
    thermo8_default_cfg( &thermo8 );
}
```

### Application Task

> Wait for the interrupt pin to be triggered. When the
> measured temperature breaches the upper or lower limit the
> temperature value as well as the status of the breach is
> is shown on the serial port (UART).

```c
void application_task ( void )
{
    float t_data;
    char alert;
    char alert_on;

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    alert = thermo8_ale_get( &thermo8 );

    if ( alert == 0 )
    {
        t_data  = thermo8_get_temperature( &thermo8 );
        alert_on = thermo8_get_alert_stat( &thermo8 );
    }

    if ( alert_on & THERMO8_TLOWER_REACHED )
    {
        log_printf( &logger, "Temperature under the low limit: %.2f �C \r\n", t_data );
    }

    if ( alert_on & THERMO8_TUPPER_REACHED )
    {
        log_printf( &logger, "Temperature over the high limit: %.2f �C \r\n", t_data );
    }
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
