
---
# NB IoT 4 click

NB IoT 4 Click is a compact add-on board that contains a cellular IoT-based module with integrated eSIM for global data connectivity. This board features the C1-RM, a three-band NB-IoT, IoT/2G wireless communication module supporting Band 3, 5, and 8 mainly applied to low power data transmission service from Cavli Wireless.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nbiot_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nb-iot-4-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the NBIoT4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NBIoT4 Click driver.

#### Standard key functions :

- `nbiot4_cfg_setup` Config Object Initialization function.
```c
void nbiot4_cfg_setup ( nbiot4_cfg_t *cfg );
```

- `nbiot4_init` Initialization function.
```c
err_t nbiot4_init ( nbiot4_t *ctx, nbiot4_cfg_t *cfg );
```

- `nbiot4_default_cfg` Click Default Configuration function.
```c
err_t nbiot4_default_cfg ( nbiot4_t *ctx );
```

#### Example key functions :

- `nbiot4_send_cmd`  Send command function.
```c
void nbiot4_send_cmd ( nbiot4_t *ctx, char *cmd );
```

- `nbiot4_set_sim_apn` Set SIM APN.
```c
void nbiot4_set_sim_apn ( nbiot4_t *ctx, char *sim_apn );
```

- `nbiot4_send_text_message` Send SMS message to number in text mode.
```c
void nbiot4_send_text_message ( nbiot4_t *ctx, char *phone_number, char *message_content );
```

## Example Description

> Application example shows device capability to connect 
network and send SMS messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes UART communication modules and additional pins 
wait for powerup or restarts device. Test communication and 
read information from device.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot4_cfg_t nbiot4_cfg;  /**< Click config object. */

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
    Delay_ms( 500 );
    // Click initialization.

    nbiot4_cfg_setup( &nbiot4_cfg );
    NBIOT4_MAP_MIKROBUS( nbiot4_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot4_init( &nbiot4, &nbiot4_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    nbiot4_default_cfg( &nbiot4 );
    nbiot4_process( );
    nbiot4_clear_app_buf(  );
    
    log_info( &logger, "Power up" );
    nbiot4_restart_device( 5000 );
    
    //Check communication
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_AT );
    error_flag = nbiot4_rsp_check();
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Check revision
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_ATI );
    error_flag = nbiot4_rsp_check();
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    log_info( &logger, " Application Task " );
    example_state = NBIOT4_CONFIGURE_FOR_CONNECTION;
}

```

### Application Task

> First it confiures device for connection to network(sets 
extern sim, selected apn). It waits until device gets 
information that is connected to home network. Then 
checks connection parameters. After that it configures 
device for one type of sending message TEXT or PDU mode. 
In the end it sends SMS message to selected number.

```c

void application_task ( void ) 
{
    switch ( example_state )
    {
        case NBIOT4_CONFIGURE_FOR_CONNECTION:
        {
            if ( !nbiot4_configure_for_connection() )
                example_state++;
            break;
        }
        case NBIOT4_WAIT_FOR_CONNECTION:
        {
            nbiot4_wait_to_connect( );
            example_state++;
            break;
        }
        case NBIOT4_CHECK_CONNECTION:
        {
            if ( !nbiot4_check_connection() )
                example_state++;
            break;
        }
        case NBIOT4_CONFIGURE_FOR_SMS:
        {
            if ( !nbiot4_configure_for_sms() )
                example_state++;
            break;
        }
        case NBIOT4_MESSAGES:
        {
            nbiot4_send_meesage();
            break;
        }
        default:
        {
            log_error( &logger, " Unknown example state." );
            Delay_ms( 500 );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
