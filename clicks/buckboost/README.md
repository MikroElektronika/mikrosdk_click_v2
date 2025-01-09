
---
# Buck-Boost  Click

> [Buck-Boost Click](https://www.mikroe.com/?pid_product=MIKROE-2806) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2806&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> The demo application change output voltage from 2500 mV to 15000 mV every 5 seconds.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost

### Example Key Functions

- `buckboost_cfg_setup` Config Object Initialization function. 
```c
void buckboost_cfg_setup ( buckboost_cfg_t *cfg );
``` 
 
- `buckboost_init` Initialization function. 
```c
err_t buckboost_init ( buckboost_t *ctx, buckboost_cfg_t *cfg );
```

- `buckboost_default_cfg` Click Default Configuration function. 
```c
void buckboost_default_cfg ( buckboost_t *ctx );
```

- `buckboost_set_mode_fixed_freq` This function set fixed frequency PWM operation mode of LTC3129-1 on Buck Boost Click by set PWM pin ( logic 1 ). 
```c
void buckboost_set_mode_fixed_freq ( buckboost_t *ctx );
```
 
- `buckboost_enables_auto_burst_mode` This function enables automatic burst mode operation of LTC3129-1 on Buck Boost Click by clear PWM pin ( logic 0 ). 
```c
void buckboost_enables_auto_burst_mode ( buckboost_t *ctx );
```

- `buckboost_set_2500mv` This function set the output voltage of 2500 mV function. 
```c
void buckboost_set_2500mv ( buckboost_t *ctx );
```

### Application Init

> Initialization device and set default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    buckboost_cfg_setup( &cfg );
    BUCKBOOST_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost_init( &buckboost, &cfg );

    buckboost_default_cfg( &buckboost );
    log_printf(&logger, "--------------------------------\r\n");
    log_printf(&logger, "        Buck Boost Click        \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    Delay_ms ( 100 );
}
```

### Application Task

> This is a example which demonstrates the use of Buck Boost Click board.
> Change output voltage from 2500 mV to 15000 mV every 5 seconds.
> All data logs write on usb uart for aproximetly every 5 sec.

```c
void application_task ( void )
{
    log_printf(&logger, " Set Output Voltage of  2500 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_2500mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  3300 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_3300mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  4100 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_4100mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  5000 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_5000mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  6900 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_6900mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  8200 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_8200mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  12000 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_12000mv( &buckboost );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf(&logger, " Set Output Voltage of  15000 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_15000mv( &buckboost );
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
