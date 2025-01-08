
---
# LTE IoT 8 Click

> [LTE IoT 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4493) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4493&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Apr 2021.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability to connect 
network and send SMS messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT8

### Example Key Functions

- `lteiot8_cfg_setup` Config Object Initialization function.
```c
void lteiot8_cfg_setup ( lteiot8_cfg_t *cfg );
```

- `lteiot8_init` Initialization function.
```c
err_t lteiot8_init ( lteiot8_t *ctx, lteiot8_cfg_t *cfg );
```

- `lteiot8_default_cfg` Click Default Configuration function.
```c
err_t lteiot8_default_cfg ( lteiot8_t *ctx );
```

- `lteiot8_send_cmd` Send command function.
```c
void lteiot8_send_cmd ( lteiot8_t *ctx, char *cmd );
```

- `lteiot8_set_sim_apn` Set SIM APN.
```c
void lteiot8_set_sim_apn ( lteiot8_t *ctx, char *sim_apn );
```

- `lteiot8_send_text_message` Send SMS message to number in text mode.
```c
void lteiot8_send_text_message ( lteiot8_t *ctx, char *phone_number, char *message_content );
```

### Application Init

> Initializes driver and wake-up module and test communication.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot8_cfg_t lteiot8_cfg;  /**< Click config object. */

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
    lteiot8_cfg_setup( &lteiot8_cfg );
    LTEIOT8_MAP_MIKROBUS( lteiot8_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot8_init( &lteiot8, &lteiot8_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    lteiot8_process();
    lteiot8_clear_app_buf(); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    lteiot8_default_cfg ( &lteiot8 );
    while ( 0 == strstr( app_buf, LTEIOT8_RSP_SYSTART ) )
    {
        lteiot8_process();
    }
    
    //Check communication
    lteiot8_send_cmd( &lteiot8, "AT" );
    error_flag = lteiot8_rsp_check();
    lteiot8_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTEIOT8_CONFIGURE_FOR_CONNECTION;
}
```

### Application Task

> Application taks is split in few stages:
 - LTEIOT8_CONFIGURE_FOR_CONNECTION: 
> Sets configuration to device to be able to connect to newtork.
 - LTEIOT8_WAIT_FOR_CONNECTION: 
> Checks device response untill device sends information 
that it is connected to network.
 - LTEIOT8_CHECK_CONNECTION:
> Checks device connection status parameters.
 - LTEIOT8_CONFIGURE_FOR_MESSAGES:
> Sets configuration to device to send SMS messages.
 - LTEIOT8_MESSAGES:
> Sends message in selected mode (PDU/TXT).

```c
void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTEIOT8_CONFIGURE_FOR_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_configure_for_connection( ) )
            {
                example_state = LTEIOT8_WAIT_FOR_CONNECTION;
            }
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT8_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_check_connection( ) )
            {
                example_state = LTEIOT8_CHECK_CONNECTION;
            }
            break;
        }
        case LTEIOT8_CHECK_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_check_connection_parameters( ) )
            {
                example_state = LTEIOT8_CONFIGURE_FOR_MESSAGES;
            }
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT8_CONFIGURE_FOR_MESSAGES:
        {
            if ( LTEIOT8_OK == lteiot8_configure_for_meesages( ) )
            {
                example_state = LTEIOT8_MESSAGES;
            }
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            break;
        }
        case LTEIOT8_MESSAGES:
        {
            lteiot8_send_meesage();
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
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
PHONE_NUMBER_TO_MESSAGE     "+381659999999"

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
