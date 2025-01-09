
---
# LTE IoT 14 Click

> [LTE IoT 14 Click](https://www.mikroe.com/?pid_product=MIKROE-6389) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6389&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and
sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT14

### Example Key Functions

- `lteiot14_cfg_setup` Config Object Initialization function.
```c
void lteiot14_cfg_setup ( lteiot14_cfg_t *cfg );
```

- `lteiot14_init` Initialization function.
```c
err_t lteiot14_init ( lteiot14_t *ctx, lteiot14_cfg_t *cfg );
```

- `lteiot14_set_sim_apn` This function sets APN for sim card.
```c
void lteiot14_set_sim_apn ( lteiot14_t *ctx, uint8_t *sim_apn );
```

- `lteiot14_send_sms_text` This function sends text message to a phone number.
```c
void lteiot14_send_sms_text ( lteiot14_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `lteiot14_send_cmd` This function sends a specified command to the Click module.
```c
void lteiot14_send_cmd ( lteiot14_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot14_cfg_t lteiot14_cfg;  /**< Click config object. */

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
    lteiot14_cfg_setup( &lteiot14_cfg );
    LTEIOT14_MAP_MIKROBUS( lteiot14_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lteiot14_init( &lteiot14, &lteiot14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTEIOT14_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - LTEIOT14_POWER_UP: 
   > Powers up the device, performs a device reset and reads system information.
 - LTEIOT14_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 - LTEIOT14_CHECK_CONNECTION:
   > Waits for the network registration indicated via CREG command and then checks the signal quality report (used only for SMS or TCP/UDP demo examples).
 - LTEIOT14_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTEIOT14_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTEIOT14_POWER_UP:
        {
            if ( LTEIOT14_OK == lteiot14_power_up( &lteiot14 ) )
            {
                app_state = LTEIOT14_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_CONFIG_CONNECTION:
        {
            if ( LTEIOT14_OK == lteiot14_config_connection( &lteiot14 ) )
            {
                app_state = LTEIOT14_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_CHECK_CONNECTION:
        {
            if ( LTEIOT14_OK == lteiot14_check_connection( &lteiot14 ) )
            {
                app_state = LTEIOT14_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_CONFIG_EXAMPLE:
        {
            if ( LTEIOT14_OK == lteiot14_config_example( &lteiot14 ) )
            {
                app_state = LTEIOT14_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTEIOT14_EXAMPLE:
        {
            lteiot14_example( &lteiot14 );
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
