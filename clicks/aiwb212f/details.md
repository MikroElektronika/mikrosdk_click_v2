
---
# Ai-WB2-12F Click

> Ai-WB2-12F Click is a compact add-on board for easy integration into the Internet of Things (IoT) and smart home applications. This board features the Ai-WB2-12F, a WiFi and BLE module from Ai-Thinker Technology, powered by the BL602 chip supporting WiFi 802.11b/g/n and BLE 5.0 protocols.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/aiwb212f_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ai-wb2-12f-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : UART type


# Software Support

We provide a library for the Ai-WB2-12F Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ai-WB2-12F Click driver.

#### Standard key functions :

- `aiwb212f_cfg_setup` Config Object Initialization function.
```c
void aiwb212f_cfg_setup ( aiwb212f_cfg_t *cfg );
```

- `aiwb212f_init` Initialization function.
```c
err_t aiwb212f_init ( aiwb212f_t *ctx, aiwb212f_cfg_t *cfg );
```

#### Example key functions :

- `aiwb212f_send_cmd` Ai-WB2-12F send command function.
```c
void aiwb212f_send_cmd ( aiwb212f_t *ctx, uint8_t *at_cmd_buf );
```

- `aiwb212f_send_cmd_with_par` Ai-WB2-12F send command with parameter function.
```c
void aiwb212f_send_cmd_with_par ( aiwb212f_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

- `aiwb212f_send_cmd_check` Ai-WB2-12F send command check function.
```c
void aiwb212f_send_cmd_check ( aiwb212f_t *ctx, uint8_t *at_cmd_buf );
```

## Example Description

> This example demonstrates the use of Ai-WB2-12F Click board by processing
  the incoming data and displaying them on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, tests the communication, and after that restarts the device, and performs example configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    aiwb212f_cfg_t aiwb212f_cfg;  /**< Click config object. */

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
    aiwb212f_cfg_setup( &aiwb212f_cfg );
    AIWB212F_MAP_MIKROBUS( aiwb212f_cfg, MIKROBUS_1 );
    if ( UART_ERROR == aiwb212f_init( &aiwb212f, &aiwb212f_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    aiwb212f_process( );
    aiwb212f_clear_app_buf( );

    aiwb212f_hw_reset( &aiwb212f );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_READY );
    aiwb212f_error_check( error_flag );

    // Check communication
    aiwb212f_send_cmd( &aiwb212f, AIWB212F_CMD_AT );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_OK );
    aiwb212f_error_check( error_flag );

    // Restart device
    aiwb212f_send_cmd( &aiwb212f, AIWB212F_CMD_AT_SW_RESET );
    error_flag = aiwb212f_rsp_check( AIWB212F_RSP_READY );
    aiwb212f_error_check( error_flag );

    aiwb212f_configure_for_example( );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the selected demo example, it sends a TCP/UDP echo server message and receives it or 
  creates BLE Client which receives the messages from the connected device.

```c
void application_task ( void ) 
{
    aiwb212f_example( );
}
```

## Note

> We have used the BLE Scanner Android application for the BLE Example test
  and you can find it at the link:
  https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AiWB212F

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
