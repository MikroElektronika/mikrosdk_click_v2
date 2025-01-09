
---
# LTE Cat.1 2 Click

> [LTE Cat.1 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5906) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5906&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and 
  sending SMS, TCP/UDP messages or calling the selected number using standard "AT" commands. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTECat12

### Example Key Functions

- `ltecat12_cfg_setup` Config Object Initialization function.
```c
void ltecat12_cfg_setup ( ltecat12_cfg_t *cfg );
```

- `ltecat12_init` Initialization function.
```c
err_t ltecat12_init ( ltecat12_t *ctx, ltecat12_cfg_t *cfg );
```

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
