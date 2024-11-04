\mainpage Main Page

---
# LTE Cat.4 Click

> LTE Cat.4 Click (for Europe) is a compact add-on board made specially for 4G M2M and IoT applications in Europe. This board features the EG95EXGA-128-SGNS, an IoT/M2M-optimized LTE Cat.4 module that meets the 3GPP Release 11 standard from Quectel. It supports multiple wireless standards, including LTE-FDD, WCDMA, and GSM, ensuring broad network compatibility. Key features include multi-band LTE support (B1/B3/B7/B8/B20/B28), RX diversity for bands B1 and B8, and multi-constellation GNSS (GPS, GLONASS, BeiDou/Compass, Galileo, QZSS). It also integrates a 16-bit mono audio codec for voice functionality with support for CTIA standard headphones. Additionally, it offers a USB Type C connector for power and data transfer, AT command communication, and firmware upgrades.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-cat4-click-for-europe)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LTE Cat.4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE Cat.4 Click driver.

#### Standard key functions :

- `ltecat4_cfg_setup` Config Object Initialization function.
```c
void ltecat4_cfg_setup ( ltecat4_cfg_t *cfg );
```

- `ltecat4_init` Initialization function.
```c
err_t ltecat4_init ( ltecat4_t *ctx, ltecat4_cfg_t *cfg );
```

#### Example key functions :

- `ltecat4_set_sim_apn` This function sets APN for sim card.
```c
void ltecat4_set_sim_apn ( ltecat4_t *ctx, uint8_t *sim_apn );
```

- `ltecat4_send_sms_text` This function sends text message to a phone number.
```c
void ltecat4_send_sms_text ( ltecat4_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `ltecat4_send_cmd` This function sends a specified command to the Click module.
```c
void ltecat4_send_cmd ( ltecat4_t *ctx, uint8_t *cmd );
```

## Example Description

> Application example shows device capability of connecting to the network and
sending SMS or TCP/UDP messages, answering incoming calls, or retrieving data from GNSS using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat4_cfg_t ltecat4_cfg;  /**< Click config object. */

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
    ltecat4_cfg_setup( &ltecat4_cfg );
    LTECAT4_MAP_MIKROBUS( ltecat4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat4_init( &ltecat4, &ltecat4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTECAT4_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

```

### Application Task

> Application task is split in few stages:
 - LTECAT4_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - LTECAT4_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network (used only for SMS, CALL, or TCP/UDP demo examples).
 - LTECAT4_CHECK_CONNECTION:
   > Waits for the network registration indicated via CREG command and then checks the signal quality report (used only for SMS, CALL, or TCP/UDP demo examples).
 - LTECAT4_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTECAT4_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message, waits for incoming calls and answers it, or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTECAT4_POWER_UP:
        {
            if ( LTECAT4_OK == ltecat4_power_up( &ltecat4 ) )
            {
                app_state = LTECAT4_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_CONFIG_CONNECTION:
        {
            if ( LTECAT4_OK == ltecat4_config_connection( &ltecat4 ) )
            {
                app_state = LTECAT4_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_CHECK_CONNECTION:
        {
            if ( LTECAT4_OK == ltecat4_check_connection( &ltecat4 ) )
            {
                app_state = LTECAT4_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_CONFIG_EXAMPLE:
        {
            if ( LTECAT4_OK == ltecat4_config_example( &ltecat4 ) )
            {
                app_state = LTECAT4_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT4_EXAMPLE:
        {
            ltecat4_example( &ltecat4 );
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
- Click.LTECat4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
