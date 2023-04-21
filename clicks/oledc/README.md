\mainpage Main Page
 
---
# OLED C click

OLED C click is equipped with the 96x96 high-color OLED display.
It can display up to 65K/262K different colors and shades on a compact size display, based on the OLED technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/oledc_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/oled-c-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the OledC Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OledC Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void oledc_cfg_setup ( oledc_cfg_t *cfg ); 
 
- Initialization function.
> OLEDC_RETVAL oledc_init ( oledc_t *ctx, oledc_cfg_t *cfg );

- Click Default Configuration function.
> void oledc_default_cfg ( oledc_t *ctx );


#### Example key functions :

- Fill Screen.
> void oledc_fill_screen( oledc_t *ctx, uint16_t color );

- Draw BMP Image.
> void oledc_image( oledc_t *ctx, const uint8_t *img, uint8_t column_off, uint8_t row_off );

## Examples Description

> This demo demonstrates the use of the OLED C click board and the control of the OLED C display.

**The demo application is composed of two sections :**

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

    oledc_set_font( &oledc, guiFont_Tahoma_8_Regular, 0 );
    oledc_text( &oledc, text1, 15, 10 );
    oledc_text( &oledc, text2, 5, 30 );
    oledc_text( &oledc, text3, 5, 45 );
    Delay_ms( 1000 );
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
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 5, 5, 91, 91, 0xFF00 );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 10, 10, 86, 86, 0x00F0 );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 15, 15, 81, 81, 0x0F0F );
    Delay_ms( 500 );
    oledc_rectangle( &oledc, 20, 20, 76, 76, 0xF000 );
    Delay_ms( 500 );
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
    Delay_ms( 3000 );


    // Image demo 
    oledc_image( &oledc, mikroe_with_slogan96x96, 0, 0 );
    Delay_ms( 2000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OledC

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
