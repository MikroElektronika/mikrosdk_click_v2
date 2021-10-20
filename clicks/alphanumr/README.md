\mainpage Main Page

---
# AlphaNum R click

AlphaNum click is a simple solution for adding 14-segment alphanumeric display to your device. The board carries two TLC5926 16-bit Constant-Current LED sink Drivers

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/alphanumr_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/alphanum-r-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the AlphaNumR Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for AlphaNumR Click driver.

#### Standard key functions :

- `alphanumr_cfg_setup` Config Object Initialization function.
```c
void alphanumr_cfg_setup ( alphanumr_cfg_t *cfg );
```

- `alphanumr_init` Initialization function.
```c
err_t alphanumr_init ( alphanumr_t *ctx, alphanumr_cfg_t *cfg );
```

- `alphanumr_default_cfg` Click Default Configuration function.
```c
void alphanumr_default_cfg ( alphanumr_t *ctx );
```

#### Example key functions :

- `alphanumr_write_character` This function displays characters on the left and right LED segments.
```c
void alphanumr_write_character ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char );
```

- `alphanumr_write_number` This function displays numbers on the left and right LED segments.
```c
void alphanumr_write_number ( alphanumr_t *ctx, uint8_t left_char, uint8_t right_char );
```

## Example Description

> This example showcases the initialization and configuration of the logger and click modules and shows how to display characters and numbers on both LED segments of the click.

**The demo application is composed of two sections :**

### Application Init

> This function initializes and configures the logger and click modules.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    alphanumr_cfg_t alphanumr_cfg;  /**< Click config object. */

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

    alphanumr_cfg_setup( &alphanumr_cfg );
    ALPHANUMR_MAP_MIKROBUS( alphanumr_cfg, MIKROBUS_1 );
    err_t init_flag  = alphanumr_init( &alphanumr, &alphanumr_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> This function sets the time interval at which the symbols are displayed on the LED segments and shows a few characters and numbers.

```c

void application_task ( void ) {
    alphanumr_set_display_interval( &alphanumr, 1000 );

    alphanumr_write_character( &alphanumr, 'M', 'E' );
    alphanumr_write_character( &alphanumr, '@', '?' );

    alphanumr_write_number( &alphanumr, 0,  1 );
    alphanumr_write_number( &alphanumr, 1,  2 );
    alphanumr_write_number( &alphanumr, 2,  3 );
    alphanumr_write_number( &alphanumr, 3,  4 );
}


```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AlphaNumR

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
