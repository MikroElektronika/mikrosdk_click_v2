
---
# Color 8 Click

> [Color 8 Click](https://www.mikroe.com/?pid_product=MIKROE-3213) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3213&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo app reads RED, GREEEN, BLUE, IR data and return detect color.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Color8

### Example Key Functions

- `color8_cfg_setup` Config Object Initialization function. 
```c
void color8_cfg_setup ( color8_cfg_t *cfg );
``` 
 
- `color8_init` Initialization function. 
```c
err_t color8_init ( color8_t *ctx, color8_cfg_t *cfg );
```

- `color8_read_data` This function reads data from register. 
```c
uint16_t color8_read_data ( color8_t *ctx, uint8_t reg_data );
```
 
- `color8_get_color_value` This functions reads 3 color filters and Clear Filters and converts the resulting color from RGB to HSL. 
```c
float color8_get_color_value ( color8_t *ctx );
```

- `color8_get_color` This function detect colors. 
```c
uint8_t color8_get_color ( color8_t *ctx, float color_value );
```

### Application Init

> Initialization device device configuration for start measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    color8_cfg_t cfg;

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

    color8_cfg_setup( &cfg );
    COLOR8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    color8_init( &color8, &cfg );

    color8_default_cfg( &color8 );
    log_printf( &logger, "---- Start measurement ----\r\n");
}
```

### Application Task

> Reads RED, GREEEN, BLUE and IR data. 
> Converts data to HSL value and return detect color.

```c
void application_task ( void )
{
    uint16_t red_data;
    uint16_t green_data;
    uint16_t blue_data;
    uint16_t ir_data;
    uint8_t is_color;
    float color_value;
    
    red_data = color8_read_data( &color8, COLOR8_REG_RED_DATA );
    log_printf( &logger, " RED data : %d \r\n", red_data );

    green_data = color8_read_data( &color8, COLOR8_REG_GREEN_DATA );
    log_printf( &logger, " GREEN data : %d \r\n", green_data );

    blue_data = color8_read_data( &color8, COLOR8_REG_BLUE_DATA );
    log_printf( &logger, " BLUE data : %d \r\n", blue_data );

    ir_data = color8_read_data( &color8, COLOR8_REG_IR_DATA );
    log_printf( &logger, " IR data : %d \r\n", ir_data );

    color_value = color8_get_color_value( &color8 );
    log_printf( &logger, " HSL color value : %f \r\n", color_value );

    is_color = color8_get_color( &color8, color_value );
    switch( is_color )
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
        default:
        {
            break;
        }
    }
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
