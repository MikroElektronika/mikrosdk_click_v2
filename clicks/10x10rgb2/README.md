
---
# 10x10 RGB 2 Click

> [10x10 RGB 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5976) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5976&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the 10x10 RGB 2 Click board by showing a practical example of using the implemented functions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.10x10RGB2

### Example Key Functions

- `c10x10rgb2_cfg_setup` Config Object Initialization function.
```c
void c10x10rgb2_cfg_setup ( c10x10rgb2_cfg_t *cfg );
```

- `c10x10rgb2_init` Initialization function.
```c
err_t c10x10rgb2_init ( c10x10rgb2_t *ctx, c10x10rgb2_cfg_t *cfg );
```

- `c10x10rgb2_default_cfg` Click Default Configuration function.
```c
err_t c10x10rgb2_default_cfg ( c10x10rgb2_t *ctx );
```

- `c10x10rgb2_write_char` This function writes a single ASCII character in a 8x8 font size.
```c
err_t c10x10rgb2_write_char ( c10x10rgb2_t *ctx, uint8_t data_in );
```

- `c10x10rgb2_write_string` This function writes a text string in a 8x8 font size by scrolling characters to the left side.
```c
err_t c10x10rgb2_write_string ( c10x10rgb2_t *ctx, uint8_t *data_in, uint16_t speed_ms );
```

- `c10x10rgb2_draw_picture` This function draws a 10x10px picture on the screen.
```c
err_t c10x10rgb2_draw_picture ( c10x10rgb2_t *ctx, const uint32_t *image );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c10x10rgb2_cfg_t c10x10rgb2_cfg;  /**< Click config object. */

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
    c10x10rgb2_cfg_setup( &c10x10rgb2_cfg );
    C10X10RGB2_MAP_MIKROBUS( c10x10rgb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c10x10rgb2_init( &c10x10rgb2, &c10x10rgb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C10X10RGB2_ERROR == c10x10rgb2_default_cfg ( &c10x10rgb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Displays digits 0-9 first, then writes RGB chars and demonstrates the rotation of characters.
After that, scrolls the text, displays the MIKROE logo image, and showcases a rainbow demo.
All data is logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    log_printf( &logger, " Writing digits\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_MAROON, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    for ( uint8_t digit = '0'; digit <= '9'; digit++ )
    {
        c10x10rgb2_write_char ( &c10x10rgb2, digit );
        Delay_ms ( 500 );
    }

    log_printf( &logger, " Writing RGB chars\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_RED, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 1000 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_BLACK, C10X10RGB2_COLOR_GREEN, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'G' );
    Delay_ms ( 1000 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_BLUE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'B' );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Rotating char\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_H_180 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_180 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_H_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_PURPLE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_char ( &c10x10rgb2, 'R' );
    Delay_ms ( 500 );
    
    log_printf( &logger, " Writing text\r\n\n" );
    c10x10rgb2_set_pen ( &c10x10rgb2, C10X10RGB2_COLOR_OLIVE, C10X10RGB2_COLOR_BLACK, C10X10RGB2_ROTATION_V_0 );
    c10x10rgb2_write_string ( &c10x10rgb2, "MIKROE 10x10 RGB 2", 50 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing MIKROE logo\r\n\n" );
    c10x10rgb2_draw_picture ( &c10x10rgb2, c10x10rgb_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Rainbow demo\r\n\n" );
    c10x10rgb2_demo_rainbow ( &c10x10rgb2, 10, 10, 500 );
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
