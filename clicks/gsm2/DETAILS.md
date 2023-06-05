
---
# GSM 2 click

> GSM2 click is a compact quad-band GSM cellular network communication solution, featuring the GSM/GPRS Quectel M95. This module features a full set of options for the cellular networking and communication, such as the network status indication, jamming detection, embedded internet protocols, including TCP/IP, UDP, FTP, PPP, HTTP, SMTP, full GPRS multislot class 12 implementation, it is fully compliant to GSM Phase 2/2+, and more. Data communication speed is rated up to 85.6 kbps for both uplink and downlink connection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsm2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gsm-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type


# Software Support

We provide a library for the GSM2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GSM2 Click driver.

#### Standard key functions :

- `gsm2_cfg_setup` Config Object Initialization function.
```c
void gsm2_cfg_setup ( gsm2_cfg_t *cfg );
```

- `gsm2_init` Initialization function.
```c
err_t gsm2_init ( gsm2_t *ctx, gsm2_cfg_t *cfg );
```

#### Example key functions :

- `gsm2_set_sim_apn` This function sets APN for sim card.
```c
void gsm2_set_sim_apn ( gsm2_t *ctx, uint8_t *sim_apn );
```

- `gsm2_send_sms_text` This function sends text message to a phone number.
```c
void gsm2_send_sms_text ( gsm2_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `gsm2_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t gsm2_send_sms_pdu ( gsm2_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gsm2_cfg_t gsm2_cfg;  /**< Click config object. */

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
    gsm2_cfg_setup( &gsm2_cfg );
    GSM2_MAP_MIKROBUS( gsm2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gsm2_init( &gsm2, &gsm2_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    gsm2_process( );
    gsm2_clear_app_buf( );

    // Check communication
    gsm2_send_cmd( &gsm2, GSM2_CMD_AT );
    error_flag = gsm2_rsp_check( GSM2_RSP_OK );
    gsm2_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    gsm2_send_cmd_with_par( &gsm2, GSM2_CMD_CFUN, RESTART_DEVICE );
    error_flag = gsm2_rsp_check( GSM2_RSP_OK );
    gsm2_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = GSM2_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - GSM2_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - GSM2_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - GSM2_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - GSM2_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c

void application_task ( void ) 
{
    switch ( example_state )
    {
        case GSM2_CONFIGURE_FOR_NETWORK:
        {
            if ( GSM2_OK == gsm2_configure_for_network( ) )
            {
                example_state = GSM2_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case GSM2_WAIT_FOR_CONNECTION:
        {
            if ( GSM2_OK == gsm2_check_connection( ) )
            {
                example_state = GSM2_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case GSM2_CONFIGURE_FOR_EXAMPLE:
        {
            if ( GSM2_OK == gsm2_configure_for_example( ) )
            {
                example_state = GSM2_EXAMPLE;
            }
            break;
        }
        case GSM2_EXAMPLE:
        {
            gsm2_example( );
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
- Click.GSM2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
