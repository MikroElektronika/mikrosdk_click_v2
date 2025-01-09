
---
# Color Click

> [Color Click](https://www.mikroe.com/?pid_product=MIKROE-1438) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1438&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> The following code demonstrates color detection/recognition functionality of the Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color

### Example Key Functions

- `color_cfg_setup` Config Object Initialization function. 
```c
void color_cfg_setup ( color_cfg_t *cfg );
``` 
 
- `color_init` Initialization function. 
```c
err_t color_init ( color_t *ctx, color_cfg_t *cfg );
```

- `color_default_cfg` Click Default Configuration function. 
```c
void color_default_cfg ( color_t *ctx );
```

- `color_read_color_ratio` This function reads desired color ratio from register. 
```c
float color_read_color_ratio ( color_t *ctx, uint8_t color );
```

- `color_get_color_value` This function reads 3 color filters and clear filters and converts the resulting color from RGBC to HSL. 
```c
float color_get_color_value ( color_t *ctx );
```

- `color_get_color` This function determines which color is read by Click sensor function has been invoked previously. 
```c
uint8_t color_get_color ( float color_value );
```

### Application Init

> Initializes device and driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color_cfg_t cfg;

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

    color_cfg_setup( &cfg );
    COLOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color_init( &color, &cfg );
    color_default_cfg( &color );
    is_color = 0;
}
```

### Application Task

> Checks which color is detected by the sensor.
The name of the detected color is logged on the USBUART.

```c
void application_task ( void )
{
    color_value = color_get_color_value( &color );
    is_color = color_get_color( color_value );

    switch( is_color )
    {
        case ORANGE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: ORANGE\r\n" );
            break;
        }
        case RED_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: RED\r\n" );
            break;
        }
        case PINK_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PINK\r\n" );
            break;
        }
        case PURPLE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: PURPLE\r\n" );
            break;
        }
        case BLUE_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: BLUE\r\n" );
            break;
        }
        case CYAN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: CYAN\r\n" );
            break;
        }
        case GREEN_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: GREEN\r\n" );
            break;
        }
        case YELLOW_COLOR_FLAG:
        {
            log_printf( &logger, "--- Color: YELLOW\r\n" );
            break;
        }
        default:
        {
            break;
        }
    }

    Delay_ms ( 300 );
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
