
---
# AC Current Click

> [AC Current Click](https://www.mikroe.com/?pid_product=MIKROE-2523) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2523&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This application measures AC current through a conductor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AcCurrent

### Example Key Functions

- `accurrent_cfg_setup` Config Object Initialization function.
```c
void accurrent_cfg_setup ( accurrent_cfg_t *cfg );
```
 
- `accurrent_init` Initialization function.
```c
err_t accurrent_init ( accurrent_t *ctx, accurrent_cfg_t *cfg );
```

- `accurrent_get_a` Gets current value of AC Current in A.
```c
float accurrent_get_a ( accurrent_t *ctx );
```
 
- `accurrent_get_ma` Gets current value of AC Current in mA.
```c
float accurrent_get_ma ( accurrent_t *ctx );
```

### Application Init

> SPI driver and slick initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    accurrent_cfg_t cfg;

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

    accurrent_cfg_setup( &cfg );
    ACCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accurrent_init( &accurrent, &cfg );
}
```

### Application Task

> Reads the value of AC current and displays it on the USB UART.

```c
void application_task ( void )
{
    float ac_current = 0;
    ac_current = accurrent_get_ma( &accurrent );
    log_printf( &logger, "Current value: %.3f mA\r\n", ac_current );
    Delay_ms ( 1000 );
}
```

### Note
> An appropriate AC Current sensor needs to be connected to the Click board.

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
