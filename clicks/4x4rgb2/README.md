
---
# 4x4 RGB 2 Click

> [4x4 RGB 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5661) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5661&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of 4x4 RGB 2 Click board by setting all 16 LEDs to different colors and changing the LEDs color every 500 milliseconds. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4RGB2

### Example Key Functions

- `c4x4rgb2_cfg_setup` Config Object Initialization function.
```c
void c4x4rgb2_cfg_setup ( c4x4rgb2_cfg_t *cfg );
```

- `c4x4rgb2_init` Initialization function.
```c
err_t c4x4rgb2_init ( c4x4rgb2_t *ctx, c4x4rgb2_cfg_t *cfg );
```

- `c4x4rgb2_default_cfg` Click Default Configuration function.
```c
err_t c4x4rgb2_default_cfg ( c4x4rgb2_t *ctx );
```

- `c4x4rgb2_set_led_color` This function sets the color of the selected led in the led matrix.
```c
void c4x4rgb2_set_led_color ( c4x4rgb2_t *ctx, uint8_t led_num, uint32_t rgb );
```

- `c4x4rgb2_set_led_brightness` This function sets the brightness of the selected led in the led matrix.
```c
void c4x4rgb2_set_led_brightness ( c4x4rgb2_t *ctx, uint8_t led_num, uint8_t brightness );
```

- `c4x4rgb2_write_led_matrix` This function writes the led matrix data from the Click context object.
```c
err_t c4x4rgb2_write_led_matrix ( c4x4rgb2_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the LEDs brightness to level 1 and the color to black (all LEDs off).

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4x4rgb2_cfg_t c4x4rgb2_cfg;  /**< Click config object. */

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
    c4x4rgb2_cfg_setup( &c4x4rgb2_cfg );
    C4X4RGB2_MAP_MIKROBUS( c4x4rgb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c4x4rgb2_init( &c4x4rgb2, &c4x4rgb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C4X4RGB2_ERROR == c4x4rgb2_default_cfg ( &c4x4rgb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets all 16 LEDs to a different colors and changes their color every 500 milliseconds. All data is displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t color_num = 0;
    for ( uint8_t led_cnt = C4X4RGB2_LED_0; led_cnt <= C4X4RGB2_LED_15; led_cnt++ )
    {
        c4x4rgb2_set_led_color ( &c4x4rgb2, led_cnt, 
                                 color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].rgb );
        log_printf( &logger, " LED %u Color: %s - %.6LX\r\n", ( uint16_t ) led_cnt, 
                    color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].name, 
                    color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].rgb );
    }
    if ( C4X4RGB2_OK == c4x4rgb2_write_led_matrix ( &c4x4rgb2 ) )
    {
        log_printf( &logger, " Write LED Matrix\r\n\n" );
        Delay_ms ( 500 );
    }
    if ( ++color_num >= C4X4RGB2_NUM_COLORS )
    {
        color_num = 0;
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
