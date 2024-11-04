\mainpage Main Page
 
 

---
# Matrix RGB Click

Matrix RGB Click is a mikroBUS™ add-on board powered by a 32-bit FT900 MCU designed specifically for powering 16x32 RGB LED matrices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/matrixrgb_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/matrix-rgb-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the MatrixRGB Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MatrixRGB Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void matrixrgb_cfg_setup ( matrixrgb_cfg_t *cfg ); 
 
- Initialization function.
> MATRIXRGB_RETVAL matrixrgb_init ( matrixrgb_t *ctx, matrixrgb_cfg_t *cfg );

- Click Pattern Settings ( Default Configuration ) function.
> void matrixrgb_pattern_settings ( matrixrgb_t *ctx, uint8_t pattern_type, uint16_t pattern_delay_us );


#### Example key functions :

- Set Power
> void matrixrgb_set_power ( matrixrgb_t *ctx, uint8_t power_state );
 
- Set Brightness
> void matrixrgb_set_brightness ( matrixrgb_t *ctx, uint8_t brightness );

- Write Pixel
> uint8_t matrixrgb_write_pixel ( matrixrgb_t *ctx, uint16_t x, uint16_t y, uint16_t color );

## Examples Description

> This application is used for powering 16x32 RGB LED matrices.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MatrixRGB

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
