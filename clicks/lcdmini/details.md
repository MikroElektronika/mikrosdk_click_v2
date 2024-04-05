
---
# LCD mini click

> LCD mini click displays 2x16 monochrome characters on an LMB162XFW LCD display. It features the MCP23S17 port expander and the MCP4161 digital potentiometer, both from Microchip.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lcdmini_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lcd-mini-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the LCD mini Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LCD mini Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This is an example that demonstrates the use of the LCD mini Click board.

**The demo application is composed of two sections :**

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

## Note

> If the screen isn't initialized you may need to restart the device.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LCDmini

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
