
---
# WiFi NORA Click

> WiFi NORA Click is a compact add-on board that provides WiFi and BLE connectivity for professional-grade applications. This board features the NORA-W366-00B6-00B, a dual-band WiFi module with Bluetooth Low Energy (BLE) from u-blox, offering support for WiFi 4 (802.11a/b/g/n) in both 2.4 and 5GHz bands and Bluetooth v5.3 with peripheral and central roles. It features a UART interface for easy integration with the host MCU, high-level AT command configuration, and robust security protocols, including WPA2/WPA3 and TLS encryption. The board also includes a user-configurable RGB LED indicator and buttons for bootloader and application mode selection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifinora_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/wifi-nora-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : UART type


# Software Support

We provide a library for the WiFi NORA Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for WiFi NORA Click driver.

#### Standard key functions :

- `wifinora_cfg_setup` Config Object Initialization function.
```c
void wifinora_cfg_setup ( wifinora_cfg_t *cfg );
```

- `wifinora_init` Initialization function.
```c
err_t wifinora_init ( wifinora_t *ctx, wifinora_cfg_t *cfg );
```

#### Example key functions :

- `wifinora_hw_reset` This function is used to perform HW reset.
```c
void wifinora_hw_reset ( wifinora_t *ctx );
```

- `wifinora_send_cmd` This function is used to send a desired command.
```c
void wifinora_send_cmd ( wifinora_t *ctx, uint8_t *at_cmd_buf );
```

- `wifinora_send_cmd_with_par` This function sends a desired command with the parameter.
```c
void wifinora_send_cmd_with_par ( wifinora_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

## Example Description

> This example demonstrates the use of WiFi NORA Click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, tests the communication, and after that restarts the device, and performs example configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifinora_cfg_t wifinora_cfg;  /**< Click config object. */

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
    wifinora_cfg_setup( &wifinora_cfg );
    WIFINORA_MAP_MIKROBUS( wifinora_cfg, MIKROBUS_1 );
    if ( UART_ERROR == wifinora_init( &wifinora, &wifinora_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    wifinora_process( );
    wifinora_clear_app_buf( );

    // Hardware reset
    wifinora_hw_reset( &wifinora );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_READY );
    wifinora_error_check( error_flag );

    // Communication check
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    // Factory reset
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_USYFR );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    // Software reset
    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_SW_RESET );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_READY );
    wifinora_error_check( error_flag );

    wifinora_send_cmd( &wifinora, WIFINORA_CMD_AT_GMM );
    error_flag = wifinora_rsp_check( WIFINORA_RSP_OK );
    wifinora_error_check( error_flag );

    wifinora_configure_for_example( );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> It creates a connection to the TCP-UDP echo server, sends a message to it reads it back, displaces it on the UART terminal, and then closes the connection.

```c
void application_task ( void ) 
{
    wifinora_example( );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.WiFiNORA

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
