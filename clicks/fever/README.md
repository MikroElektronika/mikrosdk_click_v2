
---
# Fever Click

> [Fever Click](https://www.mikroe.com/?pid_product=MIKROE-2554) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2554&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Fever

### Example Key Functions

- `fever_cfg_setup` Config Object Initialization function. 
```c
void fever_cfg_setup ( fever_cfg_t *cfg );
``` 
 
- `fever_init` Initialization function. 
```c
err_t fever_init ( fever_t *ctx, fever_cfg_t *cfg );
```

- `fever_get_temperature` Get temperature. 
```c
float fever_get_temperature ( fever_t *ctx );
```

### Application Init

> Click device initialization

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fever_cfg_t cfg;

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

    fever_cfg_setup( &cfg );
    FEVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fever_init( &fever, &cfg );
}
```

### Application Task

> Reading and displaying current temperature via UART

```c
void application_task ( void )
{
    float temperature;
    temperature = fever_get_temperature( &fever );
    log_printf( &logger, "Current Temperature : %.2f C \r\n", temperature);
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
