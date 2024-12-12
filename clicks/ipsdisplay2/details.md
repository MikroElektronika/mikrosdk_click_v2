
---
# IPS Display 2 Click

> IPS Display 2 Click is a compact add-on board that displays high-resolution graphics in embedded applications. This board features the ER-TFT1.54-2, a 1.54inch TFT LCD display from EastRising Technology, and uses the ST7789V2 controller for 262K color output. The display offers a 240x240 pixel resolution, operates through a 3-wire SPI interface, and includes additional control signals for precise display management. Its small form factor and high-resolution output make it suitable for various projects, including handheld devices, smart displays, and panels requiring clear visual output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ipsdisplay2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ips-display-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2024.
- **Type**          : SPI type


# Software Support

We provide a library for the IPS Display 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IPS Display 2 Click driver.

#### Standard key functions :

- `ipsdisplay2_cfg_setup` Config Object Initialization function.
```c
void ipsdisplay2_cfg_setup ( ipsdisplay2_cfg_t *cfg );
```

- `ipsdisplay2_init` Initialization function.
```c
err_t ipsdisplay2_init ( ipsdisplay2_t *ctx, ipsdisplay2_cfg_t *cfg );
```

- `ipsdisplay2_default_cfg` Click Default Configuration function.
```c
err_t ipsdisplay2_default_cfg ( ipsdisplay2_t *ctx );
```

#### Example key functions :

- `ipsdisplay2_fill_screen` This function fills the screen with the selected color.
```c
err_t ipsdisplay2_fill_screen ( ipsdisplay2_t *ctx, uint16_t color );
```

- `ipsdisplay2_write_string` This function writes a text string starting from the selected position in a 6x12 font size with a specified color.
```c
err_t ipsdisplay2_write_string ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, uint8_t *data_in, uint16_t color );
```

- `ipsdisplay2_draw_line` This function draws a line with a specified color.
```c
err_t ipsdisplay2_draw_line ( ipsdisplay2_t *ctx, ipsdisplay2_point_t start_pt, ipsdisplay2_point_t end_pt, uint16_t color );
```

## Example Description

> This example demonstrates the use of the IPS Display 2 Click board by showing a practical example of using the implemented functions.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ipsdisplay2_cfg_t ipsdisplay2_cfg;  /**< Click config object. */

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
    ipsdisplay2_cfg_setup( &ipsdisplay2_cfg );
    IPSDISPLAY2_MAP_MIKROBUS( ipsdisplay2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ipsdisplay2_init( &ipsdisplay2, &ipsdisplay2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IPSDISPLAY2_ERROR == ipsdisplay2_default_cfg ( &ipsdisplay2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Showcases the text writing example as well as drawing pictures and objects, and filling the whole screen with a desired color.
All data is logged on the USB UART where you can track the program flow.

```c
void application_task ( void )
{
    ipsdisplay2_point_t start_pt, end_pt;

#if IPSDISPLAY2_RESOURCES_INCLUDE_IMG
    log_printf( &logger, " Drawing MIKROE logo example\r\n\n" );
    ipsdisplay2_draw_picture ( &ipsdisplay2, IPSDISPLAY2_ROTATION_VERTICAL_0, ipsdisplay2_img_mikroe );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
    log_printf( &logger, " Writing text example\r\n\n" );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = 60;
    start_pt.y = 70;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "      MIKROE      ", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, " IPS display Click", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "     240x240px    ", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "ST7789V controller", IPSDISPLAY2_COLOR_RED );
    start_pt.y += 20;
    ipsdisplay2_write_string ( &ipsdisplay2, start_pt, "   TEST EXAMPLE   ", IPSDISPLAY2_COLOR_RED );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " RGB fill screen example\r\n\n" );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_RED );
    Delay_ms ( 1000 );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_LIME );
    Delay_ms ( 1000 );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_BLUE );
    Delay_ms ( 1000 );

    log_printf( &logger, " Drawing objects example\r\n\n" );
    ipsdisplay2_fill_screen ( &ipsdisplay2, IPSDISPLAY2_COLOR_BLACK );
    Delay_ms ( 1000 );
    start_pt.x = IPSDISPLAY2_POS_WIDTH_MIN;
    start_pt.y = IPSDISPLAY2_POS_HEIGHT_MIN;
    end_pt.x = IPSDISPLAY2_POS_WIDTH_MAX;
    end_pt.y = IPSDISPLAY2_POS_HEIGHT_MAX;
    ipsdisplay2_draw_line ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = IPSDISPLAY2_POS_WIDTH_MAX;
    start_pt.y = IPSDISPLAY2_POS_HEIGHT_MIN;
    end_pt.x = IPSDISPLAY2_POS_WIDTH_MIN;
    end_pt.y = IPSDISPLAY2_POS_HEIGHT_MAX;
    ipsdisplay2_draw_line ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_BLUE );
    Delay_ms ( 1000 );
    start_pt.x = 60;
    start_pt.y = 40;
    end_pt.x = 180;
    end_pt.y = 100;
    ipsdisplay2_draw_rectangle ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_CYAN );
    Delay_ms ( 1000 );
    start_pt.y += 100;
    end_pt.y += 100;
    ipsdisplay2_draw_rectangle ( &ipsdisplay2, start_pt, end_pt, IPSDISPLAY2_COLOR_CYAN );
    Delay_ms ( 1000 );
    start_pt.x = 120;
    start_pt.y = 120;
    ipsdisplay2_draw_circle ( &ipsdisplay2, start_pt, start_pt.x, IPSDISPLAY2_COLOR_MAGENTA );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IPSDisplay2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
