
---
# Color 7 Click

> [Color 7 Click](https://www.mikroe.com/?pid_product=MIKROE-3062) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3062&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> Demo application reads and detects colors - detected color logs on USBUART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color7

### Example Key Functions

- `color7_cfg_setup` Config Object Initialization function. 
```c
void color7_cfg_setup ( color7_cfg_t *cfg );
``` 
 
- `color7_init` Initialization function. 
```c
err_t color7_init ( color7_t *ctx, color7_cfg_t *cfg );
```

- `color7_default_cfg` Click Default Configuration function. 
```c
void color7_default_cfg ( color7_t *ctx );
```

- `color7_get_color` Functions for detect colors. 
```c
uint8_t color7_get_color ( color7_t *ctx );
```
 
- `color7_get_interrupt_state` Get interrut pin state. 
```c
uint8_t color7_get_interrupt_state( color7_t *ctx );
```

- `color7_read_color_ratio` Functions for read color ratio. 
```c
float color7_read_color_ratio( color7_t *ctx, uint8_t color );
```

### Application Init

> Configuring Clicks and log objects.
> Settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color7_cfg_t cfg;

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

    color7_cfg_setup( &cfg );
    COLOR7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color7_init( &color7, &cfg );

    color7_default_cfg( &color7 );
    log_info( &logger, "---- Start measurement ----" );
}
```

### Application Task

> Reads light color and checks which color of light is detected by the sensor
> If the light color is detected, the detected color message is logged on the USBUART.

```c
void application_task ( void )
{
    uint8_t color;

    //  Task implementation.

    color = color7_get_color( &color7 );

    switch( color )
    {
        case 1:
        {
            log_printf( &logger, "--- Color: ORANGE \r\n" );
            break;
        }
        case 2:
        {
            log_printf( &logger, "--- Color: RED \r\n" );
            break;
        }
        case 3:
        {
            log_printf( &logger, "--- Color: PINK \r\n" );
            break;
        }
        case 4:
        {
            log_printf( &logger, "--- Color: PURPLE \r\n" );
            break;
        }
        case 5:
        {
            log_printf( &logger, "--- Color: BLUE \r\n" );
            break;
        }
        case 6:
        {
            log_printf( &logger, "--- Color: CYAN \r\n" );
            break;
        }
        case 7:
        {
            log_printf( &logger, "--- Color: GREEN \r\n" );
            break;
        }
        case 8:
        {
            log_printf( &logger, "--- Color: YELLOW \r\n" );
            break;
        }
    }
    Delay_100ms();
}
```

### Note

> Light source must be pointed towards sensor in order for sensor to 
> detect light source color correctly.
> We used the HSL color palette on the monitor as an example.

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
