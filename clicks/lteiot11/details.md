
---
# LTE IoT 11 click

> LTE IoT 11 Click is a compact add-on board with an optimized global coverage module, as it supports a comprehensive set of bands required for global deployment. This board features the TX62-W, a global MTC module from Thales. It delivers global LTE-M, NB-IoT (NB1 and NB2) connectivity from a single SKU, and it is the first Thales product to adopt a revolutionary “Things” footprint. Besides, it integrates an embedded GNSS multi-constellation, state-of-the-art secure services, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LTE IoT 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE IoT 11 Click driver.

#### Standard key functions :

- `lteiot11_cfg_setup` Config Object Initialization function.
```c
void lteiot11_cfg_setup ( lteiot11_cfg_t *cfg );
```

- `lteiot11_init` Initialization function.
```c
err_t lteiot11_init ( lteiot11_t *ctx, lteiot11_cfg_t *cfg );
```

#### Example key functions :

- `lteiot11_set_sim_apn` This function sets APN for sim card.
```c
void lteiot11_set_sim_apn ( lteiot11_t *ctx, char *sim_apn );
```

- `lteiot11_send_sms_text` This function sends text message to a phone number.
```c
void lteiot11_send_sms_text ( lteiot11_t *ctx, char *phone_number, char *sms_text );
```

- `lteiot11_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t lteiot11_parse_gga ( char *rsp_buf, uint8_t gga_element, char *element_data );
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
    lteiot11_cfg_t lteiot11_cfg;  /**< Click config object. */

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
    lteiot11_cfg_setup( &lteiot11_cfg );
    LTEIOT11_MAP_MIKROBUS( lteiot11_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot11_init( &lteiot11, &lteiot11_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    lteiot11_process( );
    lteiot11_clear_app_buf( );

    // Check communication
    lteiot11_send_cmd( &lteiot11, LTEIOT11_CMD_AT );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_OK );
    lteiot11_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    lteiot11_send_cmd_with_parameter( &lteiot11, LTEIOT11_CMD_CFUN, RESTART_DEVICE );
    error_flag = lteiot11_rsp_check( LTEIOT11_RSP_SYSSTART );
    lteiot11_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = LTEIOT11_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - LTEIOT11_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network. (used only for SMS or TCP/UDP demo examples).
 - LTEIOT11_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status (used only for SMS or TCP/UDP demo examples).
 - LTEIOT11_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS depending on the selected demo example.
 - LTEIOT11_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case LTEIOT11_CONFIGURE_FOR_NETWORK:
        {
            if ( LTEIOT11_OK == lteiot11_configure_for_network( ) )
            {
                example_state = LTEIOT11_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT11_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT11_OK == lteiot11_check_connection( ) )
            {
                example_state = LTEIOT11_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTEIOT11_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTEIOT11_OK == lteiot11_configure_for_example( ) )
            {
                example_state = LTEIOT11_EXAMPLE;
            }
            break;
        }
        case LTEIOT11_EXAMPLE:
        {
            lteiot11_example( );
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

> In order to establish communication with the module, some of the supported MCUs may require the UART RX line
to be pulled up additionally either with the external or internal weak pull-up resistor.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
