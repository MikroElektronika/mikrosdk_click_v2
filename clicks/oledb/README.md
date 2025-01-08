
---
# OLED B Click

> [OLED B Click](https://www.mikroe.com/?pid_product=MIKROE-1650) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1650&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2023.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use (control) of the OLED B display.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OLEDB

### Example Key Functions

- `oledb_cfg_setup` Config Object Initialization function.
```c
void oledb_cfg_setup ( oledb_cfg_t *cfg );
```

- `oledb_init` Initialization function.
```c
err_t oledb_init ( oledb_t *ctx, oledb_cfg_t *cfg );
```

- `oledb_display_picture` This function allows user to display picture for on the screen.
```c
void oledb_display_picture( oledb_t *ctx, oledb_resources_t *pic );
```

- `oledb_clear_display` This function clears SSD1306 controller display.
```c
void oledb_clear_display( oledb_t *ctx );
```

- `oledb_write_string` This function writes a text string from the selected position in a 5x7 or 6x8 font size.
```c
void oledb_write_string( oledb_t *ctx, uint8_t font, uint8_t row, uint8_t position, uint8_t *data_in );
```

### Application Init

> Configures the microcontroller for communication and initializes the Click board to default state.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    oledb_cfg_t oledb_cfg;  /**< Click config object. */

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
    oledb_cfg_setup( &oledb_cfg );
    OLEDB_MAP_MIKROBUS( oledb_cfg, MIKROBUS_1 );
    err_t init_flag  = oledb_init( &oledb, &oledb_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    oledb_default_cfg ( &oledb );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This section contains the main program that is executed showing a practical example on how to use the implemented functions.

```c
void application_task ( void ) 
{
    oledb_clear_display( &oledb );
    Delay_ms ( 100 );

    oledb_write_string( &oledb, OLEDB_FONT_6X8, 0, 0, "     MIKROE     " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 1, 0, "  OLED B Click  " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 2, 0, "  with SSD1306  " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 3, 0, "   controller   " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 4, 0, "  TEST EXAMPLE  " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 0, 0, " TEXT SCROLL EXAMPLE " );
    oledb_write_string( &oledb, OLEDB_FONT_6X8, 4, 0, " TEXT SCROLL EXAMPLE " );
    Delay_ms ( 1000 );
    
    oledb_scroll_right( &oledb, 4, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    oledb_stop_scroll( &oledb );
    
    oledb_clear_display( &oledb );
    Delay_ms ( 100 );
    
    oledb_display_picture( &oledb, oledb_img_mikroe );
    Delay_ms ( 500 );
    oledb_send_cmd( &oledb, OLEDB_INVERTDISPLAY );
    Delay_ms ( 500 );
    oledb_send_cmd( &oledb, OLEDB_NORMALDISPLAY );
    Delay_ms ( 500 );
    oledb_send_cmd( &oledb, OLEDB_INVERTDISPLAY );
    Delay_ms ( 500 );
    oledb_send_cmd( &oledb, OLEDB_NORMALDISPLAY );
    Delay_ms ( 300 );

    for ( uint8_t contrast = 0xAF; contrast > 0x00; contrast-- ) 
    {
        oledb_set_contrast( &oledb, contrast );
        Delay_ms ( 5 );
    }

    for ( uint8_t contrast = 0x00; contrast < 0xAF; contrast++ ) 
    {
        oledb_set_contrast( &oledb, contrast );
        Delay_ms ( 5 );
    }

    oledb_scroll_left( &oledb, 0, 4 );
    Delay_ms ( 1000 );
    oledb_stop_scroll( &oledb );

    oledb_scroll_right( &oledb, 0, 4 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    oledb_stop_scroll( &oledb );
    
    oledb_scroll_left( &oledb, 0, 4 );
    Delay_ms ( 1000 );
    oledb_stop_scroll( &oledb );
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
