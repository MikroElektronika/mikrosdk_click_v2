
---
# ZigBee Click

> [ZigBee Click](https://www.mikroe.com/?pid_product=MIKROE-4277) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4277&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : UART type

# Software Support

## Example Description

> This is an example that demonstrates the use of the ZigBee Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ZigBee

### Example Key Functions

- `zigbee_cfg_setup` Config Object Initialization function.
```c
void zigbee_cfg_setup ( zigbee_cfg_t *cfg );
```

- `zigbee_init` Initialization function.
```c
err_t zigbee_init ( zigbee_t *ctx, zigbee_cfg_t *cfg );
```

- `zigbee_default_cfg` Click Default Configuration function.
```c
err_t zigbee_default_cfg ( zigbee_t *ctx );
```

- `zigbee_send_at` Function merges two string and sends it to device.
```c
void zigbee_send_at ( zigbee_t *ctx, uint8_t *at_buf, uint8_t *suffix_buf );
```

- `zigbee_resp` Function checking driver buffer string.
```c
uint8_t zigbee_resp ( zigbee_t *ctx, char *data_in );
```

- `zigbee_set_pin_rst` Function setting RST pin status.
```c
void zigbee_set_pin_rst ( zigbee_t *ctx, uint8_t status );
```

### Application Init

> Initialization of driver, UART ISR and then configures device. 
> Depending on previous selected device mode it creates new PAN network or joins to one.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    zigbee_cfg_t zigbee_cfg;  /**< Click config object. */

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
    app_mode = ZIGBEE_APP_INIT;
    dev_mode = ZIGBEE_DEV_USER;

    // Click initialization.
    zigbee_cfg_setup( &zigbee_cfg );
    ZIGBEE_MAP_MIKROBUS( zigbee_cfg, MIKROBUS_1 );
    if ( UART_ERROR == zigbee_init( &zigbee, &zigbee_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Restarting Device \r\n" );
    zigbee_restart( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + DASSL \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_DASSL );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : ATZ \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_ATZ );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : ATI \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_ATI );
    resp_wait( &zigbee );

    log_printf( &logger, "------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + N \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_N );
    resp_wait( &zigbee );
    
    if ( ZIGBEE_DEV_HOST == dev_mode )
    {
        // Setting the device into host mode and creating a network for other devices to connect.
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + HOST CFG 1 \r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_ATS, &AT_HOST_CFG1[ 0 ] );
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + HOST CFG 2 \r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_ATS, &AT_HOST_CFG2[ 0 ] );
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + HOST CFG 3 \r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_ATS, &AT_HOST_CFG3[ 0 ] );
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + EN \r\n", app_buf );
        zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_EN );
        resp_wait( &zigbee );
    }
    else if ( ZIGBEE_DEV_USER == dev_mode )
    {
        // Setting the device into user mode and joining the existing network.
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        log_printf( &logger, " Sending command : AT + JN \r\n", app_buf );
        zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_JN );
        resp_wait( &zigbee );
    }

    log_printf( &logger, "-----------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + IDREQ \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_IDREQ );
    resp_wait( &zigbee );

    log_printf( &logger, "-----------------------------------\r\n", app_buf );
    log_printf( &logger, " Sending command : AT + N \r\n", app_buf );
    zigbee_send_cmd( &zigbee, ZIGBEE_CMD_AT_N );
    resp_wait( &zigbee );

    Delay_ms ( 1000 );
    app_mode = ZIGBEE_APP_TASK;
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------------\r\n", app_buf );
}
```

### Application Task

> Host mode: Broadcasts message 'MikroE' every 3 seconds.
> User mode: Cheks if something is received.

```c
void application_task ( void ) 
{
    if ( ZIGBEE_DEV_HOST == dev_mode )
    {
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
        zigbee_send_at( &zigbee, ZIGBEE_CMD_AT_BCAST, &AT_BCAST_MSG[ 0 ] );
        resp_wait( &zigbee );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else if ( ZIGBEE_DEV_USER == dev_mode )
    {
        resp_wait( &zigbee );
        log_printf( &logger, "-----------------------------------\r\n", app_buf );
    }
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
