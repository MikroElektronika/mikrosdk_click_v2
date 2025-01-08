
---
# NB IoT 5 Click

> [NB IoT 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4472) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4472&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT5

### Example Key Functions

- `nbiot5_cfg_setup` Config Object Initialization function.
```c
void nbiot5_cfg_setup ( nbiot5_cfg_t *cfg );
```

- `nbiot5_init` Initialization function.
```c
err_t nbiot5_init ( nbiot5_t *ctx, nbiot5_cfg_t *cfg );
```

- `nbiot5_set_sim_apn` This function sets APN for sim card.
```c
void nbiot5_set_sim_apn ( nbiot5_t *ctx, uint8_t *sim_apn );
```

- `nbiot5_send_sms_text` This function sends text message to a phone number.
```c
void nbiot5_send_sms_text ( nbiot5_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `nbiot5_send_sms_pdu` This function sends text message to a phone number in PDU mode.
```c
err_t nbiot5_send_sms_pdu ( nbiot5_t *ctx, uint8_t *service_center_number, uint8_t *phone_number, uint8_t *sms_text );
```

### Application Init

> Initializes the driver, tests the communication by sending "AT" command, and after that restarts the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot5_cfg_t nbiot5_cfg;  /**< Click config object. */

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
    nbiot5_cfg_setup( &nbiot5_cfg );
    NBIOT5_MAP_MIKROBUS( nbiot5_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot5_init( &nbiot5, &nbiot5_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    nbiot5_process( );
    nbiot5_clear_app_buf( );

    // Check communication
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_AT );
    error_flag = nbiot5_rsp_check( NBIOT5_RSP_OK );
    nbiot5_error_check( error_flag );
    
    // Restart device
    #define RESTART_DEVICE "1,1"
    nbiot5_send_cmd_with_par( &nbiot5, NBIOT5_CMD_CFUN, RESTART_DEVICE );
    error_flag = nbiot5_rsp_check( NBIOT5_RSP_OK );
    nbiot5_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = NBIOT5_CONFIGURE_FOR_NETWORK;
}
```

### Application Task

> Application task is split in few stages:
 - NBIOT5_CONFIGURE_FOR_NETWORK: 
   > Sets configuration to device to be able to connect to the network.
 - NBIOT5_WAIT_FOR_CONNECTION: 
   > Waits for the network registration indicated via CEREG URC event and then checks the connection status.
 - NBIOT5_CONFIGURE_FOR_EXAMPLE:
   > Sets the device configuration for sending SMS or TCP/UDP messages depending on the selected demo example.
 - NBIOT5_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void ) 
{
    switch ( example_state )
    {
        case NBIOT5_CONFIGURE_FOR_NETWORK:
        {
            if ( NBIOT5_OK == nbiot5_configure_for_network( ) )
            {
                example_state = NBIOT5_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case NBIOT5_WAIT_FOR_CONNECTION:
        {
            if ( NBIOT5_OK == nbiot5_check_connection( ) )
            {
                example_state = NBIOT5_CONFIGURE_FOR_EXAMPLE;
            }
            break;
        }
        case NBIOT5_CONFIGURE_FOR_EXAMPLE:
        {
            if ( NBIOT5_OK == nbiot5_configure_for_example( ) )
            {
                example_state = NBIOT5_EXAMPLE;
            }
            break;
        }
        case NBIOT5_EXAMPLE:
        {
            nbiot5_example( );
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
> Make sure the JP2 is removed from the Click board, otherwise, you will need to connect the USB so that the module can boot up successfully.


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
