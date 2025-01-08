
---
# LED Driver 3 Click

> [LED Driver 3 Click](https://www.mikroe.com/?pid_product=MIKROE-2950) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2950&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This app changes color and intensity of light.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LedDriver3

### Example Key Functions

- `leddriver3_cfg_setup` Config Object Initialization function. 
```c
void leddriver3_cfg_setup ( leddriver3_cfg_t *cfg );
``` 
 
- `leddriver3_init` Initialization function. 
```c
err_t leddriver3_init ( leddriver3_t *ctx, leddriver3_cfg_t *cfg );
```

- `leddriver3_default_cfg` Click Default Configuration function. 
```c
void leddriver3_default_cfg ( leddriver3_t *ctx );
```

- `leddriver3_set_rgb_color` This function sets the color of the rgb LEDs through the parameters for red, green and blue. 
```c
void leddriver3_set_rgb_color ( leddriver3_t *ctx, rgb_t *rgb );
```
 
- `leddriver3_set_color` This function sets color. 
```c
void leddriver3_set_color ( leddriver3_t *ctx, uint32_t color );
```

- `leddriver3_set_timer` This function sets timer for increase or decrease light. 
```c
void leddriver3_set_timer ( leddriver3_t *ctx, uint8_t time );
```

### Application Init

> Driver initialize.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver3_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    leddriver3_cfg_setup( &cfg );
    LEDDRIVER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver3_init( &leddriver3, &cfg );
}
```

### Application Task

> Changes color and intensity of light.

```c
void application_task ( void )
{
    rgb.red = 0x40;
    rgb.green = 0x7F;
    rgb.blue = 0x80;

    leddriver3_set_intensity( &leddriver3, LEDDRIVER3_INCREMENT | LEDDRIVER3_INTENSITY_8 );
    leddriver3_set_timer( &leddriver3, LEDDRIVER3_TIMER_8ms | LEDDRIVER3_TIMER_16ms );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_RED );
    Delay_1sec( );
    
    leddriver3_set_intensity( &leddriver3, LEDDRIVER3_CONSTANT | LEDDRIVER3_INTENSITY_16 );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_YELLOW );
    Delay_1sec( );
    leddriver3_set_color( &leddriver3, LEDDRIVER3_COLOR_BLUE );
    Delay_1sec( );

    leddriver3_set_rgb_color( &leddriver3, &rgb );
    Delay_1sec( );
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
