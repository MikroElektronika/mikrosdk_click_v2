\mainpage Main Page

---
# NB IoT 4 Click

> NB IoT 4 Click is a compact add-on board that contains a cellular IoT-based module with integrated eSIM for global data connectivity. This board features the C1-RM, a three-band NB-IoT, IoT/2G wireless communication module supporting Band 3, 5, and 8 mainly applied to low power data transmission service from Cavli Wireless.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nbiot_4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/nb-iot-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : UART type


# Software Support

We provide a library for the NBIOT4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NBIOT4 Click driver.

#### Standard key functions :

- `nbiot4_cfg_setup` Config Object Initialization function.
```c
void nbiot4_cfg_setup ( nbiot4_cfg_t *cfg );
```

- `nbiot4_init` Initialization function.
```c
err_t nbiot4_init ( nbiot4_t *ctx, nbiot4_cfg_t *cfg );
```

#### Example key functions :

- `nbiot4_set_sim_apn` This function sets APN for sim card.
```c
void nbiot4_set_sim_apn ( nbiot4_t *ctx, uint8_t *sim_apn );
```

- `nbiot4_send_sms_text` This function sends text message to a phone number.
```c
void nbiot4_send_sms_text ( nbiot4_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `nbiot4_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t nbiot4_send_sms_pdu ( nbiot4_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.

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

    // Click initialization.
    nbiot4_cfg_setup( &nbiot4_cfg );
    NBIOT4_MAP_MIKROBUS( nbiot4_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot4_init( &nbiot4, &nbiot4_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    nbiot4_process( );
    nbiot4_clear_app_buf( );

    // Check communication
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_AT );
    error_flag = nbiot4_rsp_check( NBIOT4_RSP_OK );
    nbiot4_error_check( error_flag );
    
    // Enable command echo
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_ATE1 );
    error_flag = nbiot4_rsp_check( NBIOT4_RSP_OK );
    nbiot4_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    nbiot4_send_cmd_with_par( &nbiot4, NBIOT4_CMD_CFUN, RESTART_DEVICE );
    error_flag = nbiot4_rsp_check( NBIOT4_RSP_OK );
    nbiot4_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = NBIOT4_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - NBIOT4_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - NBIOT4_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CEREG URC event and then checks the connection status.
 - NBIOT4_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - NBIOT4_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c

void application_task ( void ) 
{
    switch ( example_state )
    {
        case NBIOT4_CONFIGURE_FOR_NETWORK:
        {
            if ( NBIOT4_OK == nbiot4_configure_for_network( ) )
            {
                example_state = NBIOT4_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case NBIOT4_WAIT_FOR_CONNECTION:
        {
            if ( NBIOT4_OK == nbiot4_check_connection( ) )
            {
                example_state = NBIOT4_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case NBIOT4_CONFIGURE_FOR_EXAMPLE:
        {
            if ( NBIOT4_OK == nbiot4_configure_for_example( ) )
            {
                example_state = NBIOT4_EXAMPLE;
            }
            break;
        }
        case NBIOT4_EXAMPLE:
        {
            nbiot4_example( );
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
- Click.NBIoT4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
