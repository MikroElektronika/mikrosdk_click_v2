
---
# Matrix RGB Click

> [Matrix RGB Click](https://www.mikroe.com/?pid_product=MIKROE-2239) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2239&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application is used for powering 16x32 RGB LED matrices.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MatrixRGB

### Example Key Functions

- `matrixrgb_cfg_setup` Config Object Initialization function. 
```c
void matrixrgb_cfg_setup ( matrixrgb_cfg_t *cfg );
``` 
 
- `matrixrgb_init` Initialization function. 
```c
err_t matrixrgb_init ( matrixrgb_t *ctx, matrixrgb_cfg_t *cfg );
```

- `matrixrgb_pattern_settings` Click Pattern Settings ( Default Configuration ) function. 
```c
void matrixrgb_pattern_settings ( matrixrgb_t *ctx, uint8_t pattern_type, uint16_t pattern_delay_us );
```

- `matrixrgb_set_power` Set Power. 
```c
void matrixrgb_set_power ( matrixrgb_t *ctx, uint8_t power_state );
```
 
- `matrixrgb_set_brightness` Set Brightness. 
```c
void matrixrgb_set_brightness ( matrixrgb_t *ctx, uint8_t brightness );
```

- `matrixrgb_write_pixel` Write Pixel. 
```c
uint8_t matrixrgb_write_pixel ( matrixrgb_t *ctx, uint16_t x, uint16_t y, uint16_t color );
```

### Application Init

> Initializes driver, reset device and initializes
> firmware depend on pattern used alongside with fonts 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    matrixrgb_cfg_t cfg;
    matrixrgb_font_t font_cfg;

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

    matrixrgb_cfg_setup( &cfg );
    MATRIXRGB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    matrixrgb_init( &matrixrgb, &cfg );

    matrixrgb_device_reset( &matrixrgb );

    matrixrgb_pattern_settings ( &matrixrgb, MATRIXRGB_PATTERN_1_MAP_6MM, 1000 );
    matrixrgb_set_power( &matrixrgb, 1 );
    Delay_ms ( 1000 );
    
    font_cfg.p_font       = Arial9x9;
    font_cfg.color        = 0xFFFF;
    font_cfg.orientation  = MATRIXRGB_FONT_HORIZONTAL;
    
    matrixrgb_set_font ( &matrixrgb, &font_cfg );
    
    matrixrgb_fill_screen( &matrixrgb, 0xFFFF );
    Delay_ms ( 1000 );
}
```

### Application Task

> Test of panel brightnes, draws red cross on
> the panel using pixel write function, writes text on panel using
> write text function and finaly displays image on the panel.

```c
void application_task ( )
{
    uint16_t test;

    // Brightness Test
    for ( test = 5; test < 50; test++ )
    {
        matrixrgb_set_brightness( &matrixrgb, test );
        Delay_ms ( 50 );
    }

    for ( test = 50; test > 5; test-- )
    {
        matrixrgb_set_brightness( &matrixrgb, test );
        Delay_ms ( 50 );
    }

    // Pixel Write Test
    matrixrgb_fill_screen( &matrixrgb, 0x0000 );
    for ( test = 0; test < 32; test++ )
    {
        matrixrgb_write_pixel( &matrixrgb, test, test, 0xF100 );
        Delay_ms ( 100 );
    }
    for ( test = 32; test > 0; test-- )
    {
        matrixrgb_write_pixel( &matrixrgb, 32 - test, test, 0xF100 );
        Delay_ms ( 100 );
    }

    //Text Write Test
    matrixrgb_fill_screen( &matrixrgb, 0x0000 );
    matrixrgb_write_text( &matrixrgb, "RGB", 6, 5 );
    matrixrgb_write_text( &matrixrgb, "Demo", 4, 20 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    // Image Test
    matrixrgb_draw_image( &matrixrgb, &mikroe_logo_32x32_bmp[ 0 ] );
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
