
---
# PowerBank 2 Click

> [PowerBank 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4116) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4116&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This single chip includes a linear charger, a synchronous Boost with dual output load management and a torch function support. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Powerbank2

### Example Key Functions

- `powerbank2_cfg_setup` Config Object Initialization function. 
```c
void powerbank2_cfg_setup ( powerbank2_cfg_t *cfg );
``` 
 
- `powerbank2_init` Initialization function. 
```c
err_t powerbank2_init ( powerbank2_t *ctx, powerbank2_cfg_t *cfg );
```

- `powerbank2_read` Read function. 
```c
void powerbank2_read ( powerbank2_t *ctx, uint16_t *result );
```
 
- `powerbank2_read_voltage` Read voltage function. 
```c
uint16_t powerbank2_read_voltage ( powerbank2_t *ctx, uint16_t v_ref );
```

### Application Init

> Initalizes I2C driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    powerbank2_cfg_t cfg;

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

    powerbank2_cfg_setup( &cfg );
    POWERBANK2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    powerbank2_init( &powerbank2, &cfg );
}
```

### Application Task

> This example shows the capabilities of the Power Bank 2 Click
> by measuring voltage of the connected battery. In order to get correct calculations 
> the user should change "v_ref" value to his own power supply voltage.

```c
void application_task ( void )
{
    voltage = powerbank2_read_voltage( &powerbank2, v_ref );

    log_printf( &logger, "Battery voltage: %u mV\r\n", voltage );

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
