
---
# LTE IoT 7 Click

> [LTE IoT 7 Click](https://www.mikroe.com/?pid_product=MIKROE-5290) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5290&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2022.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT7

### Example Key Functions

- `lteiot7_cfg_setup` Config Object Initialization function.
```c
void lteiot7_cfg_setup ( lteiot7_cfg_t *cfg );
```

- `lteiot7_init` Initialization function.
```c
err_t lteiot7_init ( lteiot7_t *ctx, lteiot7_cfg_t *cfg );
```

- `lteiot7_default_cfg` Click Default Configuration function.
```c
err_t lteiot7_default_cfg ( lteiot7_t *ctx );
```

- `lteiot7_set_sim_apn` This function sets APN for sim card.
```c
void lteiot7_set_sim_apn ( lteiot7_t *ctx, char *sim_apn );
```

- `lteiot7_send_sms_text` This function sends text message to a phone number.
```c
void lteiot7_send_sms_text ( lteiot7_t *ctx, char *phone_number, char *sms_text );
```

- `lteiot7_parse_gpgga` This function parses the GPGGA data from the read response buffer.
```c
err_t lteiot7_parse_gpgga ( char *rsp_buf, uint8_t gpgga_element, char *element_data );
```

### Application Init

> Initializes the driver, reboots the module which takes about 20 seconds and then tests the communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot7_cfg_t lteiot7_cfg;  /**< Click config object. */

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
    lteiot7_cfg_setup( &lteiot7_cfg );
    LTEIOT7_MAP_MIKROBUS( lteiot7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot7_init( &lteiot7, &lteiot7_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    lteiot7_set_power_state ( &lteiot7, LTEIOT7_POWER_STATE_REBOOT );
    
    lteiot7_process( );
    lteiot7_clear_app_buf( );
    app_buf_len = 0;
    app_buf_cnt = 0;

    // Check communication
    lteiot7_send_cmd( &lteiot7, LTEIOT7_CMD_AT );
    error_flag = lteiot7_rsp_check( );
    lteiot7_error_check( error_flag );

    log_info( &logger, " Application Task " );
    example_state = LTEIOT7_CONFIGURE_FOR_NETWORK;
}
```

### Application Task

> Application task is split in few stages:
 - LTEIOT7_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network. (used only for SMS or TCP/UDP demo examples).
 - LTEIOT7_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CREG URC event and then checks the connection status (used only for SMS or TCP/UDP demo examples).
 - LTEIOT7_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages or for retrieving data from GNSS depending on the selected demo example.
 - LTEIOT7_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( example_state )
    {
        case LTEIOT7_CONFIGURE_FOR_NETWORK:
        {
            if ( LTEIOT7_OK == lteiot7_configure_for_network( ) )
            {
                example_state = LTEIOT7_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT7_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT7_OK == lteiot7_check_connection( ) )
            {
                example_state = LTEIOT7_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case LTEIOT7_CONFIGURE_FOR_EXAMPLE:
        {
            if ( LTEIOT7_OK == lteiot7_configure_for_example( ) )
            {
                example_state = LTEIOT7_EXAMPLE;
            }
            break;
        }
        case LTEIOT7_EXAMPLE:
        {
            lteiot7_example( );
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

> In order for the examples to work (except GNSS example), user needs to set the APN and SMSC (SMS PDU mode only)
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
