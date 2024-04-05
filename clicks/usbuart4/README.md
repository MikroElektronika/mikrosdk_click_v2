\mainpage Main Page

---
# USB UART 4 click

USB UART 4 click offers a USB to asynchronous serial data (UART) interface, allowing the microcontroller based designs to communicate with the personal computer, in a very simple way. It is equipped with the FT232RL, a very popular USB to UART interface IC, used on many MikroElektronika devices - both for its reliability and simplicity. USB UART click is used for whenever there is a need to seamlessly and effortlessly interface the UART lines to a personal computer

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbuart4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-uart-4-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the USBUART4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USBUART4 Click driver.

#### Standard key functions :

- `usbuart4_cfg_setup` Config Object Initialization function.
```c
void usbuart4_cfg_setup ( usbuart4_cfg_t *cfg );
```

- `usbuart4_init` Initialization function.
```c
err_t usbuart4_init ( usbuart4_t *ctx, usbuart4_cfg_t *cfg );
```

#### Example key functions :

- `usbuart4_pwr_ctrl` This function sets the click turns click on.
```c
void usbuart4_pwr_ctrl ( usbuart4_t *ctx, uint8_t state );
```

- `usbuart4_set_cts` This function sets CTS pin.
```c
void usbuart4_set_cts ( usbuart4_t *ctx, uint8_t state );
```

- `usbuart4_send_command` This function is used for sending commands.
```c
void usbuart4_send_command ( usbuart4_t *ctx, char *command );
```

## Example Description

> This example reads and processes data from USB UART 4 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and power module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart4_cfg_t usbuart4_cfg;  /**< Click config object. */

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

    usbuart4_cfg_setup( &usbuart4_cfg );
    USBUART4_MAP_MIKROBUS( usbuart4_cfg, MIKROBUS_1 );
    
    err_t init_flag  = usbuart4_init( &usbuart4, &usbuart4_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    
    usbuart4_pwr_ctrl( &usbuart4, USBUART4_POWER_ON );
    usbuart4_set_cts( &usbuart4, USBUART4_CTS_NO_ACTIVE );
    usbuart4_set_mode( &usbuart4, USBUART4_MODE_NORMAL );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads data and echos it back to device and logs it to board.

```c

void application_task ( void ) {
    app_buf_len = usbuart4_generic_read( &usbuart4, app_buf, PROCESS_BUFFER_SIZE );
    
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
- Click.USBUART4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
