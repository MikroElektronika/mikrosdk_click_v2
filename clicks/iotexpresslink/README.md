
---
# IoT ExpressLink Click

> [IoT ExpressLink Click](https://www.mikroe.com/?pid_product=MIKROE-5800) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5800&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of IoT ExpressLink Click board by bridging the USB UART
to mikroBUS UART which allows the Click board to establish a connection with
the IoT ExpressLink over the Quick Connect demo application without an AWS account.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IoTExpressLink

### Example Key Functions

- `iotexpresslink_cfg_setup` Config Object Initialization function.
```c
void iotexpresslink_cfg_setup ( iotexpresslink_cfg_t *cfg );
```

- `iotexpresslink_init` Initialization function.
```c
err_t iotexpresslink_init ( iotexpresslink_t *ctx, iotexpresslink_cfg_t *cfg );
```

- `iotexpresslink_reset_device` This function resets device by toggling the RST pin state.
```c
void iotexpresslink_reset_device ( iotexpresslink_t *ctx );
```

- `iotexpresslink_send_cmd` This function send command string by using UART serial interface.
```c
void iotexpresslink_send_cmd ( iotexpresslink_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver, resets the Click board to factory default settings, reads
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
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, "Factory reset\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK_CMD_FACTORY_RESET );
    iotexpresslink_send_cmd ( &iotexpresslink, app_buf );
    iotexpresslink_read_response ( &iotexpresslink );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
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

### Note

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

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
