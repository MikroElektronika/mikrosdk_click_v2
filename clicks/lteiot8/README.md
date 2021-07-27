\mainpage Main Page

---
# LTE IoT 8 click

> LTE IoT 8 Click is a compact add-on board that contains a low-power solution for LTE and NB-IoT connectivity. This board features the SKY66430-11, a multi-band multi-chip System-in-Package (SiP) supporting 5G Massive IoT (LTE-M/NB-IoT) platforms from Skyworks Solutions and Sequans Communications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lte_iot_8_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-8-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Apr 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LTEIoT8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTEIoT8 Click driver.

#### Standard key functions :

- `lteiot8_cfg_setup` Config Object Initialization function.
```c
void lteiot8_cfg_setup ( lteiot8_cfg_t *cfg );
```

- `lteiot8_init` Initialization function.
```c
err_t lteiot8_init ( lteiot8_t *ctx, lteiot8_cfg_t *cfg );
```

- `lteiot8_default_cfg` Click Default Configuration function.
```c
err_t lteiot8_default_cfg ( lteiot8_t *ctx );
```

#### Example key functions :

- `lteiot8_send_cmd` Send command function.
```c
void lteiot8_send_cmd ( lteiot8_t *ctx, char *cmd );
```

- `lteiot8_set_sim_apn` Set SIM APN.
```c
void lteiot8_set_sim_apn ( lteiot8_t *ctx, char *sim_apn );
```

- `lteiot8_send_text_message` Send SMS message to number in text mode.
```c
void lteiot8_send_text_message ( lteiot8_t *ctx, char *phone_number, char *message_content );
```

## Example Description

> Application example shows device capability to connect 
network and send SMS messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module and test communication.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot8_cfg_t lteiot8_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    lteiot8_cfg_setup( &lteiot8_cfg );
    LTEIOT8_MAP_MIKROBUS( lteiot8_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot8_init( &lteiot8, &lteiot8_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    lteiot8_process();
    lteiot8_clear_app_buf(); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    lteiot8_default_cfg ( &lteiot8 );
    while ( 0 == strstr( app_buf, LTEIOT8_RSP_SYSTART ) )
    {
        lteiot8_process();
    }
    
    //Check communication
    lteiot8_send_cmd( &lteiot8, "AT" );
    error_flag = lteiot8_rsp_check();
    lteiot8_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTEIOT8_CONFIGURE_FOR_CONNECTION;
}

```

### Application Task

> Application taks is split in few stages:
 - LTEIOT8_CONFIGURE_FOR_CONNECTION: 
> Sets configuration to device to be able to connect to newtork.
 - LTEIOT8_WAIT_FOR_CONNECTION: 
> Checks device response untill device sends information 
that it is connected to network.
 - LTEIOT8_CHECK_CONNECTION:
> Checks device connection status parameters.
 - LTEIOT8_CONFIGURE_FOR_MESSAGES:
> Sets configuration to device to send SMS messages.
 - LTEIOT8_MESSAGES:
> Sends message in selected mode (PDU/TXT).

```c

void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTEIOT8_CONFIGURE_FOR_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_configure_for_connection( ) )
            {
                example_state = LTEIOT8_WAIT_FOR_CONNECTION;
            }
            Delay_ms( 5000 );
            break;
        }
        case LTEIOT8_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_check_connection( ) )
            {
                example_state = LTEIOT8_CHECK_CONNECTION;
            }
            break;
        }
        case LTEIOT8_CHECK_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_check_connection_parameters( ) )
            {
                example_state = LTEIOT8_CONFIGURE_FOR_MESSAGES;
            }
            Delay_ms( 5000 );
            break;
        }
        case LTEIOT8_CONFIGURE_FOR_MESSAGES:
        {
            if ( LTEIOT8_OK == lteiot8_configure_for_meesages( ) )
            {
                example_state = LTEIOT8_MESSAGES;
            }
            Delay_ms( 5000 );
            break;
        }
        case LTEIOT8_MESSAGES:
        {
            lteiot8_send_meesage();
            Delay_ms( 10000 );
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
PHONE_NUMBER_TO_MESSAGE     "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
