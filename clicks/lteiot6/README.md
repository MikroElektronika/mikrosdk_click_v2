
---
# LTE IoT 6 Click

> [LTE IoT 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4388) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4388&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Nov 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> Application example shows device capability to connect 
network and send SMS messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT6

### Example Key Functions

- `lteiot6_cfg_setup` Config Object Initialization function.
```c
void lteiot6_cfg_setup ( lteiot6_cfg_t *cfg );
```

- `lteiot6_init` Initialization function.
```c
err_t lteiot6_init ( lteiot6_t *ctx, lteiot6_cfg_t *cfg );
```

- `lteiot6_default_cfg` Click Default Configuration function.
```c
void lteiot6_default_cfg ( lteiot6_t *ctx );
```

- `lteiot6_send_cmd` Send command function.
```c
void lteiot6_send_cmd ( lteiot6_t *ctx, char *cmd );
```

- `lteiot6_set_sim_apn` Set SIM APN.
```c
void lteiot6_set_sim_apn ( lteiot6_t *ctx, char *sim_apn );
```

- `lteiot6_send_sms_pdu` Send SMS message to number in pdu mode.
```c
err_t lteiot6_send_sms_pdu ( lteiot6_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

### Application Init

> Initializes driver and wake-up module and test communication.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot6_cfg_t lteiot6_cfg;  /**< Click config object. */

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
    Delay_ms ( 1000 );
    log_info( &logger, " Application Init " );
    Delay_ms ( 1000 );

    // Click initialization.
    lteiot6_cfg_setup( &lteiot6_cfg );
    LTEIOT6_MAP_MIKROBUS( lteiot6_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot6_init( &lteiot6, &lteiot6_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    lteiot6_process();
    lteiot6_clear_app_buf(); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    lteiot6_reset( &lteiot6 );
    lteiot6_power_on( &lteiot6 );
    
    //Check communication
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_AT );
    error_flag = lteiot6_rsp_check();
    lteiot6_error_check( error_flag );
    
    //Check fw version
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_ATI );
    error_flag = lteiot6_rsp_check();
    lteiot6_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTEIOT6_CONFIGURE_FOR_CONNECTION;
}
```

### Application Task

> Application taks is split in few stages:
 - LTEIOT6_CONFIGURE_FOR_CONNECTION: 
> Sets configuration to device to be able to connect to newtork.

 - LTEIOT6_WAIT_FOR_CONNECTION: 
> Checks device response untill device sends information 
that it is connected to network.

 - LTEIOT6_CHECK_CONNECTION:
> Checks device connection status parameters.

 - LTEIOT6_CONFIGURE_FOR_MESSAGES:
> Sets configuration to device to send SMS messages.

 - LTEIOT6_MESSAGES:
> Sends message in selected mode (PDU/TXT).

```c
void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTEIOT6_CONFIGURE_FOR_CONNECTION:
        {
            if ( LTEIOT6_OK == lteiot6_configure_for_connection( ) )
            {
                example_state = LTEIOT6_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT6_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT6_OK == lteiot6_check_connection( ) )
            {
                example_state = LTEIOT6_CHECK_CONNECTION;
            }
            break;
        }
        case LTEIOT6_CHECK_CONNECTION:
        {
            Delay_ms ( 1000 );
            if ( LTEIOT6_OK == lteiot6_check_connection_parameters( ) )
            {
                example_state = LTEIOT6_CONFIGURE_FOR_MESSAGES;
            }
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT6_CONFIGURE_FOR_MESSAGES:
        {
            if ( LTEIOT6_OK == lteiot6_configure_for_meesages( ) )
            {
                example_state = LTEIOT6_MESSAGES;
            }
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT6_MESSAGES:
        {
            lteiot6_send_meesage();
            Delay_ms ( 1000 );
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

> In order for the example to work, user needs to set the phone number to which he wants 
to send an SMS, and also will need to set an APN and SMSC of entered SIM card.
Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>>E.g. 
SIM_APN                     "vip.iot",
SMSC_ADDRESS_CSCA           "\"+381999999\",145",
SMSC_ADDRESS_PDU            "+381999999\" ,
PHONE_NUMBER_TO_MESSAGE     "+381659999999",
  PHONE_NUMBER_TO_MESSAGE "999999999"

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
