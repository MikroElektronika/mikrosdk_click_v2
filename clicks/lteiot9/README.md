\mainpage Main Page

---
# LTE IoT 9 Click

> LTE IoT 9 Click is a compact add-on board containing a cellular IoT Module that supports 3GPP Release 14 and all LTE bands.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lte_iot_9_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lte-iot-9-click)

---


#### Click library

- **Author**        : Luka FIlipovic
- **Date**          : Feb 2021.
- **Type**          : UART type


# Software Support

We provide a library for the LTEIoT9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTEIoT9 Click driver.

#### Standard key functions :

- `lteiot9_cfg_setup` Config Object Initialization function.
```c
void lteiot9_cfg_setup ( lteiot9_cfg_t *cfg );
```

- `lteiot9_init` Initialization function.
```c
LTEIOT9_RETVAL lteiot9_init ( lteiot9_t *ctx, lteiot9_cfg_t *cfg );
```

- `lteiot9_default_cfg` Click Default Configuration function.
```c
void lteiot9_default_cfg ( lteiot9_t *ctx );
```

#### Example key functions :

- `lteiot9_generic_read` Function reads a desired number of data bytes by using UART serial interface.
```c
err_t lteiot9_generic_read ( lteiot9_t *ctx, char *data_buf, uint16_t max_len );
```

- `lteiot9_send_cmd` Function sends the specified command to the Click module.
```c
void lteiot9_send_cmd ( lteiot9_t *ctx, char *cmd );
```

- `lteiot9_set_sim_apn` Function sets APN for sim card.
```c
void lteiot9_set_sim_apn ( lteiot9_t *ctx, char *sim_apn );
```

## Example Description

>  This application shows capability of LTE IoT 9 Click board.
 It connects to network with standard "AT" commands, then
 sends SMS whit SIM card, and then logs GNNS data.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module and checks
  communication and device version.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot9_cfg_t lteiot9_cfg;  /**< Click config object. */

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
    Delay_ms ( 1000 );

    // Click initialization.

    lteiot9_cfg_setup( &lteiot9_cfg );
    LTEIOT9_MAP_MIKROBUS( lteiot9_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot9_init( &lteiot9, &lteiot9_cfg );
    if ( init_flag == UART_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Power on device... " );
    lteiot9_default_cfg ( &lteiot9 );
    lteiot9_process(  );
    lteiot9_clear_app_buf(  );
    
    lteiot9_send_cmd_with_parameter( &lteiot9, LTEIOT9_CMD_CFUN, "1,1" );
    lteiot9_power_up_wait();    
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    //AT
    lteiot9_send_cmd( &lteiot9, LTEIOT9_CMD_AT );
    app_error_flag = lteiot9_rsp_check();
    lteiot9_error_check( app_error_flag );
    Delay_ms ( 500 );
    //ATI
    lteiot9_send_cmd( &lteiot9, LTEIOT9_CMD_ATI );
    app_error_flag = lteiot9_rsp_check();
    lteiot9_error_check( app_error_flag );
    Delay_ms ( 500 );

    app_connection_status = CONFIGURATION_FOR_NETWORK;
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

### Application Task

> Application taks is split in few stages:
>  - CONFIGURATION_FOR_NETWORK : Sets configuration to device to 
                                be able to connect to newtork.
>  - CHECK_NETWORK_CONNECTION  : Checks device connection status 
                                till device is connected to network.
>  - SENDING_SMS               : Sends SMS message to desired number in text mode.
  >- CONFIGURATION_FOR_GNSS    : Sets configuration to device to enable GNSS data.
>  - GNSS_DATA                 : Reads and parses data from device to 
                                get latitude, longitude and altitude from device

```c

void application_task ( void ) 
{    
    switch( app_connection_status )
    {
        case CONFIGURATION_FOR_NETWORK:
        {
            lteiot9_config_device_for_network( );
            break;
        }
        case CHECK_NETWORK_CONNECTION:
        {
            lteiot9_check_connection_to_network( );
            break;
        }
        case SENDING_SMS:
        {
            lteiot9_send_sms( );
            break;
        }
        case CONFIGURATION_FOR_GNSS:
        {
            lteiot9_config_device_for_gnss( );
            break;
        }
        case GNSS_DATA:
        {
            lteiot9_gnss_data();

            break;
        }
        default:
        {
            log_error( &logger, "Application status error!" );
            app_connection_status = CHECK_NETWORK_CONNECTION;
            Delay_ms ( 1000 );
            break;
        }
    }
}

```

## Note

> In order for the example to work, 
   user needs to set the phone number and sim apn to which he wants to send an SMS
>> Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
>>> E.g.
    SIM_APN "vip.mobile",
    PHONE_NUMBER_TO_MESSAGE "999999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
