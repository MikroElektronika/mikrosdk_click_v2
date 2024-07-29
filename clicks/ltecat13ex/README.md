\mainpage Main Page

---
# LTE Cat.1 3 EX click

> LTE Cat.1 3 Click (for Europe) is a compact add-on board for reliable 4G wireless communication. This board features the EG91EXGA-128-SGNS, an LTE Cat 1 IoT module that meets the 3GPP Release 11 standard from Quectel. It supports multiple wireless standards, including LTE-FDD, WCDMA, and GSM, ensuring broad network compatibility. Key features include multi-band LTE support (B1/B3/B7/B8/B20/B28), RX diversity for bands B1 and B8, and multi-constellation GNSS (GPS, GLONASS, BeiDou/Compass, Galileo, QZSS). It also integrates a 16-bit mono audio codec for voice functionality with support for CTIA standard headphones.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-cat1-3-click)

---


#### Click library

- **Author**        : Stefan Ilic 
- **Date**          : Mar 2024.
- **Type**          : UART type


# Software Support

We provide a library for the LTE Cat.1 3 EX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LTE Cat.1 3 EX Click driver.

#### Standard key functions :

- `ltecat13ex_cfg_setup` Config Object Initialization function.
```c
void ltecat13ex_cfg_setup ( ltecat13ex_cfg_t *cfg );
```

- `ltecat13ex_init` Initialization function.
```c
err_t ltecat13ex_init ( ltecat13ex_t *ctx, ltecat13ex_cfg_t *cfg );
```

#### Example key functions :

- `ltecat13ex_write_register` This function writes a data byte into the selected register address.
```c
err_t ltecat13ex_write_register ( ltecat13ex_t *ctx, uint8_t reg, uint8_t data_in );
```

- `ltecat13ex_max9860_cfg` This function is used to set basic config for MAX9860 of LTE Cat.1 3 EX click board.
```c
err_t ltecat13ex_max9860_cfg ( ltecat13ex_t *ctx );
```

- `ltecat13ex_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t ltecat13ex_send_sms_pdu ( ltecat13ex_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

## Example Description

> Application example shows device capability of connecting to the network and 
  sending SMS, TCP/UDP messages, calling the selected number, or getting GNSS location
  using standard "AT" commands. 

**The demo application is composed of two sections :**

### Application Init

> Sets the device configuration for sending SMS, TCP/UDP messages, calling the selected number
  or GNSS location.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat13ex_cfg_t ltecat13ex_cfg;  /**< Click config object. */

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
    ltecat13ex_cfg_setup( &ltecat13ex_cfg );
    LTECAT13EX_MAP_MIKROBUS( ltecat13ex_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat13ex_init( &ltecat13ex, &ltecat13ex_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ltecat13ex_process( );
    ltecat13ex_clear_app_buf( );
    Delay_ms ( 1000 );

    if ( 0 == ltecat13ex_get_ri_pin( &ltecat13ex ) )
    {
        ltecat13ex_start_up( &ltecat13ex );
        error_flag = ltecat13ex_rsp_check( LTECAT13EX_RSP_RDY );
        ltecat13ex_error_check( error_flag );
    }

    // Restart device
    #define MIN_FUN_DEVICE "0"
    ltecat13ex_send_cmd_with_params( &ltecat13ex, LTECAT13EX_CMD_CFUN, MIN_FUN_DEVICE );
    error_flag = ltecat13ex_rsp_check( LTECAT13EX_RSP_OK );
    ltecat13ex_error_check( error_flag );

    #define FULL_FUN_DEVICE "1"
    ltecat13ex_send_cmd_with_params( &ltecat13ex, LTECAT13EX_CMD_CFUN, FULL_FUN_DEVICE );
    error_flag = ltecat13ex_rsp_check( LTECAT13EX_RSP_OK );
    ltecat13ex_error_check( error_flag );
    
    // Check communication
    ltecat13ex_send_cmd( &ltecat13ex, LTECAT13EX_CMD_AT );
    error_flag = ltecat13ex_rsp_check( LTECAT13EX_RSP_OK );
    ltecat13ex_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTECAT13EX_CONFIGURE_FOR_NETWORK;
}

```

### Application Task

> Depending on the selected demo example, it sends an SMS message 
  (in PDU or TXT mode) or a TCP/UDP message, calls the selected number or
  gets GNSS location.

```c
void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTECAT13EX_CONFIGURE_FOR_NETWORK:
        {
            if ( LTECAT13EX_OK == ltecat13ex_cfg_for_network( ) )
            {
                example_state = LTECAT13EX_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTECAT13EX_WAIT_FOR_CONNECTION:
        {
            if ( LTECAT13EX_OK == ltecat13ex_check_connection( ) )
            {
                example_state = LTECAT13EX_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTECAT13EX_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTECAT13EX_OK == ltecat13ex_cfg_for_example( ) )
            {
                example_state = LTECAT13EX_EXAMPLE;
            }
            break;
        }
        case LTECAT13EX_EXAMPLE:
        {
            ltecat13ex_example( );
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
- Click.LTECat13EX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
