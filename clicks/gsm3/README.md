
---
# GSM 3 Click

> [GSM 3 Click](https://www.mikroe.com/?pid_product=MIKROE-1720) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1720&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2023.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GSM3

### Example Key Functions

- `gsm3_cfg_setup` Config Object Initialization function.
```c
void gsm3_cfg_setup ( gsm3_cfg_t *cfg );
```

- `gsm3_init` Initialization function.
```c
err_t gsm3_init ( gsm3_t *ctx, gsm3_cfg_t *cfg );
```

- `gsm3_set_sim_apn` This function sets APN for sim card.
```c
void gsm3_set_sim_apn ( gsm3_t *ctx, uint8_t *sim_apn );
```

- `gsm3_send_sms_text` This function sends text message to a phone number.
```c
void gsm3_send_sms_text ( gsm3_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `gsm3_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t gsm3_send_sms_pdu ( gsm3_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

### Application Init

> Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gsm3_cfg_t gsm3_cfg;  /**< Click config object. */

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
    gsm3_cfg_setup( &gsm3_cfg );
    GSM3_MAP_MIKROBUS( gsm3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == gsm3_init( &gsm3, &gsm3_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    gsm3_process( );
    gsm3_clear_app_buf( );

    // Check communication
    gsm3_send_cmd( &gsm3, GSM3_CMD_AT );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    gsm3_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    gsm3_send_cmd_with_par( &gsm3, GSM3_CMD_CFUN, RESTART_DEVICE );
    error_flag = gsm3_rsp_check( GSM3_RSP_OK );
    gsm3_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = GSM3_CONFIGURE_FOR_NETWORK;
}
```

### Application Task

> Application task is split in few stages:
 - GSM3_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - GSM3_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - GSM3_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - GSM3_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void ) 
{
    switch ( example_state )
    {
        case GSM3_CONFIGURE_FOR_NETWORK:
        {
            if ( GSM3_OK == gsm3_configure_for_network( ) )
            {
                example_state = GSM3_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case GSM3_WAIT_FOR_CONNECTION:
        {
            if ( GSM3_OK == gsm3_check_connection( ) )
            {
                example_state = GSM3_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case GSM3_CONFIGURE_FOR_EXAMPLE:
        {
            if ( GSM3_OK == gsm3_configure_for_example( ) )
            {
                example_state = GSM3_EXAMPLE;
            }
            break;
        }
        case GSM3_EXAMPLE:
        {
            gsm3_example( );
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
> > Example: 
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
