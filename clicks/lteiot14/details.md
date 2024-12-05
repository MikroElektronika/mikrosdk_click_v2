
---
# LTE IoT 14 Click

> LTE IoT 14 Click is a compact add-on board designed for low-latency and low-throughput wireless data communication in IoT applications. This board features the SIM7090G, a multi-band LTE module from SIMCom, supporting Cat-M and Cat-NB communication modes and multi-constellation GNSS (GPS/GLONASS/Galileo/BeiDou) for global connectivity. This board features a UART interface for communication with the host MCU, a USB Type-C port for data transfer and firmware upgrades, as well as visual indicators for real-time network and power status. It also includes test points for easier debugging, dual SMA connectors for LTE and GNSS antennas, and a micro SIM card holder for flexible service provider selection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot14_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-iot-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LTE IoT 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE IoT 14 Click driver.

#### Standard key functions :

- `lteiot14_cfg_setup` Config Object Initialization function.
```c
void lteiot14_cfg_setup ( lteiot14_cfg_t *cfg );
```

- `lteiot14_init` Initialization function.
```c
err_t lteiot14_init ( lteiot14_t *ctx, lteiot14_cfg_t *cfg );
```

#### Example key functions :

- `lteiot14_set_sim_apn` This function sets APN for sim card.
```c
void lteiot14_set_sim_apn ( lteiot14_t *ctx, uint8_t *sim_apn );
```

- `lteiot14_send_sms_text` This function sends text message to a phone number.
```c
void lteiot14_send_sms_text ( lteiot14_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `lteiot14_send_cmd` This function sends a specified command to the Click module.
```c
void lteiot14_send_cmd ( lteiot14_t *ctx, uint8_t *cmd );
```

## Example Description

> Application example shows device capability of connecting to the network and
sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot14_cfg_t lteiot14_cfg;  /**< Click config object. */

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
    lteiot14_cfg_setup( &lteiot14_cfg );
    LTEIOT14_MAP_MIKROBUS( lteiot14_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot14_init( &lteiot14, &lteiot14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT14_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LTEIOT14_POWER_UP: 
   > Powers up the device, performs a device reset and reads system information.
 - LTEIOT14_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 - LTEIOT14_CHECK_CONNECTION:
   > Waits for the network registration indicated via CREG command and then checks the signal quality report (used only for SMS or TCP/UDP demo examples).
 - LTEIOT14_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTEIOT14_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTEIOT14_POWER_UP:
        {
            if ( LTEIOT14_OK == lteiot14_power_up( &lteiot14 ) )
            {
                app_state = LTEIOT14_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_CONFIG_CONNECTION:
        {
            if ( LTEIOT14_OK == lteiot14_config_connection( &lteiot14 ) )
            {
                app_state = LTEIOT14_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_CHECK_CONNECTION:
        {
            if ( LTEIOT14_OK == lteiot14_check_connection( &lteiot14 ) )
            {
                app_state = LTEIOT14_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_CONFIG_EXAMPLE:
        {
            if ( LTEIOT14_OK == lteiot14_config_example( &lteiot14 ) )
            {
                app_state = LTEIOT14_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_EXAMPLE:
        {
            lteiot14_example( &lteiot14 );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
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
- Click.LTEIoT14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
