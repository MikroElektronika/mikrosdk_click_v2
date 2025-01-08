
---
# Thermo 3 Click

> [Thermo 3 Click](https://www.mikroe.com/?pid_product=MIKROE-1885) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1885&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application read the temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo3

### Example Key Functions

- `thermo3_cfg_setup` Config Object Initialization function. 
```c
void thermo3_cfg_setup ( thermo3_cfg_t *cfg );
``` 
 
- `thermo3_init` Initialization function. 
```c
err_t thermo3_init ( thermo3_t *ctx, thermo3_cfg_t *cfg );
```

- `get_temperature` Gets temperature. 
```c
float get_temperature ( thermo3_t *ctx );
```

### Application Init

> Initialization driver enables - I2C.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo3_cfg_t cfg;

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

    thermo3_cfg_setup( &cfg );
    THERMO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo3_init( &thermo3, &cfg );
}
```

### Application Task

> This is an example which demonstrates the use of Thermo 3 Click board. Detects the temperature and write on usb uart changes for every 3 sec.

```c
void application_task ( void )
{
    float read_temp;

    read_temp = get_temperature( &thermo3 );

    log_printf( &logger, "Temperature: %.2f C\r\n", read_temp );
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
