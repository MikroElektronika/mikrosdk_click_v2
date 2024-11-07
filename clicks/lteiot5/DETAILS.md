
---
# LTE IoT 5 Click

> LTE IoT 5 Click is an add-on board with a compact and cost-effective secure-cloud multi-band solution designed for IoT applications. This board features the SARA-R510M8S, a cellular module that supports LTE Cat M1/Cat NB2 bands with integrated high-performance standard precision M8 GNSS receiver for global position acquisition from u-Blox. Equipped with familiar AT commands set over the UART interface, USB interface, and Network and Status indicators this low power size-optimized solution, specifically designed for IoT, also provides over-the-air firmware updates, end-to-end trusted domain security, and u-Blox’s leading GNSS technology.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-iot-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LTE IoT 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE IoT 5 Click driver.

#### Standard key functions :

- `lteiot5_cfg_setup` Config Object Initialization function.
```c
void lteiot5_cfg_setup ( lteiot5_cfg_t *cfg );
```

- `lteiot5_init` Initialization function.
```c
err_t lteiot5_init ( lteiot5_t *ctx, lteiot5_cfg_t *cfg );
```

#### Example key functions :

- `lteiot5_set_sim_apn` This function sets APN for sim card.
```c
void lteiot5_set_sim_apn ( lteiot5_t *ctx, uint8_t *sim_apn );
```

- `lteiot5_send_sms_text` This function sends text message to a phone number.
```c
void lteiot5_send_sms_text ( lteiot5_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `lteiot5_cmd_set` This function sets a value to a specified command of the Click module.
```c
void lteiot5_cmd_set ( lteiot5_t *ctx, uint8_t *cmd, uint8_t *value );
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
    lteiot5_cfg_t lteiot5_cfg;  /**< Click config object. */

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
    lteiot5_cfg_setup( &lteiot5_cfg );
    LTEIOT5_MAP_MIKROBUS( lteiot5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot5_init( &lteiot5, &lteiot5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT5_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LTEIOT5_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LTEIOT5_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 - LTEIOT5_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report (used only for SMS or TCP/UDP demo examples).
 - LTEIOT5_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTEIOT5_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTEIOT5_POWER_UP:
        {
            if ( LTEIOT5_OK == lteiot5_power_up( &lteiot5 ) )
            {
                app_state = LTEIOT5_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_CONFIG_CONNECTION:
        {
            if ( LTEIOT5_OK == lteiot5_config_connection( &lteiot5 ) )
            {
                app_state = LTEIOT5_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_CHECK_CONNECTION:
        {
            if ( LTEIOT5_OK == lteiot5_check_connection( &lteiot5 ) )
            {
                app_state = LTEIOT5_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_CONFIG_EXAMPLE:
        {
            if ( LTEIOT5_OK == lteiot5_config_example( &lteiot5 ) )
            {
                app_state = LTEIOT5_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT5_EXAMPLE:
        {
            lteiot5_example( &lteiot5 );
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
Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER.
> > Example: 
> > - SIM_APN "internet"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
