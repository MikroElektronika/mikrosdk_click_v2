
---
# LTE IoT 23 Click

> [LTE IoT 23 Click](https://www.mikroe.com/?pid_product=MIKROE-6682) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6682&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2025.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT23

### Example Key Functions

- `lteiot23_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void lteiot23_cfg_setup ( lteiot23_cfg_t *cfg );
```

- `lteiot23_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t lteiot23_init ( lteiot23_t *ctx, lteiot23_cfg_t *cfg );
```

- `lteiot23_set_sim_apn` This function sets APN for sim card.
```c
void lteiot23_set_sim_apn ( lteiot23_t *ctx, uint8_t *sim_apn );
```

- `lteiot23_send_sms_text` This function sends text message to a phone number.
```c
void lteiot23_send_sms_text ( lteiot23_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `lteiot23_cmd_run` This function sends a specified command to the Click module.
```c
void lteiot23_cmd_run ( lteiot23_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot23_cfg_t lteiot23_cfg;  /**< Click config object. */

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
    lteiot23_cfg_setup( &lteiot23_cfg );
    LTEIOT23_MAP_MIKROBUS( lteiot23_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot23_init( &lteiot23, &lteiot23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT23_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - LTEIOT23_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - LTEIOT23_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network.
 - LTEIOT23_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 - LTEIOT23_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTEIOT23_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTEIOT23_POWER_UP:
        {
            if ( LTEIOT23_OK == lteiot23_power_up( &lteiot23 ) )
            {
                app_state = LTEIOT23_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_CONFIG_CONNECTION:
        {
            if ( LTEIOT23_OK == lteiot23_config_connection( &lteiot23 ) )
            {
                app_state = LTEIOT23_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_CHECK_CONNECTION:
        {
            if ( LTEIOT23_OK == lteiot23_check_connection( &lteiot23 ) )
            {
                app_state = LTEIOT23_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_CONFIG_EXAMPLE:
        {
            if ( LTEIOT23_OK == lteiot23_config_example( &lteiot23 ) )
            {
                app_state = LTEIOT23_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT23_EXAMPLE:
        {
            lteiot23_example( &lteiot23 );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
    }
}
```

### Note

> In order for the examples to work, user needs to set the APN and SMSC (SMS PDU mode only)
of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER.
> > Example: 
> > - SIM_APN "internet"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER "+381659999999"

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
