\mainpage Main Page

---
# LTE Cat.1 2 click

> LTE Cat.1 2 Click (EU) is a compact add-on board that provides your application with complete LTE and VoLTE with CSFB functionalities. This board features the ELS62-E, a single antenna LTE cat.1bis module from Telit.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-cat1-2-click-for-eu)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : UART type


# Software Support

We provide a library for the LTE Cat.1 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE Cat.1 2 Click driver.

#### Standard key functions :

- `ltecat12_cfg_setup` Config Object Initialization function.
```c
void ltecat12_cfg_setup ( ltecat12_cfg_t *cfg );
```

- `ltecat12_init` Initialization function.
```c
err_t ltecat12_init ( ltecat12_t *ctx, ltecat12_cfg_t *cfg );
```

#### Example key functions :

- `ltecat12_max9860_cfg` LTE Cat.1 2 MAX9860 configuration function.
```c
err_t ltecat12_max9860_cfg ( ltecat12_t *ctx );
```

- `ltecat12_send_cmd` LTE Cat.1 2 send command function.
```c
void ltecat12_send_cmd ( ltecat12_t *ctx, uint8_t *cmd );
```

- `ltecat12_send_sms_pdu` LTE Cat.1 2 send SMS in PDU mode.
```c
err_t ltecat12_send_sms_pdu ( ltecat12_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and 
  sending SMS, TCP/UDP messages or calling the selected number using standard "AT" commands. 

**The demo application is composed of two sections :**

### Application Init

> Sets the device configuration for sending SMS, TCP/UDP messages or calling the selected number.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat12_cfg_t ltecat12_cfg;  /**< Click config object. */

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
    ltecat12_cfg_setup( &ltecat12_cfg );
    LTECAT12_MAP_MIKROBUS( ltecat12_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat12_init( &ltecat12, &ltecat12_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    ltecat12_process( );
    ltecat12_clear_app_buf( );

    // Restart device
    #define RESTART_DEVICE "1,1"
    ltecat12_send_cmd_with_params( &ltecat12, LTECAT12_CMD_CFUN, RESTART_DEVICE );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_SYSSTART );
    ltecat12_error_check( error_flag );
    
    // Check communication
    ltecat12_send_cmd( &ltecat12, LTECAT12_CMD_AT );
    error_flag = ltecat12_rsp_check( LTECAT12_RSP_OK );
    ltecat12_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTECAT12_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Depending on the selected demo example, it sends an SMS message 
  (in PDU or TXT mode) or a TCP/UDP message or calls the selected number.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case LTECAT12_CONFIGURE_FOR_NETWORK:
        {
            if ( LTECAT12_OK == ltecat12_cfg_for_network( ) )
            {
                example_state = LTECAT12_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTECAT12_WAIT_FOR_CONNECTION:
        {
            if ( LTECAT12_OK == ltecat12_check_connection( ) )
            {
                example_state = LTECAT12_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTECAT12_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTECAT12_OK == ltecat12_cfg_for_example( ) )
            {
                example_state = LTECAT12_EXAMPLE;
            }
            break;
        }
        case LTECAT12_EXAMPLE:
        {
            ltecat12_example( );
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
> >  Example:
> > - SIM_APN "internet"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTECat12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
