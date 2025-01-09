
---
# LCD mini Click

> [LCD mini Click](https://www.mikroe.com/?pid_product=MIKROE-2453) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2453&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the LCD mini Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LCDmini

### Example Key Functions

- `lcdmini_cfg_setup` Config Object Initialization function.
```c
void lcdmini_cfg_setup ( lcdmini_cfg_t *cfg );
```

- `lcdmini_init` Initialization function.
```c
err_t lcdmini_init ( lcdmini_t *ctx, lcdmini_cfg_t *cfg );
```

- `lcdmini_default_cfg` Click Default Configuration function.
```c
err_t lcdmini_default_cfg ( lcdmini_t *ctx );
```

- `lcdmini_set_backlight` Set backlight function.
```c
void lcdmini_set_backlight ( lcdmini_t *ctx, float backlight_value );
```

- `lcdmini_set_contrast` Set contrast function.
```c
void lcdmini_set_contrast( lcdmini_t *ctx, uint8_t contrast_value );
```

- `lcdmini_display_text` LCD mini display text.
```c
void lcdmini_display_text ( lcdmini_t *ctx, uint8_t row, uint8_t column, char *data_in );
```

### Application Init

> Initialization driver enables - SPI, performing hardware reset, default config, 
> setting up the backlight, and entering text to be written.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lcdmini_cfg_t lcdmini_cfg;  /**< Click config object. */

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
    lcdmini_cfg_setup( &lcdmini_cfg );
    LCDMINI_MAP_MIKROBUS( lcdmini_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == lcdmini_init( &lcdmini, &lcdmini_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    lcdmini_hw_reset( &lcdmini );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   SPI LCD Config    \r\n" );
    log_printf( &logger, " Clear LCD display   \r\n" );
    log_printf( &logger, "     Cursor OFF      \r\n" );
    
    if ( LCDMINI_ERROR == lcdmini_default_cfg ( &lcdmini ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Setting Backlight  \r\n" );
    lcdmini_set_backlight ( &lcdmini, 1 );
    Delay_ms ( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "  Set Contrast: 200  \r\n" );
    lcdmini_set_contrast( &lcdmini, 200 );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "     Display text    \r\n" );
    log_printf( &logger, "---------------------\r\n" );
    
    lcdmini_display_text ( &lcdmini, 1, 6, "Mikro E" );
    lcdmini_display_text ( &lcdmini, 2, 2, "LCD mini Click" ); 
    lcdmini_display_text ( &lcdmini, 3, 2, "LCD mini Click" ); 
    lcdmini_display_text ( &lcdmini, 4, 6, "Mikro E" );
    Delay_ms ( 500 );
}
```

### Application Task

> This example shows the written text, then the text is moved left, 
> with changing between rows of the LCD screen.

```c
void application_task ( void )
{
    Delay_ms ( 500 );
    lcdmini_send_cmd( &lcdmini, LCDMINI_SHIFT_LEFT ); 
}
```

### Note

> If the screen isn't initialized you may need to restart the device.

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
