
---
# USB UART 2 click

USB UART 2 click provides USB isolation and carries the ADUM4160BRWZ USB port isolator. The click is designed to run on either 3.3V or 5V power supply. It communicates with the target microcontroller over UART interface, with additional functionality provided the following pins on the mikroBUS™ line: RST, CS, PWM, INT.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbuart2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-uart-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the USBUART2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USBUART2 Click driver.

#### Standard key functions :

- `usbuart2_cfg_setup` Config Object Initialization function.
```c
void usbuart2_cfg_setup ( usbuart2_cfg_t *cfg );
```

- `usbuart2_init` Initialization function.
```c
err_t usbuart2_init ( usbuart2_t *ctx, usbuart2_cfg_t *cfg );
```

#### Example key functions :

- `usbuart2_pwr_ctrl` This function sets the click turns click on.
```c
void usbuart2_pwr_ctrl ( usbuart2_t *ctx, uint8_t state );
```

- `usbuart2_set_cts` This function sets CTS pin.
```c
void usbuart2_set_cts ( usbuart2_t *ctx, uint8_t state );
```

- `usbuart2_send_command` This function is used for sending commands.
```c
void usbuart2_send_command ( usbuart2_t *ctx, char *command );
```

## Example Description

> This example reads and processes data from USB UART 2 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and power module.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbuart2_cfg_t usbuart2_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 100 );

    // Click initialization.

    usbuart2_cfg_setup( &usbuart2_cfg );
    USBUART2_MAP_MIKROBUS( usbuart2_cfg, MIKROBUS_1 );
    
    err_t init_flag  = usbuart2_init( &usbuart2, &usbuart2_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    
    usbuart2_pwr_ctrl( &usbuart2, USBUART2_POWER_ON );
    usbuart2_set_cts( &usbuart2, USBUART2_CTS_NO_ACTIVE );
    usbuart2_set_mode( &usbuart2, USBUART2_MODE_NORMAL );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads data and echos it back to device and logs it to board.

```c

void application_task ( void ) {
    app_buf_len = usbuart2_generic_read( &usbuart2, app_buf, PROCESS_BUFFER_SIZE );
    
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
- Click.USBUART2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
