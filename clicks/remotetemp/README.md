
---
# Remote Temp Click

> [Remote Temp Click](https://www.mikroe.com/?pid_product=MIKROE-3685) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3685&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application reads remote temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RemoteTemp

### Example Key Functions

- `remotetemp_cfg_setup` Config Object Initialization function. 
```c
void remotetemp_cfg_setup ( remotetemp_cfg_t *cfg );
``` 
 
- `remotetemp_init` Initialization function. 
```c
err_t remotetemp_init ( remotetemp_t *ctx, remotetemp_cfg_t *cfg );
```

- `remotetemp_default_cfg` Click Default Configuration function. 
```c
void remotetemp_default_cfg ( remotetemp_t *ctx );
```

- `remotetemp_int_get` Getting state of INT pin. 
```c
uint8_t remotetemp_int_get ( remotetemp_t *ctx );
```

- `remotetemp_an_get` Getting state of AN pin. 
```c
uint8_t remotetemp_an_get ( remotetemp_t *ctx );
```

- `remotetemp_set_range` Setting temperature range. 
```c
uint8_t remotetemp_set_range ( remotetemp_t *ctx, uint8_t range_setting );
```

### Application Init

> Initializes I2C driver, sets range, configures device and sets threshold values.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    remotetemp_cfg_t cfg;

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

    remotetemp_cfg_setup( &cfg );
    REMOTETEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    remotetemp_init( &remotetemp, &cfg );
    Delay_ms ( 300 );
    remotetemp_set_range( &remotetemp, REMOTETEMP_RANGE_0_127 );
    remotetemp_default_cfg( &remotetemp );
    log_printf( &logger, "> app init done \r\n" );
}
```

### Application Task

> Executes all 'remotetemp_aux_getXxx()' functions.

```c
void application_task ( void )
{
    remotetemp_aux_get_fault( &remotetemp );
    remotetemp_aux_get_high_limit_status( &remotetemp );
    remotetemp_aux_get_low_limit_status( &remotetemp );
    remotetemp_aux_get_therm_limit_status( &remotetemp );
    remotetemp_aux_get_hottest_status( &remotetemp );
    Delay_ms ( 500 );
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
