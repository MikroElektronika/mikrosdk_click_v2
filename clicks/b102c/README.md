\mainpage Main Page

---
# B102C Click

> B102C Click is a compact add-on board designed for Bluetooth 5.0 (BLE) communication in various wireless applications. This board features the B102C, a Bluetooth module from Amphenol based on the Realtek RTL8762CMF chip. The board offers BLE v5.0 support, a 20MHz Arm® Cortex® M4F processor, and an integrated antenna for 2.4GHz communication, with low-power modes for optimal energy efficiency. It includes UART and USB Type-C connectivity, a PROG header for debugging, and fully programmable GPIOs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/b102c_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/b102c-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Feb 2024.
- **Type**          : UART type


# Software Support

We provide a library for the B102C Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for B102C Click driver.

#### Standard key functions :

- `b102c_cfg_setup` Config Object Initialization function.
```c
void b102c_cfg_setup ( b102c_cfg_t *cfg );
```

- `b102c_init` Initialization function.
```c
err_t b102c_init ( b102c_t *ctx, b102c_cfg_t *cfg );
```

- `b102c_default_cfg` Click Default Configuration function.
```c
err_t b102c_default_cfg ( b102c_t *ctx );
```

#### Example key functions :

- `b102c_send_cmd` This function sends a specified command to the B102C Click module.
```c
void b102c_send_cmd ( b102c_t *ctx, uint8_t *cmd );
```

- `b102c_send_cmd_with_params` This function sends a command with specified parameter to the Click module.
```c
void b102c_send_cmd_with_params ( b102c_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

- `b102c_send_cmd_params_check` This function checks the command that is sent.
```c
void b102c_send_cmd_params_check ( b102c_t *ctx, uint8_t *at_cmd_buf );
```

## Example Description

> This example demonstrates the use of B102C Click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, then performs a factory reset and sets the local device name.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    b102c_cfg_t b102c_cfg;  /**< Click config object. */

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
    b102c_cfg_setup( &b102c_cfg );
    B102C_MAP_MIKROBUS( b102c_cfg, MIKROBUS_1 );
    if ( UART_ERROR == b102c_init( &b102c, &b102c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_printf( &logger, " Software reset. \r\n" );
    b102c_send_cmd( &b102c, B102C_CMD_RESET );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_READY );
    
    log_printf( &logger, " Factory reset. \r\n" );
    b102c_send_cmd( &b102c, B102C_CMD_DEFAULT );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_READY );

    log_printf( &logger, " Set device name. \r\n" );
    #define DEVICE_NAME             "B102C Click"
    b102c_send_cmd_with_params( &b102c, B102C_CMD_NAME, DEVICE_NAME );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_OK );

    log_printf( &logger, " Set Auto broadcast mode. \r\n" );
    #define AUTO_BROADCAST          "1"
    b102c_send_cmd_with_params( &b102c, B102C_CMD_ADVMOD, AUTO_BROADCAST );
    app_error_flag = b102c_rsp_check( &b102c, B102C_RSP_OK );

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Connect to device. " );
}

```

### Application Task

> Reads and processes all incoming data and displays them on the USB UART.

```c
void application_task ( void ) 
{
    if ( B102C_OK == b102c_process( &b102c ) ) 
    {
        b102c_log_app_buf( );
        b102c_clear_app_buf( );
    }
}

```

## Note

> For communication with B102C Click use the android application on the link:
> https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.B102C

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
