
---
# Wifi 9 click

WiFi 9 Click is fully embedded stand-alone Wi-Fi module, equipped with the PAN9420 a 2.4 GHz ISM band Wi-Fi-embedded module which includes a wireless radio and an MCU for easy integration of Wi-Fi connectivity into various electronic devices.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/wifi9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/wifi-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Wifi9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Wifi9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void wifi9_cfg_setup ( wifi9_cfg_t *cfg ); 
 
- Initialization function.
> WIFI9_RETVAL wifi9_init ( wifi9_t *ctx, wifi9_cfg_t *cfg );

- Click Default Configuration function.
> void wifi9_default_cfg ( wifi9_t *ctx );


#### Example key functions :

- Switch to a command or binary uart
> void wifi9_select_uart ( wifi9_t *ctx, uint8_t uart_select );
 
- Module power up.
> void wifi9_module_power ( wifi9_t *ctx );

- Send Command function.
> void wifi9_send_command ( wifi9_t *ctx, char *command );

## Examples Description

> This example reads and processes data from Wifi 9 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    wifi9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    wifi9_cfg_setup( &cfg );
    WIFI9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    wifi9_init( &wifi9, &cfg );

    wifi9_module_power( &wifi9 );
    wifi9_select_uart( &wifi9, WIFI9_SELECT_CMD_UART );

    Delay_ms( 4000 );

    wifi9_process(  );

    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "---- System Info ----\r\n" );
    log_printf( &logger, "---------------------\r\n" );

    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_FIRMWARE );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_MAC_ADDR );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_SERIAL_NUM );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_RADIO_VER );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_BOOTL_VER );
    Delay_ms( 500 );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_SYSTEM_HW_REV );
    
    Delay_ms( 5000 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "---- Start NETCAT app ----\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    
    log_printf( &logger, "> Reads the current Station status\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_WLAN_STATE_STA );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Set Station to ON status\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_WLAN_STATE_STA_ON );
    Delay_ms( 2000 );

    log_printf( &logger, "> Sets Station SSID and PASSWORD\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_WLAN_CFG_STA );
    Delay_ms( 4000 );
    
    log_printf( &logger, "> Turn OFF - Netcat module\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_STATE_OFF );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Turn ON - Netcat module\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_STATE_ON );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Sets the Netcat module as a server with port 1234\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_CFG_SERVER );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Excludes Netcat authentication\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_SET_NETCAT_AUTH_OFF );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Gets the current received IP address\r\n" );
    wifi9_send_command( &wifi9, WIFI9_CMD_GET_NET_CFG_STA );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> At the moment, a netcat server at port 1234 has been built\r\n" );
    log_printf( &logger, "> The module is transferred to BIN-UART - for data collection\r\n" );

    wifi9_select_uart( &wifi9, WIFI9_SELECT_BIN_UART );
    log_printf( &logger, "test" );
    Delay_ms( 5000 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    wifi9_process(  );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Wifi9

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
