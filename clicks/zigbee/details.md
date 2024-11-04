
---
# ZigBee Click

> ZigBee Click is a compact add-on board that contains a fully integrated Zigbee transceiver with a 32-bit ARM® Cortex M3TM microprocessor, Flash and RAM memory, and peripherals. This board features the ETRX357, 2.4 GHz Zigbee Radio module from Silicon Labs, which has been designed to be easily integrated and to provide a fast, simple, and low-cost wireless mesh networking interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/zigbee_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/zigbee-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : UART type


# Software Support

We provide a library for the ZigBee Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ZigBee Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This is an example that demonstrates the use of the ZigBee Click board.

**The demo application is composed of two sections :**

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


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ZigBee

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
