
---
# 4G LTE 2 Data-NA Click

> [4G LTE 2 Data-NA Click](https://www.mikroe.com/?pid_product=MIKROE-6476) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6476&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4GLTE2DataNA

### Example Key Functions

- `c4glte2datana_cfg_setup` Config Object Initialization function.
```c
void c4glte2datana_cfg_setup ( c4glte2datana_cfg_t *cfg );
```

- `c4glte2datana_init` Initialization function.
```c
err_t c4glte2datana_init ( c4glte2datana_t *ctx, c4glte2datana_cfg_t *cfg );
```

- `c4glte2datana_set_power_state` This function sets a desired power state by toggling PWR pin with a specific time for high state.
```c
void c4glte2datana_set_power_state ( c4glte2datana_t *ctx, uint8_t state );
```

- `c4glte2datana_set_sim_apn` This function sets APN for sim card.
```c
void c4glte2datana_set_sim_apn ( c4glte2datana_t *ctx, char *sim_apn );
```

- `c4glte2datana_send_sms_text` This function sends text message to a phone number.
```c
void c4glte2datana_send_sms_text ( c4glte2datana_t *ctx, char *phone_number, char *sms_text );
```

### Application Init

> Initializes the driver, restarts the module and tests the communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4glte2datana_cfg_t c4glte2datana_cfg;  /**< Click config object. */

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
    c4glte2datana_cfg_setup( &c4glte2datana_cfg );
    C4GLTE2DATANA_MAP_MIKROBUS( c4glte2datana_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c4glte2datana_init( &c4glte2datana, &c4glte2datana_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    c4glte2datana_set_power_state ( &c4glte2datana, C4GLTE2DATANA_POWER_STATE_OFF );
    c4glte2datana_set_power_state ( &c4glte2datana, C4GLTE2DATANA_POWER_STATE_ON );
    c4glte2datana_process( );
    c4glte2datana_clear_app_buf( );
    app_buf_len = 0;
    app_buf_cnt = 0;

    // Check communication
    c4glte2datana_send_cmd( &c4glte2datana, C4GLTE2DATANA_CMD_AT );
    error_flag = c4glte2datana_rsp_check( );
    c4glte2datana_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = C4GLTE2DATANA_CONFIGURE_FOR_NETWORK;
}
```

### Application Task

> Application task is split in few stages:
 - C4GLTE2DATANA_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - C4GLTE2DATANA_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status.
 - C4GLTE2DATANA_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - C4GLTE2DATANA_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case C4GLTE2DATANA_CONFIGURE_FOR_NETWORK:
        {
            if ( C4GLTE2DATANA_OK == c4glte2datana_configure_for_network( ) )
            {
                example_state = C4GLTE2DATANA_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case C4GLTE2DATANA_WAIT_FOR_CONNECTION:
        {
            if ( C4GLTE2DATANA_OK == c4glte2datana_check_connection( ) )
            {
                example_state = C4GLTE2DATANA_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case C4GLTE2DATANA_CONFIGURE_FOR_EXAMPLE:
        {
            if ( C4GLTE2DATANA_OK == c4glte2datana_configure_for_example( ) )
            {
                example_state = C4GLTE2DATANA_EXAMPLE;
            }
            break;
        }
        case C4GLTE2DATANA_EXAMPLE:
        {
            c4glte2datana_example( );
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
