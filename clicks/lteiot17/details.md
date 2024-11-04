
---
# LTE IoT 17 Click

> LTE IoT 17 Click is a compact add-on board designed for low-power, long-range cellular communication in IoT applications. This board features the SIM7070E, a multi-band LTE module from SIMCom that supports the European/Australian region's Cat-M, Cat-NB, and GSM modes. Key features include a maximum 589kbps downlink and 1.1Mbps uplink rate, support of multiple LTE bands and optional multi-constellation GNSS, a micro SIM card holder, AT command communication, firmware upgrades, power management options, and visual indicators for network and power status.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-iot-17-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LTE IoT 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE IoT 17 Click driver.

#### Standard key functions :

- `lteiot17_cfg_setup` Config Object Initialization function.
```c
void lteiot17_cfg_setup ( lteiot17_cfg_t *cfg );
```

- `lteiot17_init` Initialization function.
```c
err_t lteiot17_init ( lteiot17_t *ctx, lteiot17_cfg_t *cfg );
```

#### Example key functions :

- `lteiot17_set_sim_apn` This function sets APN for sim card.
```c
void lteiot17_set_sim_apn ( lteiot17_t *ctx, uint8_t *sim_apn );
```

- `lteiot17_send_sms_text` This function sends text message to a phone number.
```c
void lteiot17_send_sms_text ( lteiot17_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `lteiot17_send_cmd` This function sends a specified command to the Click module.
```c
void lteiot17_send_cmd ( lteiot17_t *ctx, uint8_t *cmd );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot17_cfg_t lteiot17_cfg;  /**< Click config object. */

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
    lteiot17_cfg_setup( &lteiot17_cfg );
    LTEIOT17_MAP_MIKROBUS( lteiot17_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot17_init( &lteiot17, &lteiot17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT17_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LTEIOT17_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LTEIOT17_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network.
 - LTEIOT17_CHECK_CONNECTION:
   > Waits for the network registration indicated via CREG command and then checks the signal quality report.
 - LTEIOT17_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTEIOT17_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTEIOT17_POWER_UP:
        {
            if ( LTEIOT17_OK == lteiot17_power_up( &lteiot17 ) )
            {
                app_state = LTEIOT17_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_CONFIG_CONNECTION:
        {
            if ( LTEIOT17_OK == lteiot17_config_connection( &lteiot17 ) )
            {
                app_state = LTEIOT17_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_CHECK_CONNECTION:
        {
            if ( LTEIOT17_OK == lteiot17_check_connection( &lteiot17 ) )
            {
                app_state = LTEIOT17_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_CONFIG_EXAMPLE:
        {
            if ( LTEIOT17_OK == lteiot17_config_example( &lteiot17 ) )
            {
                app_state = LTEIOT17_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT17_EXAMPLE:
        {
            lteiot17_example( &lteiot17 );
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
- Click.LTEIoT17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
