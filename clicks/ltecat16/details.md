
---
# LTE Cat.1 6 Click

> LTE Cat.1 6 Click is a compact add-on board with global coverage for wireless communication over LTE, UMTS, and GSM networks. This board features the SIM7600SA, a LTE Cat 1 module from SIMCom, supporting LTE-TDD/LTE-FDD/HSPA+/GSM/GPRS/EDGE communication modes. Key features include multi-band LTE support, auxiliary diversity, and optional multi-constellation GNSS. It also integrates USB Type C for power and data transfer, a micro SIM card holder, three LED indicators for network status, power, custom notifications, AT command communication, and firmware upgrades.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat16_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-cat1-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LTE Cat.1 6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE Cat.1 6 Click driver.

#### Standard key functions :

- `ltecat16_cfg_setup` Config Object Initialization function.
```c
void ltecat16_cfg_setup ( ltecat16_cfg_t *cfg );
```

- `ltecat16_init` Initialization function.
```c
err_t ltecat16_init ( ltecat16_t *ctx, ltecat16_cfg_t *cfg );
```

#### Example key functions :

- `ltecat16_set_sim_apn` This function sets APN for sim card.
```c
void ltecat16_set_sim_apn ( ltecat16_t *ctx, uint8_t *sim_apn );
```

- `ltecat16_send_sms_text` This function sends text message to a phone number.
```c
void ltecat16_send_sms_text ( ltecat16_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `ltecat16_send_cmd` This function sends a specified command to the Click module.
```c
void ltecat16_send_cmd ( ltecat16_t *ctx, uint8_t *cmd );
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
    ltecat16_cfg_t ltecat16_cfg;  /**< Click config object. */

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
    ltecat16_cfg_setup( &ltecat16_cfg );
    LTECAT16_MAP_MIKROBUS( ltecat16_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat16_init( &ltecat16, &ltecat16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTECAT16_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LTECAT16_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LTECAT16_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network.
 - LTECAT16_CHECK_CONNECTION:
   > Waits for the network registration indicated via CREG command and then checks the signal quality report.
 - LTECAT16_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTECAT16_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTECAT16_POWER_UP:
        {
            if ( LTECAT16_OK == ltecat16_power_up( &ltecat16 ) )
            {
                app_state = LTECAT16_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT16_CONFIG_CONNECTION:
        {
            if ( LTECAT16_OK == ltecat16_config_connection( &ltecat16 ) )
            {
                app_state = LTECAT16_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT16_CHECK_CONNECTION:
        {
            if ( LTECAT16_OK == ltecat16_check_connection( &ltecat16 ) )
            {
                app_state = LTECAT16_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT16_CONFIG_EXAMPLE:
        {
            if ( LTECAT16_OK == ltecat16_config_example( &ltecat16 ) )
            {
                app_state = LTECAT16_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT16_EXAMPLE:
        {
            ltecat16_example( &ltecat16 );
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
- Click.LTECat16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
