
---
# 3G SARA Click

3G SARA Click is a versatile cellular network communication solution, featuring the compact 3.75G UMTS/HSPA SARA U-201 modem from u-blox.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3gsara_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/3g-sara-click)

---


#### Click library 

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type


# Software Support

We provide a library for the 3gSara Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 3gSara Click driver.

#### Standard key functions :

- `c3gsara_cfg_setup` Config Object Initialization function.
```c
void c3gsara_cfg_setup ( c3gsara_cfg_t *cfg );
```

- `c3gsara_init` Initialization function.
```c
err_t c3gsara_init ( c3gsara_t *ctx, c3gsara_cfg_t *cfg );
```

#### Example key functions :

- `c3gsara_set_sim_apn` This function sets APN for sim card.
```c
void c3gsara_set_sim_apn ( c3gsara_t *ctx, uint8_t *sim_apn );
```

- `c3gsara_send_sms_text` This function sends text message to a phone number.
```c
void c3gsara_send_sms_text ( c3gsara_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `c3gsara_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t c3gsara_send_sms_pdu ( c3gsara_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
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
    c3gsara_cfg_t c3gsara_cfg;  /**< Click config object. */

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
    c3gsara_cfg_setup( &c3gsara_cfg );
    C3GSARA_MAP_MIKROBUS( c3gsara_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c3gsara_init( &c3gsara, &c3gsara_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    c3gsara_set_power_state ( &c3gsara, C3GSARA_POWER_STATE_ON );
    
    c3gsara_process( );
    c3gsara_clear_app_buf( );

    // Check communication
    c3gsara_send_cmd( &c3gsara, C3GSARA_CMD_AT );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    c3gsara_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    c3gsara_send_cmd_with_par( &c3gsara, C3GSARA_CMD_CFUN, RESTART_DEVICE );
    error_flag = c3gsara_rsp_check( C3GSARA_RSP_OK );
    c3gsara_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = C3GSARA_CONFIGURE_FOR_NETWORK;
}
  
```

### Application Task

> Application task is split in few stages:
 - C3GSARA_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - C3GSARA_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - C3GSARA_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - C3GSARA_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c

void application_task ( void )
{
    switch ( example_state )
    {
        case C3GSARA_CONFIGURE_FOR_NETWORK:
        {
            if ( C3GSARA_OK == c3gsara_configure_for_network( ) )
            {
                example_state = C3GSARA_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case C3GSARA_WAIT_FOR_CONNECTION:
        {
            if ( C3GSARA_OK == c3gsara_check_connection( ) )
            {
                example_state = C3GSARA_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case C3GSARA_CONFIGURE_FOR_EXAMPLE:
        {
            if ( C3GSARA_OK == c3gsara_configure_for_example( ) )
            {
                example_state = C3GSARA_EXAMPLE;
            }
            break;
        }
        case C3GSARA_EXAMPLE:
        {
            c3gsara_example( );
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


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.3gSara

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
