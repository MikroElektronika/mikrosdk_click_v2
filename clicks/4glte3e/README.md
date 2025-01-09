
---
# 4G LTE 3 E Click

> [4G LTE 3 E Click](https://www.mikroe.com/?pid_product=MIKROE-6380) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6380&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.4GLTE3E

### Example Key Functions

- `c4glte3e_cfg_setup` Config Object Initialization function.
```c
void c4glte3e_cfg_setup ( c4glte3e_cfg_t *cfg );
```

- `c4glte3e_init` Initialization function.
```c
err_t c4glte3e_init ( c4glte3e_t *ctx, c4glte3e_cfg_t *cfg );
```

- `c4glte3e_set_sim_apn` This function sets APN for sim card.
```c
void c4glte3e_set_sim_apn ( c4glte3e_t *ctx, uint8_t *sim_apn );
```

- `c4glte3e_send_sms_text` This function sends text message to a phone number.
```c
void c4glte3e_send_sms_text ( c4glte3e_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `c4glte3e_cmd_run` This function sends a specified command to the Click module.
```c
void c4glte3e_cmd_run ( c4glte3e_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4glte3e_cfg_t c4glte3e_cfg;  /**< Click config object. */

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
    c4glte3e_cfg_setup( &c4glte3e_cfg );
    C4GLTE3E_MAP_MIKROBUS( c4glte3e_cfg, MIKROBUS_1 );
    if ( UART_ERROR == c4glte3e_init( &c4glte3e, &c4glte3e_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = C4GLTE3E_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - C4GLTE3E_POWER_UP:
   > Powers up the device, performs a factory reset and reads system information.
 - C4GLTE3E_CONFIG_CONNECTION:
   > Sets configuration to device to be able to connect to the network.
 - C4GLTE3E_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 - C4GLTE3E_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - C4GLTE3E_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case C4GLTE3E_POWER_UP:
        {
            if ( C4GLTE3E_OK == c4glte3e_power_up( &c4glte3e ) )
            {
                app_state = C4GLTE3E_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case C4GLTE3E_CONFIG_CONNECTION:
        {
            if ( C4GLTE3E_OK == c4glte3e_config_connection( &c4glte3e ) )
            {
                app_state = C4GLTE3E_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case C4GLTE3E_CHECK_CONNECTION:
        {
            if ( C4GLTE3E_OK == c4glte3e_check_connection( &c4glte3e ) )
            {
                app_state = C4GLTE3E_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case C4GLTE3E_CONFIG_EXAMPLE:
        {
            if ( C4GLTE3E_OK == c4glte3e_config_example( &c4glte3e ) )
            {
                app_state = C4GLTE3E_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case C4GLTE3E_EXAMPLE:
        {
            c4glte3e_example( &c4glte3e );
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
> of entered SIM card as well as the phone number (SMS mode only) to which he wants to send an SMS.
> Enter valid values for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER.
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
