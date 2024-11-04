\mainpage Main Page

---
# AnyNet 2G Click

> AnyNet 2G Click is a cellular to AWS gateway device, which provides developers with the complete solution for various IoT applications, by using the AWS IoT and Cloud Storage services for the data storage, analyzing and processing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/anynet2g_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/anynet-2g-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type


# Software Support

We provide a library for the ANYNET2G Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ANYNET2G Click driver.

#### Standard key functions :

- `anynet2g_cfg_setup` Config Object Initialization function.
```c
void anynet2g_cfg_setup ( anynet2g_cfg_t *cfg );
```

- `anynet2g_init` Initialization function.
```c
err_t anynet2g_init ( anynet2g_t *ctx, anynet2g_cfg_t *cfg );
```

#### Example key functions :

- `anynet2g_send_cmd` This function sends a specified command to the Click module.
```c
void anynet2g_send_cmd ( anynet2g_t *ctx, uint8_t *cmd );
```

- `anynet2g_send_cmd_with_par` This function sends a command with specified parameter to the Click module.
```c
void anynet2g_send_cmd_with_par ( anynet2g_t *ctx, uint8_t *at_cmd_buf, uint8_t *param_buf );
```

- `anynet2g_send_cmd_check` This function checks the command status.
```c
void anynet2g_send_cmd_check ( anynet2g_t *ctx, uint8_t *at_cmd_buf );
```

## Example Description

> This example demonstrates the use of AnyNet 2G Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and sends a few AT commands to test the communication and configure the Click board.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    anynet2g_cfg_t anynet2g_cfg;  /**< Click config object. */

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
    anynet2g_cfg_setup( &anynet2g_cfg );
    ANYNET2G_MAP_MIKROBUS( anynet2g_cfg, MIKROBUS_1 );
    if ( UART_ERROR == anynet2g_init( &anynet2g, &anynet2g_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    anynet2g_process( );
    anynet2g_clear_app_buf( );

    // Check communication
    anynet2g_send_cmd( &anynet2g, ANYNET2G_CMD_AT );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    
    // Query VERSION info for the AnyNet AWS IoT code
    anynet2g_send_cmd( &anynet2g, ANYNET2G_CMD_AWSVER );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    
    // Query IMEI of the modem on the board
    anynet2g_send_cmd( &anynet2g, ANYNET2G_CMD_GSN );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    
    // Query ICCID of the SIM
    anynet2g_send_cmd( &anynet2g, ANYNET2G_CMD_QCCID );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    
    // Check AWS State
    anynet2g_send_cmd_check( &anynet2g, ANYNET2G_CMD_AWSSTATE );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    
    // Open AWS topic
    #define AWS_TOPIC_OPEN "0,\"MY_TOPIC_OPEN\""
    anynet2g_send_cmd_with_par( &anynet2g, ANYNET2G_CMD_AWSPUBOPEN, AWS_TOPIC_OPEN );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    
    // Subscribe to AWS topic
    #define AWS_TOPIC_SUBSCRIBE "0,\"MY_TOPIC_SUBSCRIBE\""
    anynet2g_send_cmd_with_par( &anynet2g, ANYNET2G_CMD_AWSSUBOPEN, AWS_TOPIC_SUBSCRIBE );
    error_flag = anynet2g_rsp_check( ANYNET2G_RSP_OK );
    anynet2g_error_check( error_flag );
    anynet2g_clear_app_buf( );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads all the received data and logs them to the USB UART.

```c

void application_task ( void ) 
{
    anynet2g_process( );
    anynet2g_log_app_buf( );
    anynet2g_clear_app_buf( );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.AnyNet2G

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
