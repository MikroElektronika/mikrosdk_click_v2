
---
# LTE IoT 3 click

> LTE IoT 3 Click is a compact add-on board that contains a Low Power Wide Area (LPWA) Wireless IoT module that allows connections to the LTE CAT-M1, CAT NB1/2, and 2G networks. This board features the EXS82-W, LTE-IoT Wireless Module from Thales that offers a rich set of Internet protocols and industry-standard interfaces such as UART, USB, etc. Global IoT connectivity, integrated GNSS support, SMS support, extended coverage range, and reduced power consumption makes this single IoT module an excellent choice for device makers while ensuring worldwide reliability.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LTEIoT3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTEIoT3 Click driver.

#### Standard key functions :

- `lteiot3_cfg_setup` Config Object Initialization function.
```c
void lteiot3_cfg_setup ( lteiot3_cfg_t *cfg );
```

- `lteiot3_init` Initialization function.
```c
err_t lteiot3_init ( lteiot3_t *ctx, lteiot3_cfg_t *cfg );
```

- `lteiot3_default_cfg` Click Default Configuration function.
```c
err_t lteiot3_default_cfg ( lteiot3_t *ctx );
```

#### Example key functions :

- `lteiot3_send_cmd` Send command function.
```c
void lteiot3_send_cmd ( lteiot3_t *ctx, char *cmd );
```

- `lteiot3_send_cmd_check` Check the sent command.
```c
void lteiot3_send_cmd_check ( lteiot3_t *ctx, char *at_cmd_buf );
```

- `lteiot3_send_text_message` LTE IoT 3 send text message.
```c
void lteiot3_send_text_message ( lteiot3_t *ctx, char *phone_number, char *message_context );
```

## Example Description

> This example reads and processes data from LTE IoT 3 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module and checks communication and device version.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot3_cfg_t lteiot3_cfg;  /**< Click config object. */

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
    Delay_ms( 1000 );

    // Click initialization.

    lteiot3_cfg_setup( &lteiot3_cfg );
    LTEIOT3_MAP_MIKROBUS( lteiot3_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot3_init( &lteiot3, &lteiot3_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Power on device... " );
    lteiot3_default_cfg ( &lteiot3 );
    lteiot3_process( );
    lteiot3_clear_app_buf( );
    
    lteiot3_send_cmd_with_parameter( &lteiot3, LTEIOT3_CMD_CFUN, "1,1" );
    lteiot3_power_up_wait();    
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    //AT
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_AT );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
    //ATI
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_ATI );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );

    app_connection_status = CONFIGURATION_FOR_NETWORK;
    log_info( &logger, " Application Task " );
    Delay_ms( 2000 );
}

```

### Application Task

> Application taks is split in few stages:
>  - CONFIGURATION_FOR_NETWORK : Sets configuration to device to 
>                                be able to connect to newtork.
> 
>  - CHECK_NETWORK_CONNECTION  : Checks device connection status 
>                                till device is connected to network.
> 
>  - SENDING_SMS               : Sends SMS message to desired number in text mode.
> 
>  - CONFIGURATION_FOR_GNSS    : Sets configuration to device to enable GNSS data.
> 
>  - GNSS_DATA                 : Reads and parses data from device to 
>                                get latitude, longitude and altitude from device

```c

void application_task ( void ) 
{    
    switch( app_connection_status )
    {
        case CONFIGURATION_FOR_NETWORK:
        {
            lteiot3_config_device_for_network( );
            break;
        }
        case CHECK_NETWORK_CONNECTION:
        {
            lteiot3_check_connection_to_network( );
            break;
        }
        case SENDING_SMS:
        {
            lteiot3_send_sms( );
            break;
        }
        case CONFIGURATION_FOR_GNSS:
        {
            lteiot3_config_device_for_gnss( );
            break;
        }
        case GNSS_DATA:
        {
            lteiot3_gnss_data();

            break;
        }
        default:
        {
            log_error( &logger, "Application status error!" );
            app_connection_status = CHECK_NETWORK_CONNECTION;
            Delay_ms( 1000 );
            break;
        }
    }
}

```

## Note

> In order for the example to work, 
> user needs to set the phone number and sim apn to which he wants to send an SMS
> Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
> E.g. 
>  SIM_APN "vipmobile"
>  PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
