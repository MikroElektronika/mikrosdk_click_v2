
---
# BARGRAPH 3 Click

> [BARGRAPH 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3264) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3264&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> Used to create various types of VU meters, status indicators, different types of counters and similar devices.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph3

### Example Key Functions

- `bargraph3_cfg_setup` Config Object Initialization function. 
```c
void bargraph3_cfg_setup ( bargraph3_cfg_t *cfg );
``` 
 
- `bargraph3_init` Initialization function. 
```c
err_t bargraph3_init ( bargraph3_t *ctx, bargraph3_cfg_t *cfg );
```

- `bargraph3_display ` This function control the displey. 
```c
void bargraph3_display  ( bargraph3_t *ctx, uint8_t ctrl, uint8_t dir, uint8_t counter );
```
 
- `bargraph3_set_pwm` This function set PWM. 
```c
void bargraph3_set_pwm ( bargraph3_t *ctx, uint8_t state );
```

- `bargraph3_enable` Functions for enable the chip. 
```c
void bargraph3_enable ( bargraph3_t *ctx, uint8_t state );
```

### Application Init

> Initialization driver init, enable device and set PWM.

```c
void application_init ( void )
{
 log_cfg_t log_cfg;
    bargraph3_cfg_t cfg;

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

    bargraph3_cfg_setup( &cfg );
    BARGRAPH3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph3_init( &bargraph3, &cfg );
}
```

### Application Task

> Counter passes through the loop and logs the value of the counter on the bargraph display.

```c
void application_task ( void )
{
    uint8_t bargraph_cnt;
    
    for (bargraph_cnt = 0; bargraph_cnt <= 5; bargraph_cnt++)
    {
        bargraph3_display(  &bargraph3, BARGRAPH3_INCREASE_LED,  BARGRAPH3_DIRECTION_BOTTOM_TO_TOP, bargraph_cnt);
        Delay_ms ( 1000 );
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
