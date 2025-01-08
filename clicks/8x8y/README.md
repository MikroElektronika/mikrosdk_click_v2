
---
# 8x8 Y Click

> [8x8 Y Click](https://www.mikroe.com/?pid_product=MIKROE-1294) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1294&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo example shows a drawing of Image, new create string and character on the screen.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.8x8Y

### Example Key Functions

- `c8x8y_cfg_setup` Config Object Initialization function.
```c
void c8x8y_cfg_setup ( c8x8y_cfg_t *cfg );
```

- `c8x8y_init` Initialization function.
```c
err_t c8x8y_init ( c8x8y_t *ctx, c8x8y_cfg_t *cfg );
```

- `c8x8y_default_cfg` Click Default Configuration function.
```c
void c8x8y_default_cfg ( c8x8y_t *ctx );
```

- `c8x8y_write_cmd` This function writes a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
void c8x8y_write_cmd ( c8x8y_t *ctx, uint8_t cmd, uint8_t tx_data  );
```

- `c8x8y_display_refresh` The function switches off all LEDs.
```c
void c8x8y_display_refresh ( c8x8y_t *ctx );
```

- `c8x8y_display_byte` This function displayes one character to the display.
```c
void c8x8y_display_byte ( c8x8y_t *ctx, char tx_byte );
```

### Application Init

> Configuring Clicks and log objects. Settings the Click in the default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c8x8y_cfg_t c8x8y_cfg;  /**< Click config object. */

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

    c8x8y_cfg_setup( &c8x8y_cfg );
    C8X8Y_MAP_MIKROBUS( c8x8y_cfg, MIKROBUS_1 );
    err_t init_flag  = c8x8y_init( &c8x8y, &c8x8y_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c8x8y_default_cfg ( &c8x8y );
    log_info( &logger, " Application Task " );
    Delay_1sec( );
}
```

### Application Task

> Shows one byte, then scrolls the string and image, every 1 sec.

```c
void application_task ( void ) 
{
    c8x8y_display_byte( &c8x8y, demo_char );
    Delay_ms ( 1000 );
    
    c8x8y_display_string( &c8x8y, &demo_string[ 0 ] );
    Delay_ms ( 1000 );

    c8x8y_display_image( &c8x8y, &demo_img_on[ 0 ] );
    Delay_ms ( 500 );

    c8x8y_display_image( &c8x8y, &demo_img_off[ 0 ] );
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
