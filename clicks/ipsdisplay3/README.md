
---
# IPS Display 3 Click

> [IPS Display 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6542) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6542&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the IPS Display 3 Click board by showing a practical example of using the implemented functions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IPSDisplay3

### Example Key Functions

- `ipsdisplay3_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ipsdisplay3_cfg_setup ( ipsdisplay3_cfg_t *cfg );
```

- `ipsdisplay3_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ipsdisplay3_init ( ipsdisplay3_t *ctx, ipsdisplay3_cfg_t *cfg );
```

- `ipsdisplay3_default_cfg` This function executes a default configuration of IPS Display 3 Click board.
```c
err_t ipsdisplay3_default_cfg ( ipsdisplay3_t *ctx );
```

- `ipsdisplay3_fill_screen` This function fills the screen with the selected color.
```c
err_t ipsdisplay3_fill_screen ( ipsdisplay3_t *ctx, uint16_t color );
```

- `ipsdisplay3_write_string` This function writes a text string starting from the selected position in configured font size with a specified color.
```c
err_t ipsdisplay3_write_string ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, uint8_t *data_in, uint16_t color );
```

- `ipsdisplay3_draw_line` This function draws a line with a specified color.
```c
err_t ipsdisplay3_draw_line ( ipsdisplay3_t *ctx, ipsdisplay3_point_t start_pt, ipsdisplay3_point_t end_pt, uint16_t color );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipsdisplay3_cfg_t ipsdisplay3_cfg;  /**< Click config object. */

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
    ipsdisplay3_cfg_setup( &ipsdisplay3_cfg );
    IPSDISPLAY3_MAP_MIKROBUS( ipsdisplay3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ipsdisplay3_init( &ipsdisplay3, &ipsdisplay3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IPSDISPLAY3_ERROR == ipsdisplay3_default_cfg ( &ipsdisplay3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Showcases the text writing example as well as drawing pictures and objects,
and filling the whole screen with a desired color. All data is logged on the USB UART
where you can track the program flow.

```c
void application_task ( void )
{
    ipsdisplay3_point_t start_pt, end_pt;

#if IPSDISPLAY3_RESOURCES_INCLUDE_IMG
    log_printf( &logger, " Drawing MIKROE logo example\r\n\n" );
    ipsdisplay3_draw_picture ( &ipsdisplay3, IPSDISPLAY3_ROTATION_VERTICAL_0, ipsdisplay3_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
    log_printf( &logger, " Writing text example\r\n\n" );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = 0;
    start_pt.y = ipsdisplay3.center.y - 50;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "    MIKROE    ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "   128x115px  ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, " IPS Display 3", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "     Click    ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "    GC9107    ", IPSDISPLAY3_COLOR_RED );
    start_pt.y += 15;
    ipsdisplay3_write_string ( &ipsdisplay3, start_pt, "  controller  ", IPSDISPLAY3_COLOR_RED );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " RGB fill screen example\r\n\n" );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_RED );
    Delay_ms ( 1000 );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_LIME );
    Delay_ms ( 1000 );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_BLUE );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing objects example\r\n\n" );
    ipsdisplay3_fill_screen ( &ipsdisplay3, IPSDISPLAY3_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = ipsdisplay3.center.x - 50;
    start_pt.y = ipsdisplay3.center.y - 50;
    end_pt.x = ipsdisplay3.center.x + 50;
    end_pt.y = ipsdisplay3.center.y + 50;
    ipsdisplay3_draw_line ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = ipsdisplay3.center.x + 50;
    start_pt.y = ipsdisplay3.center.y - 50;
    end_pt.x = ipsdisplay3.center.x - 50;
    end_pt.y = ipsdisplay3.center.y + 50;
    ipsdisplay3_draw_line ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = ipsdisplay3.center.x - 40;
    start_pt.y = ipsdisplay3.center.y - 40;
    end_pt.x = ipsdisplay3.center.x + 40;
    end_pt.y = ipsdisplay3.center.y + 40;
    ipsdisplay3_draw_rectangle ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_CYAN );
    Delay_ms ( 1000 );
    start_pt.x += 20;
    start_pt.y += 20;
    end_pt.x -= 20;
    end_pt.y -= 20;
    ipsdisplay3_draw_rectangle ( &ipsdisplay3, start_pt, end_pt, IPSDISPLAY3_COLOR_CYAN );
    Delay_ms ( 1000 );
    ipsdisplay3_draw_circle ( &ipsdisplay3, ipsdisplay3.center, ipsdisplay3.center.x - 25, IPSDISPLAY3_COLOR_MAGENTA );
    Delay_ms ( 1000 );
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
