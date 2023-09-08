
---
# IoT ExpressLink click

> IoT ExpressLink Click is a compact add-on board that allows users 
> to easily connected to IoT ExpressLink services 
> and securely interact with cloud applications and other devices. 
> This board features the ESP32-C3-MINI-1-N4-A, a small 2.4GHz WiFi (802.11 b/g/n) 
> and Bluetooth® 5 module from Espressif Systems that use ESP32C3 series 
> of SoC RISCV single-core microprocessor (ESP32-C3FN4) with 4MB flash in a single chip package. 
> The module uses UART communication alongside several other features like the JTAG interface, 
> module wake-up, various operational event detection, additional UART for debugging, and others.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/iotexpresslink_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iot-expresslink-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type


# Software Support

We provide a library for the IoT ExpressLink Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IoT ExpressLink Click driver.

#### Standard key functions :

- `iotexpresslink_cfg_setup` Config Object Initialization function.
```c
void iotexpresslink_cfg_setup ( iotexpresslink_cfg_t *cfg );
```

- `iotexpresslink_init` Initialization function.
```c
err_t iotexpresslink_init ( iotexpresslink_t *ctx, iotexpresslink_cfg_t *cfg );
```

#### Example key functions :

- `iotexpresslink_reset_device` This function resets device by toggling the RST pin state.
```c
void iotexpresslink_reset_device ( iotexpresslink_t *ctx );
```

- `iotexpresslink_send_cmd` This function send command string by using UART serial interface.
```c
void iotexpresslink_send_cmd ( iotexpresslink_t *ctx, uint8_t *cmd );
```

## Example Description

> This example demonstrates the use of IoT ExpressLink click board by bridging the USB UART
to mikroBUS UART which allows the click board to establish a connection with
the IoT ExpressLink over the Quick Connect demo application without an AWS account.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, resets the click board to factory default settings, reads
and displays the vendor model and thing name on the USB UART, sets the WiFi credentials,
and attempts to connect to the AWS Cloud. If the initial attempt fails and the error
message "Failed to access network" or "Failed to login AWS (MQTT) broker" appears,
check the WiFi credentials and try running the example again.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iotexpresslink_cfg_t iotexpresslink_cfg;  /**< Click config object. */

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
    iotexpresslink_cfg_setup( &iotexpresslink_cfg );
    IOTEXPRESSLINK_MAP_MIKROBUS( iotexpresslink_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iotexpresslink_init( &iotexpresslink, &iotexpresslink_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, "Reset device\r\n\n" );
    iotexpresslink_reset_device ( &iotexpresslink );
    Delay_ms ( 2000 );
    log_printf( &logger, "Factory reset\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_FACTORY_RESET );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    Delay_ms ( 2000 );
    
    log_printf( &logger, "Vendor model\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_ABOUT );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "Thing name\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_THING_NAME );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "WiFi SSID\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_SSID );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SIGN_EQUAL );
    strcat ( app_buf, WIFI_SSID );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "WiFi Password\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK_CONF_KEY_PASSPHRASE );
    strcat ( app_buf, IOTEXPRESSLINK_CMD_SIGN_EQUAL );
    strcat ( app_buf, WIFI_PASS );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_printf( &logger, "Try to connect\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_CONNECT );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    
    log_info( &logger, " Application Task " );
    
    log_printf( &logger, "Now close the UART terminal and switch to the QuickConnect app\r\n" );
    Delay_ms ( 1000 );
    
    uart_set_blocking( &logger.uart, false );
}

```

### Application Task

> All data received from the USB UART will be forwarded to mikroBUS UART, and vice versa.
At this point you should disconnect from the UART terminal and run the Quick Connect demo application.

```c
void application_task ( void )
{
    app_buf_len = uart_read( &logger.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &iotexpresslink.uart, app_buf, app_buf_len );
        iotexpresslink_clear_app_buf( );
    }
    app_buf_len = uart_read( &iotexpresslink.uart, app_buf, PROCESS_BUFFER_SIZE );
    if ( app_buf_len > 0 ) 
    {
        uart_write ( &logger.uart, app_buf, app_buf_len );
        iotexpresslink_clear_app_buf( );
    }
}
```

## Note

> To run the demo, follow the below steps:
> 1. If you opened a terminal application in the previous step, be sure to > disconnect that application from the serial port. 
> 2. Download the Quick Connect executable: 
> - [Mac](https://quickconnectexpresslinkutility.s3.us-west-2.amazonaws.com/QuickConnect_v1.9_macos.x64.tar.gz)
> - [Windows](https://quickconnectexpresslinkutility.s3.us-west-2.amazonaws.com/QuickConnect_v1.9_windows.x64.zip)
> - [Linux](https://quickconnectexpresslinkutility.s3.us-west-2.amazonaws.com/QuickConnect_v1.9_linux.x64.tar.gz)
> 3. Unzip the package, and follow the steps from the README file.
> 
> The demo will connect to IoT ExpressLink and give you an URL that you can use to visualize data
flowing from the device to the cloud using AT+SEND commands. The demo will run for up
to two minutes, and afterwards, you will be able to type AT+SEND commands yourself and
see the data coming in on the visualizer.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IoTExpressLink

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
