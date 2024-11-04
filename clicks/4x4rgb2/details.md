
---
# 4x4 RGB 2 Click

> 4x4 RGB 2 Click is a compact add-on board that contains a matrix of 16 intelligent RGB LEDs, forming a 4x4 display screen. This board features 16 IN-PC55TBTRGB, 5x5mm RGB LEDs with an integrated IC from Inolux. The LEDs feature an 8-bit color control in 256 steps (256-level greyscale) and a 5-bit brightness control in 32 steps. The intelligent LEDs are cascaded (daisy-chained); thus, every one of them can communicate with the host MCU using the same data lines.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4x4rgb2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/4x4-rgb-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the 4x4 RGB 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 4x4 RGB 2 Click driver.

#### Standard key functions :

- `c4x4rgb2_cfg_setup` Config Object Initialization function.
```c
void c4x4rgb2_cfg_setup ( c4x4rgb2_cfg_t *cfg );
```

- `c4x4rgb2_init` Initialization function.
```c
err_t c4x4rgb2_init ( c4x4rgb2_t *ctx, c4x4rgb2_cfg_t *cfg );
```

- `c4x4rgb2_default_cfg` Click Default Configuration function.
```c
err_t c4x4rgb2_default_cfg ( c4x4rgb2_t *ctx );
```

#### Example key functions :

- `c4x4rgb2_set_led_color` This function sets the color of the selected led in the led matrix.
```c
void c4x4rgb2_set_led_color ( c4x4rgb2_t *ctx, uint8_t led_num, uint32_t rgb );
```

- `c4x4rgb2_set_led_brightness` This function sets the brightness of the selected led in the led matrix.
```c
void c4x4rgb2_set_led_brightness ( c4x4rgb2_t *ctx, uint8_t led_num, uint8_t brightness );
```

- `c4x4rgb2_write_led_matrix` This function writes the led matrix data from the Click context object.
```c
err_t c4x4rgb2_write_led_matrix ( c4x4rgb2_t *ctx );
```

## Example Description

> This example demonstrates the use of 4x4 RGB 2 Click board by setting all 16 LEDs to different colors and changing the LEDs color every 500 milliseconds. 

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets the LEDs brightness to level 1 and the color to black (all LEDs off).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4x4rgb2_cfg_t c4x4rgb2_cfg;  /**< Click config object. */

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
    c4x4rgb2_cfg_setup( &c4x4rgb2_cfg );
    C4X4RGB2_MAP_MIKROBUS( c4x4rgb2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == c4x4rgb2_init( &c4x4rgb2, &c4x4rgb2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( C4X4RGB2_ERROR == c4x4rgb2_default_cfg ( &c4x4rgb2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets all 16 LEDs to a different colors and changes their color every 500 milliseconds. All data is displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t color_num = 0;
    for ( uint8_t led_cnt = C4X4RGB2_LED_0; led_cnt <= C4X4RGB2_LED_15; led_cnt++ )
    {
        c4x4rgb2_set_led_color ( &c4x4rgb2, led_cnt, 
                                 color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].rgb );
        log_printf( &logger, " LED %u Color: %s - %.6LX\r\n", ( uint16_t ) led_cnt, 
                    color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].name, 
                    color[ ( led_cnt + color_num ) % C4X4RGB2_NUM_COLORS ].rgb );
    }
    if ( C4X4RGB2_OK == c4x4rgb2_write_led_matrix ( &c4x4rgb2 ) )
    {
        log_printf( &logger, " Write LED Matrix\r\n\n" );
        Delay_ms ( 500 );
    }
    if ( ++color_num >= C4X4RGB2_NUM_COLORS )
    {
        color_num = 0;
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.4x4RGB2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
