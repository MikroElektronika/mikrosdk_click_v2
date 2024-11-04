\mainpage Main Page

---
# GSM 5 Click

> GSM 5 Click is a compact add-on board representing a compact GSM cellular network communication solution. This board features the SARA-G450, a GSM/GPRS quad-band cellular module certified and approved by the main regulatory bodies and operators from u-blox. It features class 12 GSM/GPRS connectivity in the popular u-blox SARA form factor and comes with a comprehensive feature set, including an extensive set of internet protocols designed to provide fully integrated access to u-blox GNSS positioning with embedded A-GPS (AssistNow Online and AssistNow Offline) functionality. Besides a data rate up to 85.6 kbps and an advanced jamming detection feature, this board also offers a high-quality integrated audio interface allowing voice communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsm5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gsm-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART type


# Software Support

We provide a library for the GSM 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GSM 5 Click driver.

#### Standard key functions :

- `gsm5_cfg_setup` Config Object Initialization function.
```c
void gsm5_cfg_setup ( gsm5_cfg_t *cfg );
```

- `gsm5_init` Initialization function.
```c
err_t gsm5_init ( gsm5_t *ctx, gsm5_cfg_t *cfg );
```

#### Example key functions :

- `gsm5_send_cmd` This function sends a specified command to the Click module.
```c
void gsm5_send_cmd ( gsm5_t *ctx, char *cmd );
```

- `gsm5_set_sim_apn` This function sets APN for sim card.
```c
void gsm5_set_sim_apn ( gsm5_t *ctx, char *sim_apn );
```

- `gsm5_send_sms_text` This function sends text message to a phone number.
```c
void gsm5_send_sms_text ( gsm5_t *ctx, char *phone_number, char *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, wakes the module up and tests the communication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gsm5_cfg_t gsm5_cfg;  /**< Click config object. */

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
    gsm5_cfg_setup( &gsm5_cfg );
    GSM5_MAP_MIKROBUS( gsm5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gsm5_init( &gsm5, &gsm5_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    gsm5_module_power_on ( &gsm5 );
    
    gsm5_process( );
    gsm5_clear_app_buf( ); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    // Check communication
    gsm5_send_cmd( &gsm5, GSM5_CMD_AT );
    error_flag = gsm5_rsp_check( );
    gsm5_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = GSM5_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - GSM5_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - GSM5_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - GSM5_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - GSM5_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case GSM5_CONFIGURE_FOR_NETWORK:
        {
            if ( GSM5_OK == gsm5_configure_for_network( ) )
            {
                example_state = GSM5_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case GSM5_WAIT_FOR_CONNECTION:
        {
            if ( GSM5_OK == gsm5_check_connection( ) )
            {
                example_state = GSM5_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case GSM5_CONFIGURE_FOR_EXAMPLE:
        {
            if ( GSM5_OK == gsm5_configure_for_example( ) )
            {
                example_state = GSM5_EXAMPLE;
            }
            break;
        }
        case GSM5_EXAMPLE:
        {
            gsm5_example( );
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
- Click.GSM5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
