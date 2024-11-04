\mainpage Main Page

---
# LTE IoT 3 Click

> LTE IoT 3 Click is a compact add-on board that contains a Low Power Wide Area (LPWA) Wireless IoT module that allows connections to the LTE CAT-M1, CAT NB1/2, and 2G networks. This board features the EXS82-W, LTE-IoT Wireless Module from Thales that offers a rich set of Internet protocols and industry-standard interfaces such as UART, USB, etc. Global IoT connectivity, integrated GNSS support, SMS support, extended coverage range, and reduced power consumption makes this single IoT module an excellent choice for device makers while ensuring worldwide reliability.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-iot-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LTE IoT 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE IoT 3 Click driver.

#### Standard key functions :

- `lteiot3_cfg_setup` Config Object Initialization function.
```c
void lteiot3_cfg_setup ( lteiot3_cfg_t *cfg );
```

- `lteiot3_init` Initialization function.
```c
err_t lteiot3_init ( lteiot3_t *ctx, lteiot3_cfg_t *cfg );
```

#### Example key functions :

- `lteiot3_set_sim_apn` This function sets APN for sim card.
```c
void lteiot3_set_sim_apn ( lteiot3_t *ctx, char *sim_apn );
```

- `lteiot3_send_sms_text` This function sends text message to a phone number.
```c
void lteiot3_send_sms_text ( lteiot3_t *ctx, char *phone_number, char *sms_text );
```

- `lteiot3_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t lteiot3_parse_gga ( char *rsp_buf, uint8_t gga_element, char *element_data );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot3_cfg_t lteiot3_cfg;  /**< Click config object. */

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
    lteiot3_cfg_setup( &lteiot3_cfg );
    LTEIOT3_MAP_MIKROBUS( lteiot3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot3_init( &lteiot3, &lteiot3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    lteiot3_process( );
    lteiot3_clear_app_buf( );

    // Check communication
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_AT );
    error_flag = lteiot3_rsp_check( LTEIOT3_RSP_OK );
    lteiot3_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    lteiot3_send_cmd_with_parameter( &lteiot3, LTEIOT3_CMD_CFUN, RESTART_DEVICE );
    error_flag = lteiot3_rsp_check( LTEIOT3_RSP_SYSSTART );
    lteiot3_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = LTEIOT3_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - LTEIOT3_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network. (used only for SMS or TCP/UDP demo examples).
 - LTEIOT3_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status (used only for SMS or TCP/UDP demo examples).
 - LTEIOT3_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS depending on the selected demo example.
 - LTEIOT3_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case LTEIOT3_CONFIGURE_FOR_NETWORK:
        {
            if ( LTEIOT3_OK == lteiot3_configure_for_network( ) )
            {
                example_state = LTEIOT3_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT3_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT3_OK == lteiot3_check_connection( ) )
            {
                example_state = LTEIOT3_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTEIOT3_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTEIOT3_OK == lteiot3_configure_for_example( ) )
            {
                example_state = LTEIOT3_EXAMPLE;
            }
            break;
        }
        case LTEIOT3_EXAMPLE:
        {
            lteiot3_example( );
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
- Click.LTEIoT3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
