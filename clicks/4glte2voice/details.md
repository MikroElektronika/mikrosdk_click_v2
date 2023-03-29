
---
# 4G LTE 2 Voice click

> 4G LTE 2 Click is a compact add-on board representing a secure-cloud multi-band solution offering universal connectivity and reliable performance. This board features the LARA-R6001, the world’s smallest LTE Cat 1 module with global coverage and a built-in MQTT client from u-blox, representing a data and voice solution. Equipped with familiar AT commands set over the UART interface, USB interface, and Network and Status indicators, the LARA-R6001 also has a comprehensive certification scheme and multi-band/multi-mode capabilities providing excellent flexibility alongside the support of voice/audio application.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4glte2voice_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4g-lte-2-click-voice)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : UART type


# Software Support

We provide a library for the 4G LTE 2 Voice Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 4G LTE 2 Voice Click driver.

#### Standard key functions :

- `c4glte2voice_cfg_setup` Config Object Initialization function.
```c
void c4glte2voice_cfg_setup ( c4glte2voice_cfg_t *cfg );
```

- `c4glte2voice_init` Initialization function.
```c
err_t c4glte2voice_init ( c4glte2voice_t *ctx, c4glte2voice_cfg_t *cfg );
```

#### Example key functions :

- `c4glte2voice_set_power_state` This function sets a desired power state by toggling PWR pin with a specific time for high state.
```c
void c4glte2voice_set_power_state ( c4glte2voice_t *ctx, uint8_t state );
```

- `c4glte2voice_set_sim_apn` This function sets APN for sim card.
```c
void c4glte2voice_set_sim_apn ( c4glte2voice_t *ctx, char *sim_apn );
```

- `c4glte2voice_send_sms_text` This function sends text message to a phone number.
```c
void c4glte2voice_send_sms_text ( c4glte2voice_t *ctx, char *phone_number, char *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, restarts the module and tests the communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4glte2voice_cfg_t c4glte2voice_cfg;  /**< Click config object. */

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
    c4glte2voice_cfg_setup( &c4glte2voice_cfg );
    C4GLTE2VOICE_MAP_MIKROBUS( c4glte2voice_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c4glte2voice_init( &c4glte2voice, &c4glte2voice_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    c4glte2voice_set_power_state ( &c4glte2voice, C4GLTE2VOICE_POWER_STATE_OFF );
    c4glte2voice_set_power_state ( &c4glte2voice, C4GLTE2VOICE_POWER_STATE_ON );
    c4glte2voice_process( );
    c4glte2voice_clear_app_buf( );
    app_buf_len = 0;
    app_buf_cnt = 0;

    // Check communication
    c4glte2voice_send_cmd( &c4glte2voice, C4GLTE2VOICE_CMD_AT );
    error_flag = c4glte2voice_rsp_check( );
    c4glte2voice_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = C4GLTE2VOICE_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - C4GLTE2VOICE_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - C4GLTE2VOICE_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - C4GLTE2VOICE_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - C4GLTE2VOICE_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case C4GLTE2VOICE_CONFIGURE_FOR_NETWORK:
        {
            if ( C4GLTE2VOICE_OK == c4glte2voice_configure_for_network( ) )
            {
                example_state = C4GLTE2VOICE_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case C4GLTE2VOICE_WAIT_FOR_CONNECTION:
        {
            if ( C4GLTE2VOICE_OK == c4glte2voice_check_connection( ) )
            {
                example_state = C4GLTE2VOICE_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case C4GLTE2VOICE_CONFIGURE_FOR_EXAMPLE:
        {
            if ( C4GLTE2VOICE_OK == c4glte2voice_configure_for_example( ) )
            {
                example_state = C4GLTE2VOICE_EXAMPLE;
            }
            break;
        }
        case C4GLTE2VOICE_EXAMPLE:
        {
            c4glte2voice_example( );
            break;
        }
        default:
        {
            log_error( &logger, " Example state." );
            break;
        }
    }
}
```

## Note

> In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only)
of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
> > Example: 
> > - SIM_APN "internet"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.4GLTE2Voice

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
