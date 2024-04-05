\mainpage Main Page

---
# 4G LTE GNSS click

> 4G LTE&GNSS Click is a compact add-on board designed for advanced global tracking and telematics applications, enabling developers to build highly efficient and smaller solutions without compromising performance. This board features the LENA-R8, a multi-mode LTE Cat 1bis module from u-blox. It stands out for its compact size and extensive network compatibility. It supports 14 LTE bands, four GSM/GPRS bands for universal connectivity, and integrated u-blox GNSS for precise global tracking. The board facilitates seamless communication via UART and includes a USB interface for comprehensive device management and firmware updates.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4gltegnss_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4g-ltegnss-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2023.
- **Type**          : UART type


# Software Support

We provide a library for the 4G LTE GNSS Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 4G LTE GNSS Click driver.

#### Standard key functions :

- `c4gltegnss_cfg_setup` Config Object Initialization function.
```c
void c4gltegnss_cfg_setup ( c4gltegnss_cfg_t *cfg );
```

- `c4gltegnss_init` Initialization function.
```c
err_t c4gltegnss_init ( c4gltegnss_t *ctx, c4gltegnss_cfg_t *cfg );
```

#### Example key functions :

- `c4gltegnss_set_sim_apn` This function sets APN for sim card.
```c
void c4gltegnss_set_sim_apn ( c4gltegnss_t *ctx, uint8_t *sim_apn );
```

- `c4gltegnss_send_sms_text` This function sends text message to a phone number.
```c
void c4gltegnss_send_sms_text ( c4gltegnss_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `c4gltegnss_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t c4gltegnss_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, restarts the device, and after that tests the communication by sending "AT" command.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4gltegnss_cfg_t c4gltegnss_cfg;  /**< Click config object. */

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
    c4gltegnss_cfg_setup( &c4gltegnss_cfg );
    C4GLTEGNSS_MAP_MIKROBUS( c4gltegnss_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c4gltegnss_init( &c4gltegnss, &c4gltegnss_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    // Power cycle device
    c4gltegnss_set_power_state ( &c4gltegnss, C4GLTEGNSS_POWER_STATE_OFF );
    c4gltegnss_set_power_state ( &c4gltegnss, C4GLTEGNSS_POWER_STATE_ON );
    
    // Dummy write to activate AT commands interface
    c4gltegnss_send_cmd( &c4gltegnss, C4GLTEGNSS_CMD_AT );
    c4gltegnss_process( );
    c4gltegnss_clear_app_buf( );
    
    // Check communication
    c4gltegnss_send_cmd( &c4gltegnss, C4GLTEGNSS_CMD_AT );
    error_flag = c4gltegnss_rsp_check( C4GLTEGNSS_RSP_OK );
    c4gltegnss_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = C4GLTEGNSS_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - C4GLTEGNSS_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 - C4GLTEGNSS_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status (used only for SMS or TCP/UDP demo examples).
 - C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS depending on the selected demo example.
 - C4GLTEGNSS_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case C4GLTEGNSS_CONFIGURE_FOR_NETWORK:
        {
            if ( C4GLTEGNSS_OK == c4gltegnss_config_for_network( ) )
            {
                example_state = C4GLTEGNSS_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case C4GLTEGNSS_WAIT_FOR_CONNECTION:
        {
            if ( C4GLTEGNSS_OK == c4gltegnss_check_connection( ) )
            {
                example_state = C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case C4GLTEGNSS_CONFIGURE_FOR_EXAMPLE:
        {
            if ( C4GLTEGNSS_OK == c4gltegnss_config_for_example( ) )
            {
                example_state = C4GLTEGNSS_EXAMPLE;
            }
            break;
        }
        case C4GLTEGNSS_EXAMPLE:
        {
            c4gltegnss_example( );
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

> In order for the examples to work (except GNSS example), user needs to set the APN and SMSC (SMS PDU mode only)
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
- Click.4GLTEGNSS

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
