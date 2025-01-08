
---
# AnyNet 3G-EA Click

> [AnyNet 3G-EA Click](https://www.mikroe.com/?pid_product=MIKROE-2975) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2975&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of AnyNet 3G-EA Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AnyNet3GEA

### Example Key Functions

- `anynet3gea_cfg_setup` Config Object Initialization function.
```c
void anynet3gea_cfg_setup ( anynet3gea_cfg_t *cfg );
```

- `anynet3gea_init` Initialization function.
```c
err_t anynet3gea_init ( anynet3gea_t *ctx, anynet3gea_cfg_t *cfg );
```

- `anynet3gea_send_cmd` This function sends a specified command to the Click module.
```c
void anynet3gea_send_cmd ( anynet3gea_t *ctx, uint8_t *cmd );
```

- `anynet3gea_send_cmd_with_par` This function sends a command with specified parameter to the Click module.
```c
void anynet3gea_send_cmd_with_par ( anynet3gea_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

- `anynet3gea_send_cmd_check` This function checks the command status.
```c
void anynet3gea_send_cmd_check ( anynet3gea_t *ctx, uint8_t *at_cmd_buf );
```

### Application Init

> Initializes the driver and sends a few AT commands to test the communication and configure the Click board.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    anynet3gea_cfg_t anynet3gea_cfg;  /**< Click config object. */

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
    anynet3gea_cfg_setup( &anynet3gea_cfg );
    ANYNET3GEA_MAP_MIKROBUS( anynet3gea_cfg, MIKROBUS_1 );
    if ( UART_ERROR == anynet3gea_init( &anynet3gea, &anynet3gea_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    anynet3gea_process( );
    anynet3gea_clear_app_buf( );

    // Check communication
    anynet3gea_send_cmd( &anynet3gea, ANYNET3GEA_CMD_AT );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    
    // Query VERSION info for the AnyNet AWS IoT code
    anynet3gea_send_cmd( &anynet3gea, ANYNET3GEA_CMD_AWSVER );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    
    // Query IMEI of the modem on the board
    anynet3gea_send_cmd( &anynet3gea, ANYNET3GEA_CMD_GSN );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    
    // Query ICCID of the SIM
    anynet3gea_send_cmd( &anynet3gea, ANYNET3GEA_CMD_QCCID );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    
    // Check AWS State
    anynet3gea_send_cmd_check( &anynet3gea, ANYNET3GEA_CMD_AWSSTATE );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    
    // Open AWS topic
    #define AWS_TOPIC_OPEN "0,\"MY_TOPIC_OPEN\""
    anynet3gea_send_cmd_with_par( &anynet3gea, ANYNET3GEA_CMD_AWSPUBOPEN, AWS_TOPIC_OPEN );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    
    // Subscribe to AWS topic
    #define AWS_TOPIC_SUBSCRIBE "0,\"MY_TOPIC_SUBSCRIBE\""
    anynet3gea_send_cmd_with_par( &anynet3gea, ANYNET3GEA_CMD_AWSSUBOPEN, AWS_TOPIC_SUBSCRIBE );
    error_flag = anynet3gea_rsp_check( ANYNET3GEA_RSP_OK );
    anynet3gea_error_check( error_flag );
    anynet3gea_clear_app_buf( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads all the received data and logs them to the USB UART.

```c
void application_task ( void ) 
{
    anynet3gea_process( );
    anynet3gea_log_app_buf( );
    anynet3gea_clear_app_buf( );
}
```

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
