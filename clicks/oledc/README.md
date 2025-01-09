
---
# OLED C Click

> [OLED C Click](https://www.mikroe.com/?pid_product=MIKROE-1585) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1585&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This demo demonstrates the use of the OLED C Click board and the control of the OLED C display.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.OledC

### Example Key Functions

- `oledc_cfg_setup` Config Object Initialization function. 
```c
void oledc_cfg_setup ( oledc_cfg_t *cfg );
``` 
 
- `oledc_init` Initialization function. 
```c
err_t oledc_init ( oledc_t *ctx, oledc_cfg_t *cfg );
```

- `oledc_default_cfg` Click Default Configuration function. 
```c
void oledc_default_cfg ( oledc_t *ctx );
```

- `oledc_fill_screen` Fill Screen. 
```c
void oledc_fill_screen ( oledc_t *ctx, uint16_t color );
```

- `oledc_image` Draw BMP Image. 
```c
void oledc_image ( oledc_t *ctx, const uint8_t *img, uint8_t column_off, uint8_t row_off );
```

### Application Init

> Initializes driver init and OLED C init and sets full screen on white color with writting demo text.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    oledc_cfg_t cfg;

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

    oledc_cfg_setup( &cfg );
    OLEDC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oledc_init( &oledc, &cfg );

    oledc_default_cfg( &oledc );
    oledc_fill_screen( &oledc, 0xFFFF );

#ifndef IMAGE_MODE_ONLY
    oledc_set_font( &oledc, guiFont_Tahoma_8_Regular, 0 );
    oledc_text( &oledc, text1, 15, 10 );
    oledc_text( &oledc, text2, 5, 30 );
    oledc_text( &oledc, text3, 5, 45 );
#endif
    Delay_ms ( 1000 );
}
```

### Application Task

> This function is composed of three sections :
>  -  Display demo rectangle.
>  -  Display demo line.
>  -  Display demo image.

```c
void application_task ( void )
{
    oledc_fill_screen( &oledc, 0xFFFF );
    Delay_100ms();

    // Rectangle demo
    oledc_rectangle( &oledc, 0, 0, 96, 96, 0xF000 );
    Delay_ms ( 500 );
    oledc_rectangle( &oledc, 5, 5, 91, 91, 0xFF00 );
    Delay_ms ( 500 );
    oledc_rectangle( &oledc, 10, 10, 86, 86, 0x00F0 );
    Delay_ms ( 500 );
    oledc_rectangle( &oledc, 15, 15, 81, 81, 0x0F0F );
    Delay_ms ( 500 );
    oledc_rectangle( &oledc, 20, 20, 76, 76, 0xF000 );
    Delay_ms ( 500 );
    oledc_rectangle( &oledc, 25, 25, 71, 71, 0xFF00 );
    Delay_100ms();

    // Line demo 
    oledc_rectangle( &oledc, 25, 25, 71, 27, 0 );
    Delay_100ms();
    oledc_rectangle( &oledc, 25, 71, 71, 73, 0 );
    Delay_100ms();
    oledc_rectangle( &oledc, 25, 25, 27, 71, 0 );
    Delay_100ms();
    oledc_rectangle( &oledc, 68, 25, 71, 71, 0 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );


    // Image demo 
    oledc_image( &oledc, mikroe_with_slogan96x96, 0, 0 );
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
