
---
# 8x8 B Click

8x8 B Click is a 64 LED matrix display Click board™, composed of SMD LEDs organized in 8 rows by 8 columns. It has a digital brightness control in 16 steps, it can control every LED in the display matrix independently, it blanks the display on power up to eliminate glitches and it requires a single resistor to control the current through all the LEDs at once, which simplifies the design. 8x8 B Click uses a fast SPI communication protocol, allowing fast display response and no lag.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/8x8b_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/8x8-b-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the 8X8B Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 8X8B Click driver.

#### Standard key functions :

- `c8x8b_cfg_setup` Config Object Initialization function.
```c
void c8x8b_cfg_setup ( c8x8b_cfg_t *cfg );
```

- `c8x8b_init` Initialization function.
```c
err_t c8x8b_init ( c8x8b_t *ctx, c8x8b_cfg_t *cfg );
```

- `c8x8b_default_cfg` Click Default Configuration function.
```c
void c8x8b_default_cfg ( c8x8b_t *ctx );
```

#### Example key functions :

- `c8x8b_write_cmd` This function writes a desired number of data bytes starting from the selected register by using SPI serial interface.
```c
void c8x8b_write_cmd ( c8x8b_t *ctx, uint8_t cmd, uint8_t tx_data  );
```

- `c8x8b_display_refresh` The function switches off all LEDs.
```c
void c8x8b_display_refresh ( c8x8b_t *ctx );
```

- `c8x8b_display_byte` This function displayes one character to the display.
```c
void c8x8b_display_byte ( c8x8b_t *ctx, char tx_byte );
```

## Example Description

> This demo example shows a drawing of Image, new create string and character on the screen.

**The demo application is composed of two sections :**

### Application Init

> Configuring clicks and log objects. Settings the Click in the default configuration.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    c8x8b_cfg_t c8x8b_cfg;  /**< Click config object. */

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

    c8x8b_cfg_setup( &c8x8b_cfg );
    C8X8B_MAP_MIKROBUS( c8x8b_cfg, MIKROBUS_1 );
    err_t init_flag  = c8x8b_init( &c8x8b, &c8x8b_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c8x8b_default_cfg ( &c8x8b );
    log_info( &logger, " Application Task " );
    Delay_1sec( );
}

```

### Application Task

> Shows one byte, then scrolls the string and image, every 1 sec.

```c

void application_task ( void ) {
    c8x8b_display_byte( &c8x8b, demo_char );
    Delay_ms ( 1000 );
    
    c8x8b_display_string( &c8x8b, &demo_string[ 0 ] );
    Delay_ms ( 1000 );

    c8x8b_display_image( &c8x8b, &demo_img_on[ 0 ] );
    Delay_ms ( 500 );

    c8x8b_display_image( &c8x8b, &demo_img_off[ 0 ] );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.8X8B

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
