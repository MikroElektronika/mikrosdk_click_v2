
---
# LTE Cat.1 3 NAX Click

> [LTE Cat.1 3 NAX Click](https://www.mikroe.com/?pid_product=MIKROE-6277) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6277&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic 
- **Date**          : Mar 2024.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and 
  sending SMS, TCP/UDP messages, calling the selected number, or getting GNSS location
  using standard "AT" commands. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTECat13NAX

### Example Key Functions

- `ltecat13nax_cfg_setup` Config Object Initialization function.
```c
void ltecat13nax_cfg_setup ( ltecat13nax_cfg_t *cfg );
```

- `ltecat13nax_init` Initialization function.
```c
err_t ltecat13nax_init ( ltecat13nax_t *ctx, ltecat13nax_cfg_t *cfg );
```

- `ltecat13nax_write_register` This function writes a data byte into the selected register address.
```c
err_t ltecat13nax_write_register ( ltecat13nax_t *ctx, uint8_t reg, uint8_t data_in );
```

- `ltecat13nax_max9860_cfg` This function is used to set basic config for MAX9860 of LTE Cat.1 3 NAX Click board.
```c
err_t ltecat13nax_max9860_cfg ( ltecat13nax_t *ctx );
```

- `ltecat13nax_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t ltecat13nax_send_sms_pdu ( ltecat13nax_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

### Application Init

> Sets the device configuration for sending SMS, TCP/UDP messages, calling the selected number
  or GNSS location.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat13nax_cfg_t ltecat13nax_cfg;  /**< Click config object. */

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
    ltecat13nax_cfg_setup( &ltecat13nax_cfg );
    LTECAT13NAX_MAP_MIKROBUS( ltecat13nax_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat13nax_init( &ltecat13nax, &ltecat13nax_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ltecat13nax_process( );
    ltecat13nax_clear_app_buf( );
    Delay_ms ( 1000 );

    if ( 0 == ltecat13nax_get_ri_pin( &ltecat13nax ) )
    {
        ltecat13nax_start_up( &ltecat13nax );
        error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_RDY );
        ltecat13nax_error_check( error_flag );
    }

    // Restart device
    #define MIN_FUN_DEVICE "0"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CFUN, MIN_FUN_DEVICE );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    ltecat13nax_error_check( error_flag );

    #define FULL_FUN_DEVICE "1"
    ltecat13nax_send_cmd_with_params( &ltecat13nax, LTECAT13NAX_CMD_CFUN, FULL_FUN_DEVICE );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    ltecat13nax_error_check( error_flag );
    
    // Check communication
    ltecat13nax_send_cmd( &ltecat13nax, LTECAT13NAX_CMD_AT );
    error_flag = ltecat13nax_rsp_check( LTECAT13NAX_RSP_OK );
    ltecat13nax_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTECAT13NAX_CONFIGURE_FOR_NETWORK;
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
        case LTECAT13NAX_CONFIGURE_FOR_NETWORK:
        {
            if ( LTECAT13NAX_OK == ltecat13nax_cfg_for_network( ) )
            {
                example_state = LTECAT13NAX_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTECAT13NAX_WAIT_FOR_CONNECTION:
        {
            if ( LTECAT13NAX_OK == ltecat13nax_check_connection( ) )
            {
                example_state = LTECAT13NAX_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTECAT13NAX_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTECAT13NAX_OK == ltecat13nax_cfg_for_example( ) )
            {
                example_state = LTECAT13NAX_EXAMPLE;
            }
            break;
        }
        case LTECAT13NAX_EXAMPLE:
        {
            ltecat13nax_example( );
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

### Note

> In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only)
  of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
  Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
> >  Example:
> > - SIM_APN "internet"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER_TO_MESSAGE "+381659999999"

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
