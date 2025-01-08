
---
# WiFi 8 Click

> [WiFi 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4704) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4704&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This application showcases capability of the WiFi 8 Click board. 
It initializes device, connects to local WiFi. Creates TCP, waits for connection
and logs every message it receives for clients when it receives CR or LF flag
it returns message back to Client.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WiFi8

### Example Key Functions

- `wifi8_cfg_setup` Config Object Initialization function.
```c
void wifi8_cfg_setup ( wifi8_cfg_t *cfg );
```

- `wifi8_init` Initialization function.
```c
err_t wifi8_init ( wifi8_t *ctx, wifi8_cfg_t *cfg );
```

- `wifi8_default_cfg` Click Default Configuration function.
```c
err_t wifi8_default_cfg ( wifi8_t *ctx );
```

- `wifi8_init_drv` Synchronous API to initialize the device driver.
```c
err_t wifi8_init_drv(wifi8_t *ctx);
```

- `wifi8_connect` Asynchronous Wi-Fi connection function.
```c
err_t wifi8_connect(wifi8_t *ctx, char *pc_ssid, uint8_t u8_ssid_len, wifi8_m2m_sec_type_t u8_sec_type, void *pv_auth_info, uint16_t u16_ch);
```

- `wifi8_socket_bind` Asynchronous bind function associates the provided address and local port to the socket.
```c
err_t wifi8_socket_bind(wifi8_t *ctx, int8_t sock, wifi8_sockaddr_t *pstr_addr, uint8_t u8_addr_len);
```

### Application Init

> Initializes Host logger, and communication module and pins. 
Then resets device and initializes devices firmware. If no error
occurred it sets callback functions for WiFi and TCP socket, and checks
current firmware version. After firmware is read it connects to local WiFi network 
set by user. When connected it initializes and creates socket.

```c
void application_init(void)
{
    log_cfg_t log_cfg;
    wifi8_cfg_t wifi8_cfg;

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
    log_info(&logger, " Application Init ");

    Delay_ms ( 1000 );

    wifi8_cfg_setup(&wifi8_cfg);
    WIFI8_MAP_MIKROBUS(wifi8_cfg, MIKROBUS_1);
    err_t init_flag = wifi8_init(&wifi8, &wifi8_cfg);
    if (init_flag == SPI_MASTER_ERROR)
    {
        log_error(&logger, " Application Init Error. ");
        log_info(&logger, " Please, run program again... ");
        for (;;);
    }

    if (WIFI8_OK != wifi8_default_cfg(&wifi8))
    {
        log_error(&logger, " Default configuartion. ");
        for (;;); 
    }
    //Set callback functions for WiFi and TCP socket
    wifi8.app_wifi_cb = wifi_cb;
    wifi8.app_socket_cb = socket_cb;
    wifi_connected = M2M_WIFI_DISCONNECTED;

    wifi8_m2m_rev_t fw_version;
    if (WIFI8_OK == wifi8_get_full_firmware_version(&wifi8, &fw_version))
    {
        log_printf(&logger, "Firmware HIF (%u) : %u.%u \n", 
                   ((uint16_t)(((fw_version.u16_firmware_hif_info) >> (14)) & (0x3))), 
                   ((uint16_t)(((fw_version.u16_firmware_hif_info) >> (8)) & (0x3f))), 
                   ((uint16_t)(((fw_version.u16_firmware_hif_info) >> (0)) & (0xff))));
        log_printf(&logger, "Firmware ver   : %u.%u.%u \n", 
                   (uint16_t)fw_version.u8_firmware_major, 
                   (uint16_t)fw_version.u8_firmware_minor, 
                   (uint16_t)fw_version.u8_firmware_patch);
        log_printf(&logger, "Firmware Build %s Time %s\n", fw_version.build_date, fw_version.build_time);
    }
    else
    {
        log_error(&logger, " reading full firmware version ");
        for (;;);
    }

    if (wifi_connected == M2M_WIFI_DISCONNECTED)
    {
        if (WIFI8_OK != wifi8_connect(&wifi8, MAIN_WLAN_SSID, sizeof(MAIN_WLAN_SSID), 
                                      MAIN_WLAN_AUTH, MAIN_WLAN_PSK, M2M_WIFI_CH_ALL))
        {
            log_error(&logger, " Connection");
            for (;;);
        }
        else
        {
            log_info(&logger, " Connecting... ");
        }
    }

    while (wifi_connected != M2M_WIFI_CONNECTED)
    {
        wifi8_handle_events(&wifi8);
    }

    wifi8_socket_init(&wifi8);
    addr.sin_family = 2;
    addr.sin_port = (uint16_t)((((uint16_t)((MAIN_TCP_SERVER_PORT))) << 8) | (((uint16_t)((MAIN_TCP_SERVER_PORT))) >> 8));
    addr.sin_addr.s_addr = 0;

    log_info(&logger, " Application Task ");
}
```

### Application Task

> It loops function for handling events. Should notify and log messages when Client
is connected/disconnected to TCP server and returns back when receives CR or LF flag.

```c
void application_task(void)
{
    wifi8_handle_events(&wifi8);

    if (tcp_server_socket < 0)
    {

        if ((tcp_server_socket = wifi8_socket_create(&wifi8, 2, 1, 0)) < 0)
        {
            log_printf(&logger, "main: failed to create TCP server socket error!\r\n");
        }
        else
        {
            wifi8_socket_bind(&wifi8, tcp_server_socket, (wifi8_sockaddr_t *)&addr,
                              sizeof(wifi8_sockaddr_in_t));
        }
    }
}
```

### Note

> User should set MAIN_WLAN_SSID and MAIN_WLAN_PSK for connecting to local network.
When devices connects to network it will log its IP that user need to connect to.
After user connects it should get notification and it can send data to server. 
Server will return message "WiFi 8 Click" when Client sends CR or LF character in message.

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
