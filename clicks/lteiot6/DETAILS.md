
---
# LTE IoT 6 click

LTE IoT 6 Click is a compact add-on board that contains an IoT module with worldwide coverage. This board features the SARA-R412M, a cellular module that offers multi-band data transmissions for Low Power Wide Area solutions in a compact form factor from u-Blox.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot6_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-6-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the lteiot6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for lteiot6 Click driver.

#### Standard key functions :

- `lteiot6_cfg_setup` Config Object Initialization function.
```c
void lteiot6_cfg_setup ( lteiot6_cfg_t *cfg );
```

- `lteiot6_init` Initialization function.
```c
lteiot6_RETVAL lteiot6_init ( lteiot6_t *ctx, lteiot6_cfg_t *cfg );
```

- `lteiot6_default_cfg` Click Default Configuration function.
```c
void lteiot6_default_cfg ( lteiot6_t *ctx );
```

#### Example key functions :

- `lteiot6_send_cmd` Send command function.
```c
void lteiot6_send_cmd ( lteiot6_t *ctx, char *cmd );
```

- `lteiot6_set_sim_apn` Set SIM APN.
```c
void lteiot6_set_sim_apn ( lteiot6_t *ctx, char *sim_apn );
```

- `lteiot6_send_sms_pdu` Send SMS message to number in pdu mode.
```c
err_t lteiot6_send_sms_pdu ( lteiot6_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

## Examples Description

> Application example shows device capability to connect 
network and send SMS messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module and test communication.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot6_cfg_t lteiot6_cfg;  /**< Click config object. */

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
    Delay_ms ( 1000 );
    log_info( &logger, " Application Init " );
    Delay_ms ( 1000 );

    // Click initialization.
    lteiot6_cfg_setup( &lteiot6_cfg );
    LTEIOT6_MAP_MIKROBUS( lteiot6_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot6_init( &lteiot6, &lteiot6_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    lteiot6_process();
    lteiot6_clear_app_buf(); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    lteiot6_reset( &lteiot6 );
    lteiot6_power_on( &lteiot6 );
    
    //Check communication
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_AT );
    error_flag = lteiot6_rsp_check();
    lteiot6_error_check( error_flag );
    
    //Check fw version
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_ATI );
    error_flag = lteiot6_rsp_check();
    lteiot6_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTEIOT6_CONFIGURE_FOR_CONNECTION;
}
  
```

### Application Task

> Application taks is split in few stages:
 - LTEIOT6_CONFIGURE_FOR_CONNECTION: 
>Sets configuration to device to be able to connect to newtork.

 - LTEIOT6_WAIT_FOR_CONNECTION: 
>Checks device response untill device sends information 
that it is connected to network.

 - LTEIOT6_CHECK_CONNECTION:
>Checks device connection status parameters.

 - LTEIOT6_CONFIGURE_FOR_MESSAGES:
>Sets configuration to device to send SMS messages.

 - LTEIOT6_MESSAGES:
>Sends message in selected mode (PDU/TXT).

```c

void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTEIOT6_CONFIGURE_FOR_CONNECTION:
        {
            if ( LTEIOT6_OK == lteiot6_configure_for_connection( ) )
            {
                example_state = LTEIOT6_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT6_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT6_OK == lteiot6_check_connection( ) )
            {
                example_state = LTEIOT6_CHECK_CONNECTION;
            }
            break;
        }
        case LTEIOT6_CHECK_CONNECTION:
        {
            Delay_ms ( 1000 );
            if ( LTEIOT6_OK == lteiot6_check_connection_parameters( ) )
            {
                example_state = LTEIOT6_CONFIGURE_FOR_MESSAGES;
            }
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT6_CONFIGURE_FOR_MESSAGES:
        {
            if ( LTEIOT6_OK == lteiot6_configure_for_meesages( ) )
            {
                example_state = LTEIOT6_MESSAGES;
            }
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT6_MESSAGES:
        {
            lteiot6_send_meesage();
            Delay_ms ( 1000 );
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

> In order for the example to work, user needs to set the phone number to which he wants 
to send an SMS, and also will need to set an APN and SMSC of entered SIM card.
Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>>E.g. 
SIM_APN                     "vip.iot",
SMSC_ADDRESS_CSCA           "\"+381999999\",145",
SMSC_ADDRESS_PDU            "+381999999\" ,
PHONE_NUMBER_TO_MESSAGE     "+381659999999",
  PHONE_NUMBER_TO_MESSAGE "999999999"

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
