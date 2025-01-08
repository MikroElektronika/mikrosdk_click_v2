
---
# IoT ExpressLink 2 Click

> [IoT ExpressLink 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5927) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5927&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of IoT ExpressLink 2 Click board by connecting
to the selected AWS account's data endpoint and showcasing the messaging topic model
through sending and receiving messages to/from AWS IoT console.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IoTExpressLink2

### Example Key Functions

- `iotexpresslink2_cfg_setup` Config Object Initialization function.
```c
void iotexpresslink2_cfg_setup ( iotexpresslink2_cfg_t *cfg );
```

- `iotexpresslink2_init` Initialization function.
```c
err_t iotexpresslink2_init ( iotexpresslink2_t *ctx, iotexpresslink2_cfg_t *cfg );
```

- `iotexpresslink2_power_on` This function performs the power on sequence.
```c
void iotexpresslink2_power_on ( iotexpresslink2_t *ctx );
```

- `iotexpresslink2_send_cmd` This function send command string by using UART serial interface.
```c
void iotexpresslink2_send_cmd ( iotexpresslink2_t *ctx, uint8_t *cmd );
```

- `iotexpresslink2_generic_read` This function reads a desired number of data bytes by using UART serial interface.
```c
err_t iotexpresslink2_generic_read ( iotexpresslink2_t *ctx, uint8_t *data_out, uint16_t len );
```

### Application Init

> Initializes the driver and logger, powers up the device, reads and displays
the vendor model, thing name, and the PEM certificate of the device. It then sets
the SIM APN and device endpoint, and attempts to connect to AWS network.
Finally, it configures the topic name and number and subscribes to it.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iotexpresslink2_cfg_t iotexpresslink2_cfg;  /**< Click config object. */

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
    iotexpresslink2_cfg_setup( &iotexpresslink2_cfg );
    IOTEXPRESSLINK2_MAP_MIKROBUS( iotexpresslink2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iotexpresslink2_init( &iotexpresslink2, &iotexpresslink2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "Power up device\r\n\n" );
    iotexpresslink2_power_on ( &iotexpresslink2 );

    log_printf( &logger, "Get vendor model\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_ABOUT );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Get thing name\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_THING_NAME );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Get certificate pem\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_CERTIFICATE_PEM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Set SIM APN to: %s\r\n", ( char * ) SIM_APN );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_APN );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SIGN_EQUAL );
    strcat ( app_buf, SIM_APN );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Set device endpoint to: %s\r\n", ( char * ) DEVICE_ENDPOINT );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_ENDPOINT );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SIGN_EQUAL );
    strcat ( app_buf, DEVICE_ENDPOINT );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Trying to connect...\r\n" );
    log_printf( &logger, "This may take up to 15min for the initial connect.\r\n" );
    iotexpresslink2_send_cmd ( &iotexpresslink2, IOTEXPRESSLINK2_CMD_CONNECT );
    if ( IOTEXPRESSLINK2_OK != 
         iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_CONNECT_TIMEOUT ) )
    {
        log_printf( &logger, "\r\nUNABLE TO CONNECT\r\n" );
        log_printf( &logger, "Make sure that the SIM card is inserted in the board, \r\n" ); 
        log_printf( &logger, "an antenna is connected, and the module is within range \r\n" );
        log_printf( &logger, "of a cellular network that provides LTE-M coverage.\r\n" );
        log_printf( &logger, "Double check that the device registration procedure have been \r\n" );
        log_printf( &logger, "correctly followed. If CONNECT worked in the past for this \r\n" );
        log_printf( &logger, "device, it may be that the cellular network has decided \r\n" );
        log_printf( &logger, "to refuse service for a \"guard time\" (e.g. 1 hour) because \r\n" );
        log_printf( &logger, "the device has connected and disconnected more than a handful \r\n" );
        log_printf( &logger, "of times in quick succession. The only way to avoid this is \r\n" );
        log_printf( &logger, "avoiding many connections/disconnections. \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, "Set topic %s to: %s\r\n", ( char * ) TOPIC_NUM, ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_TOPIC );
    strcat ( app_buf, TOPIC_NUM );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SIGN_EQUAL );
    strcat ( app_buf, TOPIC_NAME );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Subscribe to topic %s\r\n", ( char * ) TOPIC_NUM );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_SUBSCRIBE );
    strcat ( app_buf, TOPIC_NUM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sends a desired message on the configured topic and retrieves the next two pending
messages from the same topic approximately every 10 seconds. The sent message is also
added to the receive queue because the same topic is used for both sending and receiving.

```c
void application_task ( void )
{
    // Send message on topic
    log_printf( &logger, "Send message on topic: %s\r\n", ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_SEND );
    strcat ( app_buf, TOPIC_NUM );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, TEXT_MESSAGE );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    Delay_ms ( 1000 );
    
    // Retrieve the next message received on topic in the order of arrival.
    log_printf( &logger, "Request next message pending on topic: %s\r\n", ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_GET );
    strcat ( app_buf, TOPIC_NUM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    Delay_ms ( 1000 );
    
    // Retrieve the next message received on topic in the order of arrival.
    log_printf( &logger, "Request next message pending on topic: %s\r\n", ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_GET );
    strcat ( app_buf, TOPIC_NUM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Steps for the very first connection attempt:
> 1. During the initial connection attempt, the device responds with: "ERR14 UNABLE TO CONNECT
> Certificate generation completed. Proceed to register device with AWS cloud and then try to connect again". 
> 2. At this point, you should restart the system and proceed with registering the device
> with the AWS Cloud using device's thing name and PEM certificate displayed in the logger.
> Detailed steps for registering device are described in the module's application development guide. 
> 3. After registering the device with your AWS account, restart the system, and it should now successfully connect to the cloud.

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
