\mainpage Main Page

---
# Current Limit click

> Current Limit Click is a compact add-on board that contains a low-voltage, P-channel MOSFET power switch intended for high-side load switching applications. This board features the MAX890L, a low-resistance power switch with the adjustable, accurate current limit system, and thermal shutdown from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentlimit_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-limit-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the CurrentLimit Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for CurrentLimit Click driver.

#### Standard key functions :

- `currentlimit_cfg_setup` Config Object Initialization function.
```c
void currentlimit_cfg_setup ( currentlimit_cfg_t *cfg );
```

- `currentlimit_init` Initialization function.
```c
err_t currentlimit_init ( currentlimit_t *ctx, currentlimit_cfg_t *cfg );
```

#### Example key functions :

- `currentlimit_dev_enable` Device enable function.
```c
void currentlimit_dev_enable ( currentlimit_t *ctx, uint8_t state );
```

- `currentlimit_set_limit` Set Current With Predefined Values Limit function.
```c
void currentlimit_set_limit ( currentlimit_t *ctx, uint8_t lim_val );
```

- `currentlimit_set_limit_calc` Set Calculated Current Limit function.
```c
void currentlimit_set_limit_calc ( currentlimit_t *ctx, float lim_val );
```

## Example Description

> This example shows capabilities of Current Limit Click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes SPI driver and enables the device.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit_cfg_t currentlimit_cfg;  /**< Click config object. */

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

    currentlimit_cfg_setup( &currentlimit_cfg );
    CURRENTLIMIT_MAP_MIKROBUS( currentlimit_cfg, MIKROBUS_1 );
    err_t init_flag  = currentlimit_init( &currentlimit, &currentlimit_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    currentlimit_dev_enable( &currentlimit, CURRENTLIMIT_ENABLE );
    log_printf( &logger, "    Click  Enabled!    \r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    display_settings( );
}

```

### Application Task

> Reading users input from USART terminal and using it as an index for an array of pre-calculated values that define current limit level.

```c

void application_task ( void ) {
    char inx;
    if ( log_read( &logger, &inx, 1 ) != CURRENTLIMIT_ERROR ) {
        if ( inx >= '1' && inx <= '8' ) {
            currentlimit_set_limit( &currentlimit, lim_val[ inx - 1 ] );
            log_printf( &logger, " Selected mode %d, \r\n Current limit is %d mA \r\n", ( uint16_t ) inx - 48, lim_data[ inx - 49 ] );
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
        } else { 
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
            log_printf( &logger, " Data not in range! \r\n" );
            log_printf( &logger, "- - - - - - - - - - - - - - - \r\n" );
            display_settings( );
        }
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit

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
