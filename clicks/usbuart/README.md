\mainpage Main Page

---
# USB UART Click

USB UART Click offers a USB to asynchronous serial data (UART) interface, allowing the microcontroller based designs to communicate with the personal computer, in a very simple way. It is equipped with the FT232RL, a very popular USB to UART interface IC, used on many MikroElektronika devices - both for its reliability and simplicity. USB UART Click is used for whenever there is a need for seamless and effortless interfacing of the UART lines to a personal computer.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbuart_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/usb-uart-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the USBUART Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USBUART Click driver.

#### Standard key functions :

- `usbuart_cfg_setup` Config Object Initialization function.
```c
void usbuart_cfg_setup ( usbuart_cfg_t *cfg );
```

- `usbuart_init` Initialization function.
```c
err_t usbuart_init ( usbuart_t *ctx, usbuart_cfg_t *cfg );
```

#### Example key functions :

- `usbuart_pwr_ctrl` This function sets the Click turns Click on.
```c
void usbuart_pwr_ctrl ( usbuart_t *ctx, uint8_t state );
```

- `usbuart_set_cts` This function sets CTS pin.
```c
void usbuart_set_cts ( usbuart_t *ctx, uint8_t state );
```

- `usbuart_send_command` This function is used for sending commands.
```c
void usbuart_send_command ( usbuart_t *ctx, char *command );
```

## Example Description

> This example reads and processes data from USB UART clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and power module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart_cfg_t usbuart_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );

    // Click initialization.

    usbuart_cfg_setup( &usbuart_cfg );
    USBUART_MAP_MIKROBUS( usbuart_cfg, MIKROBUS_1 );
    
    err_t init_flag  = usbuart_init( &usbuart, &usbuart_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    
    usbuart_pwr_ctrl( &usbuart, USBUART_POWER_ON );
    usbuart_set_cts( &usbuart, USBUART_CTS_NO_ACTIVE );
    usbuart_set_mode( &usbuart, USBUART_MODE_NORMAL );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads data and echos it back to device and logs it to board.

```c

void application_task ( void ) {
    app_buf_len = usbuart_generic_read( &usbuart, app_buf, PROCESS_BUFFER_SIZE );
    
    if ( app_buf_len > 0 ) {
        log_printf( &logger, "%s", app_buf );
        memset( app_buf, 0, PROCESS_BUFFER_SIZE );
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBUART

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
