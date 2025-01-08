
---
# FAN 4 Click

> [FAN 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3200) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3200&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : nov 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application shows basic use of Fan 4 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan4

### Example Key Functions

- `fan4_cfg_setup` Config Object Initialization function. 
```c
void fan4_cfg_setup ( fan4_cfg_t *cfg );
``` 
 
- `fan4_init` Initialization function. 
```c
err_t fan4_init ( fan4_t *ctx, fan4_cfg_t *cfg );
```

- `fan4_default_cfg` Click Default Configuration function. 
```c
void fan4_default_cfg ( fan4_t *ctx );
```

- `fan4_check_diagnostic` Check diagnostic. 
```c
uint8_t fan4_check_diagnostic ( fan4_t *ctx );
```
 
- Set output voltage
err_t fan4_set_output ( fan4_t *ctx, uint16_t output_volt, uint8_t boost_start_timer );

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fan4_cfg_t cfg;

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

    fan4_cfg_setup( &cfg );
    FAN4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan4_init( &fan4, &cfg );

    fan4_default_cfg( &fan4 );
}
```

### Application Task

> Increases the output voltage every 500 ms until it reaches the maximum fan voltage.
> Prints current voltase data on usbuart.

```c
void application_task ( void )
{
    uint16_t voltage;

    //  Task implementation.

    voltage = FAN4_MIN_VOLT_SCALE;

    while ( voltage <= FAN4_MAX_VOLT_SCALE )
    {
        voltage += ( FAN4_DAC_LSB * 4 );
        log_info( &logger, "** Voltage is %d mV", voltage );

        fan4_set_output( &fan4, voltage, FAN4_BOOST_START_TIMER_DIS );
        Delay_ms ( 500 );
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
