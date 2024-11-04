\mainpage Main Page

---
# LTE IoT 7 Click

> LTE IoT 7 Click is an add-on board representing a secure-cloud multi-band solution designed for IoT applications. This board features the SARA-R422M8S, a multi-band LTE-M/NB-IoT/EGPRS multi-mode solution with integrated high-performance standard precision M8 GNSS receiver for global position acquisition from u-blox. Equipped with familiar AT commands set over the UART interface, USB interface, and Network and Status indicators, it also provides over-the-air firmware updates, end-to-end trusted domain security, and u-Blox’s leading GNSS technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-iot-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART type


# Software Support

We provide a library for the LTE IoT 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE IoT 7 Click driver.

#### Standard key functions :

- `lteiot7_cfg_setup` Config Object Initialization function.
```c
void lteiot7_cfg_setup ( lteiot7_cfg_t *cfg );
```

- `lteiot7_init` Initialization function.
```c
err_t lteiot7_init ( lteiot7_t *ctx, lteiot7_cfg_t *cfg );
```

- `lteiot7_default_cfg` Click Default Configuration function.
```c
err_t lteiot7_default_cfg ( lteiot7_t *ctx );
```

#### Example key functions :

- `lteiot7_set_sim_apn` This function sets APN for sim card.
```c
void lteiot7_set_sim_apn ( lteiot7_t *ctx, char *sim_apn );
```

- `lteiot7_send_sms_text` This function sends text message to a phone number.
```c
void lteiot7_send_sms_text ( lteiot7_t *ctx, char *phone_number, char *sms_text );
```

- `lteiot7_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t lteiot7_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, reboots the module which takes about 20 seconds and then tests the communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot7_cfg_t lteiot7_cfg;  /**< Click config object. */

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
    lteiot7_cfg_setup( &lteiot7_cfg );
    LTEIOT7_MAP_MIKROBUS( lteiot7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot7_init( &lteiot7, &lteiot7_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    lteiot7_set_power_state ( &lteiot7, LTEIOT7_POWER_STATE_REBOOT );
    
    lteiot7_process( );
    lteiot7_clear_app_buf( );
    app_buf_len = 0;
    app_buf_cnt = 0;

    // Check communication
    lteiot7_send_cmd( &lteiot7, LTEIOT7_CMD_AT );
    error_flag = lteiot7_rsp_check( );
    lteiot7_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = LTEIOT7_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - LTEIOT7_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network. (used only for SMS or TCP/UDP demo examples).
 - LTEIOT7_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status (used only for SMS or TCP/UDP demo examples).
 - LTEIOT7_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS depending on the selected demo example.
 - LTEIOT7_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case LTEIOT7_CONFIGURE_FOR_NETWORK:
        {
            if ( LTEIOT7_OK == lteiot7_configure_for_network( ) )
            {
                example_state = LTEIOT7_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT7_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT7_OK == lteiot7_check_connection( ) )
            {
                example_state = LTEIOT7_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTEIOT7_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTEIOT7_OK == lteiot7_configure_for_example( ) )
            {
                example_state = LTEIOT7_EXAMPLE;
            }
            break;
        }
        case LTEIOT7_EXAMPLE:
        {
            lteiot7_example( );
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
- Click.LTEIoT7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
