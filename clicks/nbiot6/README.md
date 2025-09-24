
---
# NB IoT 6 Click

> [NB IoT 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6419) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6419&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending SMS or TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT6

### Example Key Functions

- `nbiot6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void nbiot6_cfg_setup ( nbiot6_cfg_t *cfg );
```

- `nbiot6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t nbiot6_init ( nbiot6_t *ctx, nbiot6_cfg_t *cfg );
```

- `nbiot6_set_power_state` This function sets a desired power state by toggling PWR, RST, and WUP pins with a specific time frame.
```c
void nbiot6_set_power_state ( nbiot6_t *ctx, uint8_t state );
```

- `nbiot6_cmd_run` This function sends a specified command to the Click module.
```c
void nbiot6_cmd_run ( nbiot6_t *ctx, uint8_t *cmd );
```

- `nbiot6_cmd_set` This function sets a value to a specified command of the Click module.
```c
void nbiot6_cmd_set ( nbiot6_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `nbiot6_send_sms_text` This function sends text message to a phone number.
```c
void nbiot6_send_sms_text ( nbiot6_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot6_cfg_t nbiot6_cfg;  /**< Click config object. */

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
    nbiot6_cfg_setup( &nbiot6_cfg );
    NBIOT6_MAP_MIKROBUS( nbiot6_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot6_init( &nbiot6, &nbiot6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = NBIOT6_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - NBIOT6_POWER_UP: 
   > Powers up the device and reads system information.
 - NBIOT6_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network.
 - NBIOT6_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 - NBIOT6_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - NBIOT6_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case NBIOT6_POWER_UP:
        {
            if ( NBIOT6_OK == nbiot6_power_up( &nbiot6 ) )
            {
                app_state = NBIOT6_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_CONFIG_CONNECTION:
        {
            if ( NBIOT6_OK == nbiot6_config_connection( &nbiot6 ) )
            {
                app_state = NBIOT6_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_CHECK_CONNECTION:
        {
            if ( NBIOT6_OK == nbiot6_check_connection( &nbiot6 ) )
            {
                app_state = NBIOT6_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_CONFIG_EXAMPLE:
        {
            if ( NBIOT6_OK == nbiot6_config_example( &nbiot6 ) )
            {
                app_state = NBIOT6_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT6_EXAMPLE:
        {
            nbiot6_example( &nbiot6 );
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
