
---
# 1x4 RGB Click

> [1x4 RGB Click](https://www.mikroe.com/?pid_product=MIKROE-6240) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6240&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the 1x4 RGB Click board
> by controlling the color of the LEDs [LD1-LD4].

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.1x4RGB

### Example Key Functions

- `c1x4rgb_cfg_setup` Config Object Initialization function.
```c
void c1x4rgb_cfg_setup ( c1x4rgb_cfg_t *cfg );
```

- `c1x4rgb_init` Initialization function.
```c
err_t c1x4rgb_init ( c1x4rgb_t *ctx, c1x4rgb_cfg_t *cfg );
```

- `c1x4rgb_default_cfg` Click Default Configuration function.
```c
err_t c1x4rgb_default_cfg ( c1x4rgb_t *ctx );
```

- `c1x4rgb_set_rgb_color` This function sets the desired values of RGB colors for the selected LED by using the I2C serial interface.
```c
err_t c1x4rgb_set_rgb_color ( c1x4rgb_t *ctx, uint8_t led_pos, uint8_t red, uint8_t green, uint8_t blue );
```

- `c1x4rgb_enable_leds` This function turns on the desired LEDs by using the I2C serial interface.
```c
err_t c1x4rgb_enable_leds ( c1x4rgb_t *ctx, uint16_t led_bitmask );
```

- `c1x4rgb_set_tmc_mode` This function configures the desired LED drive mode as TCM 1/2/3/4 scans using the I2C serial interface.
```c
err_t c1x4rgb_set_tmc_mode ( c1x4rgb_t *ctx, uint8_t dev_cfg, uint8_t mode );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c1x4rgb_cfg_t c1x4rgb_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    c1x4rgb_cfg_setup( &c1x4rgb_cfg );
    C1X4RGB_MAP_MIKROBUS( c1x4rgb_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == c1x4rgb_init( &c1x4rgb, &c1x4rgb_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C1X4RGB_ERROR == c1x4rgb_default_cfg ( &c1x4rgb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
}
```

### Application Task

> The demo example shows the color change of four RGB LEDs, 
> starting with red color, through green and blue, and ending with white.
> These LEDs actually consist of three single-colored LEDs 
> (Red-Green-Blue) in a single package. 
> Various colors can be reproduced by mixing the intensity of each LED.

```c
void application_task ( void ) 
{
    log_printf( &logger, "\r\n\n RED: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_0 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n GREEN: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_0 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n BLUE: " );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_0, 
                                                                     DEMO_COLOR_INT_100 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
    }

    log_printf( &logger, "\r\n WHITE:" );
    for ( uint8_t led_pos = C1X4RGB_LED_POS_LD1; led_pos <= C1X4RGB_LED_POS_LD4; led_pos++ )
    {
        if ( C1X4RGB_OK == c1x4rgb_set_rgb_color( &c1x4rgb, led_pos, DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_100, 
                                                                     DEMO_COLOR_INT_100 ) )
        {
            log_printf( &logger, " LD%d ", ( uint16_t ) led_pos );
            Delay_ms ( 100 );
        }
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
