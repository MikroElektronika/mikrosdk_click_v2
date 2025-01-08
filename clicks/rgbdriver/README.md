
---
# RGB Driver Click

> [RGB Driver Click](https://www.mikroe.com/?pid_product=MIKROE-3078) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3078&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This application sets the brightness over RGB value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RgbDriver

### Example Key Functions

- `rgbdriver_cfg_setup` Config Object Initialization function. 
```c
void rgbdriver_cfg_setup ( rgbdriver_cfg_t *cfg );
``` 
 
- `rgbdriver_init` Initialization function. 
```c
err_t rgbdriver_init ( rgbdriver_t *ctx, rgbdriver_cfg_t *cfg );
```

- `rgbdriver_default_cfg` Click Default Configuration function. 
```c
void rgbdriver_default_cfg ( rgbdriver_t *ctx );
```

- `rgbdriver_set_rgb_color` This function sets the color of the rgb LEDs through the parameters for red, green and blue. 
```c
void rgbdriver_set_rgb_color ( rgbdriver_t *ctx, uint8_t red, uint8_t green, uint8_t blue );
```
 
- `rgbdriver_set_color` This function sets the color. 
```c
void rgbdriver_set_color ( rgbdriver_t *ctx, uint32_t color );
```

- `rgbdriver_shut_down` This function shut down device. 
```c
void rgbdriver_shut_down ( rgbdriver_t *ctx );
```

### Application Init

> Initializes driver and logger, and configures the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    rgbdriver_cfg_t cfg;

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

    rgbdriver_cfg_setup( &cfg );
    RGBDRIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rgbdriver_init( &rgbdriver, &cfg );
    Delay_ms ( 1000 );
    
    rgbdriver_default_cfg( &rgbdriver );
    Delay_ms ( 100 );
}
```

### Application Task

> Changes the color of RGB LED tape connected to the Click board every 2 seconds.
> The name of the selected color will be displayed on USB UART.

```c
void application_task ( void )
{
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_RED_LOW_INTENSITY );
    log_printf( &logger, "\r\n--- RED ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_ORANGE_LOW_INTENSITY );
    log_printf( &logger, "--- ORANGE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_YELLOW_LOW_INTENSITY );
    log_printf( &logger, "--- YELLOW ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_GREEN_LOW_INTENSITY );
    log_printf( &logger, "--- GREEN ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_BLUE_LOW_INTENSITY );
    log_printf( &logger, "--- BLUE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_WHITE_LOW_INTENSITY );
    log_printf( &logger, "--- WHITE ---\r\n" );
    Delay_1sec( );
    Delay_1sec( );
    rgbdriver_set_color( &rgbdriver, RGBDRIVER_COLOR_PURPLE_LOW_INTENSITY );
    log_printf( &logger, "--- PURPLE ---\r\n" );
    Delay_1sec( );
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
