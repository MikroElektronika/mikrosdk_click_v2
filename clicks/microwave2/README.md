
---
# Microwave 2 Click

> [Microwave 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3187) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3187&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This application is an accurate and reliable short to medium range motion detection.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Microwave2

### Example Key Functions

- `microwave2_cfg_setup` Config Object Initialization function. 
```c
void microwave2_cfg_setup ( microwave2_cfg_t *cfg );
``` 
 
- `microwave2_init` Initialization function. 
```c
err_t microwave2_init ( microwave2_t *ctx, microwave2_cfg_t *cfg );
```

- `microwave2_dl_state` Set pin DL . 
```c
uint8_t microwave2_dl_state ( microwave2_t *ctx );
```
 
- `microwave2_da_state` Set pin DA. 
```c
uint8_t microwave2_da_state ( microwave2_t *ctx );
```

### Application Init

> Initializes the Click board for communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    microwave2_cfg_t cfg;

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

    microwave2_cfg_setup( &cfg );
    MICROWAVE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    microwave2_init( &microwave2, &cfg );
}
```

### Application Task

> Data sent from the Click board is captured and different actions are applied.

```c
void application_task ( void )
{
    microwave2_process();
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
