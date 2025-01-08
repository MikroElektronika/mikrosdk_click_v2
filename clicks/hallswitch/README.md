
---
# Hall Switch Click

> [Hall Switch Click](https://www.mikroe.com/?pid_product=MIKROE-2985) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2985&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type

# Software Support

## Example Description

> The application sets sensor magnetic pole

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallSwitch

### Example Key Functions

- `hallswitch_cfg_setup` Config Object Initialization function. 
```c
void hallswitch_cfg_setup ( hallswitch_cfg_t *cfg );
``` 
 
- `hallswitch_init` Initialization function. 
```c
err_t hallswitch_init ( hallswitch_t *ctx, hallswitch_cfg_t *cfg );
```

- `hallswitch_default_cfg` Click Default Configuration function. 
```c
void hallswitch_default_cfg ( hallswitch_t *ctx );
```

- `hallswitch_set_npole` Function for turn on and turn off N Pole. 
```c
void hallswitch_set_npole ( hallswitch_t *ctx, uint8_t state );
```
 
- `hallswitch_set_spole ` Function for turn on and turn off S Pole. 
```c
void hallswitch_set_spole  ( hallswitch_t *ctx,uint8_t state );
```

### Application Init

> Initializes Driver init and turn OFF S pole and N pole

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hallswitch_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    hallswitch_cfg_setup( &cfg );
    HALLSWITCH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallswitch_init( &hallswitch, &cfg );

    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
}
```

### Application Task

>  Turns S and N on and off every 500 msInitializes Driver init and turn OFF S pole and N pole

```c
void application_task()
{
    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_ACTIVE );
    Delay_ms ( 500 );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_ACTIVE );
    Delay_ms ( 500 );
    hallswitch_set_npole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
    Delay_ms ( 500 );
    hallswitch_set_spole( &hallswitch, HALLSWITCH_POLE_NO_ACTIVE );
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
