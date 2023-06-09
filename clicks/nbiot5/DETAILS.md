
---
# NB IoT 5 click

> NB IoT 5 Click is a compact add-on board suitable as narrow-band Internet of Things universal wireless communication solution. This board features the OT01-5, a high-performance NB-IoT module with ultra-low power consumption allowing battery life of about ten years from Notioni.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nb_iot_5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nb-iot-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : UART type


# Software Support

We provide a library for the NBIOT5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NBIOT5 Click driver.

#### Standard key functions :

- `nbiot5_cfg_setup` Config Object Initialization function.
```c
void nbiot5_cfg_setup ( nbiot5_cfg_t *cfg );
```

- `nbiot5_init` Initialization function.
```c
err_t nbiot5_init ( nbiot5_t *ctx, nbiot5_cfg_t *cfg );
```

#### Example key functions :

- `nbiot5_set_sim_apn` This function sets APN for sim card.
```c
void nbiot5_set_sim_apn ( nbiot5_t *ctx, uint8_t *sim_apn );
```

- `nbiot5_send_sms_text` This function sends text message to a phone number.
```c
void nbiot5_send_sms_text ( nbiot5_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `nbiot5_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t nbiot5_send_sms_pdu ( nbiot5_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
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
    nbiot5_cfg_t nbiot5_cfg;  /**< Click config object. */

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
    nbiot5_cfg_setup( &nbiot5_cfg );
    NBIOT5_MAP_MIKROBUS( nbiot5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot5_init( &nbiot5, &nbiot5_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    nbiot5_process( );
    nbiot5_clear_app_buf( );

    // Check communication
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_AT );
    error_flag = nbiot5_rsp_check( NBIOT5_RSP_OK );
    nbiot5_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    nbiot5_send_cmd_with_par( &nbiot5, NBIOT5_CMD_CFUN, RESTART_DEVICE );
    error_flag = nbiot5_rsp_check( NBIOT5_RSP_OK );
    nbiot5_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = NBIOT5_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Application task is split in few stages:
 - NBIOT5_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - NBIOT5_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CEREG URC event and then checks the connection status.
 - NBIOT5_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - NBIOT5_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c

void application_task ( void ) 
{
    switch ( example_state )
    {
        case NBIOT5_CONFIGURE_FOR_NETWORK:
        {
            if ( NBIOT5_OK == nbiot5_configure_for_network( ) )
            {
                example_state = NBIOT5_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case NBIOT5_WAIT_FOR_CONNECTION:
        {
            if ( NBIOT5_OK == nbiot5_check_connection( ) )
            {
                example_state = NBIOT5_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case NBIOT5_CONFIGURE_FOR_EXAMPLE:
        {
            if ( NBIOT5_OK == nbiot5_configure_for_example( ) )
            {
                example_state = NBIOT5_EXAMPLE;
            }
            break;
        }
        case NBIOT5_EXAMPLE:
        {
            nbiot5_example( );
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
> Make sure the JP2 is removed from the click board, otherwise, you will need to connect the USB so that the module can boot up successfully.


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
