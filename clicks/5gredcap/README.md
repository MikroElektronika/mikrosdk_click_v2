
---
# 5G RedCap Click

> [5G RedCap Click](https://www.mikroe.com/?pid_product=MIKROE-6625) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6625&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2026.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and
sending SMS or TCP/UDP messages, answering incoming calls, or retrieving data
from GNSS using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.5GRedCap

### Example Key Functions

- `c5gredcap_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void c5gredcap_cfg_setup ( c5gredcap_cfg_t *cfg );
```

- `c5gredcap_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t c5gredcap_init ( c5gredcap_t *ctx, c5gredcap_cfg_t *cfg );
```

- `c5gredcap_send_sms_text` This function sends text message to a phone number.
```c
void c5gredcap_send_sms_text ( c5gredcap_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

- `c5gredcap_dial_number` This function dials the selected phone number.
```c
void c5gredcap_dial_number ( c5gredcap_t *ctx, uint8_t *phone_number );
```

- `c5gredcap_parse_gga` This function parses the GGA data from the read response buffer.
```c
err_t c5gredcap_parse_gga ( uint8_t *rsp_buf, uint8_t gga_element, uint8_t *element_data );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c5gredcap_cfg_t c5gredcap_cfg;  /**< Click config object. */

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
    c5gredcap_cfg_setup( &c5gredcap_cfg );
    C5GREDCAP_MAP_MIKROBUS( c5gredcap_cfg, MIKROBUS_POSITION_5GREDCAP );
    if ( UART_ERROR == c5gredcap_init( &c5gredcap, &c5gredcap_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = C5GREDCAP_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - C5GREDCAP_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - C5GREDCAP_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network (used only for SMS, CALL, or TCP/UDP demo examples).
 - C5GREDCAP_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report (used only for SMS, CALL, or TCP/UDP demo examples).
 - C5GREDCAP_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - C5GREDCAP_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message, waits for incoming calls and answers it, or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case C5GREDCAP_POWER_UP:
        {
            if ( C5GREDCAP_OK == c5gredcap_power_up( &c5gredcap ) )
            {
                app_state = C5GREDCAP_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_CONFIG_CONNECTION:
        {
            if ( C5GREDCAP_OK == c5gredcap_config_connection( &c5gredcap ) )
            {
                app_state = C5GREDCAP_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_CHECK_CONNECTION:
        {
            if ( C5GREDCAP_OK == c5gredcap_check_connection( &c5gredcap ) )
            {
                app_state = C5GREDCAP_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_CONFIG_EXAMPLE:
        {
            if ( C5GREDCAP_OK == c5gredcap_config_example( &c5gredcap ) )
            {
                app_state = C5GREDCAP_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case C5GREDCAP_EXAMPLE:
        {
            c5gredcap_example( &c5gredcap );
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
