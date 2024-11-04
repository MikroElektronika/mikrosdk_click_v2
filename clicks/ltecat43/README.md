\mainpage Main Page

---
# LTE Cat.4 3 Click

> LTE Cat.4 3 Click is a compact add-on board representing a multi-band and multi-mode solution, offering universal connectivity and reliable performance. This board features the LARA-L6004D-01B, an LTE Cat 4 module in the smallest form factor from u-blox. The module supports an LTE Cat 4 FDD and an LTE Cat 4 TDD radio access technology (RAT), with a 3G UMTS/HSPA and 2G GSM/GPRS/EGPRS fallback. It is an ideal solution for global and multi-regional coverage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat43_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-cat4-3-click-data)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LTE Cat.4 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE Cat.4 3 Click driver.

#### Standard key functions :

- `ltecat43_cfg_setup` Config Object Initialization function.
```c
void ltecat43_cfg_setup ( ltecat43_cfg_t *cfg );
```

- `ltecat43_init` Initialization function.
```c
err_t ltecat43_init ( ltecat43_t *ctx, ltecat43_cfg_t *cfg );
```

#### Example key functions :

- `ltecat43_set_power_state` This function sets a desired power state by toggling PWR pin with a specific time for high state.
```c
void ltecat43_set_power_state ( ltecat43_t *ctx, uint8_t state );
```

- `ltecat43_set_sim_apn` This function sets APN for sim card.
```c
void ltecat43_set_sim_apn ( ltecat43_t *ctx, char *sim_apn );
```

- `ltecat43_send_sms_text` This function sends text message to a phone number.
```c
void ltecat43_send_sms_text ( ltecat43_t *ctx, char *phone_number, char *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, restarts the module and tests the communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat43_cfg_t ltecat43_cfg;  /**< Click config object. */

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
    ltecat43_cfg_setup( &ltecat43_cfg );
    LTECAT43_MAP_MIKROBUS( ltecat43_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat43_init( &ltecat43, &ltecat43_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    ltecat43_set_power_state ( &ltecat43, LTECAT43_POWER_STATE_ON );

    ltecat43_process( );
    ltecat43_clear_app_buf( );

    // Check communication
    ltecat43_send_cmd( &ltecat43, LTECAT43_CMD_AT );
    error_flag = ltecat43_rsp_check( );
    ltecat43_error_check( error_flag );

    // Restart device
    #define RESTART_DEVICE "1,1"
    ltecat43_send_cmd_par( &ltecat43, LTECAT43_CMD_CFUN, RESTART_DEVICE );
    error_flag = ltecat43_rsp_check( );
    ltecat43_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = LTECAT43_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - LTECAT43_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - LTECAT43_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - LTECAT43_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - LTECAT43_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case LTECAT43_CONFIGURE_FOR_NETWORK:
        {
            if ( LTECAT43_OK == ltecat43_cfg_for_network( ) )
            {
                example_state = LTECAT43_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTECAT43_WAIT_FOR_CONNECTION:
        {
            if ( LTECAT43_OK == ltecat43_check_connection( ) )
            {
                example_state = LTECAT43_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTECAT43_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTECAT43_OK == ltecat43_cfg_for_example( ) )
            {
                example_state = LTECAT43_EXAMPLE;
            }
            break;
        }
        case LTECAT43_EXAMPLE:
        {
            ltecat43_example( );
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
- Click.LTECat43

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
