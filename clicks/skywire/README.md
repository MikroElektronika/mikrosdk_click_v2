
---
# Skywire Click

> [Skywire Click](https://www.mikroe.com/?pid_product=MIKROE-2405) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2405&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Sep 2026.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending
TCP/UDP messages, SMS messages, performing a voice call or reading the GNSS position
using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Skywire

### Example Key Functions

- `skywire_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void skywire_cfg_setup ( skywire_cfg_t *cfg );
```

- `skywire_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t skywire_init ( skywire_t *ctx, skywire_cfg_t *cfg );
```

- `skywire_cmd_run` This function sends a specified command to the Click module.
```c
void skywire_cmd_run ( skywire_t *ctx, uint8_t *cmd );
```

- `skywire_cmd_set` This function sets a value to a specified command of the Click module.
```c
void skywire_cmd_set ( skywire_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `skywire_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void skywire_cmd_get ( skywire_t *ctx, uint8_t *cmd );
```

- `skywire_send_sms_text` This function sends an SMS message to the selected phone number in text mode.
```c
void skywire_send_sms_text ( skywire_t *ctx, uint8_t *phone_number, uint8_t *sms_text );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    skywire_cfg_t skywire_cfg;  /**< Click config object. */

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
    skywire_cfg_setup( &skywire_cfg );
    SKYWIRE_MAP_MIKROBUS( skywire_cfg, MIKROBUS_POSITION_SKYWIRE );
    if ( UART_ERROR == skywire_init( &skywire, &skywire_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = SKYWIRE_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - SKYWIRE_POWER_UP:
   > Powers up the device and reads the device identification.
 - SKYWIRE_CONFIG_CONNECTION:
   > Sets configuration to device to be able to connect to the network.
 - SKYWIRE_CHECK_CONNECTION:
   > Waits for the network registration indicated via CREG command and then checks the signal quality report.
 - SKYWIRE_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - SKYWIRE_EXAMPLE:
   > Depending on the selected demo example, it sends a TCP/UDP message, an SMS message,
     performs a voice call or reads the GNSS position.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void ) 
{
    switch ( app_state )
    {
        case SKYWIRE_POWER_UP:
        {
            if ( SKYWIRE_OK == skywire_power_up( &skywire ) )
            {
                app_state = SKYWIRE_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_CONFIG_CONNECTION:
        {
            if ( SKYWIRE_OK == skywire_config_connection( &skywire ) )
            {
                app_state = SKYWIRE_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_CHECK_CONNECTION:
        {
            if ( SKYWIRE_OK == skywire_check_connection( &skywire ) )
            {
                app_state = SKYWIRE_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_CONFIG_EXAMPLE:
        {
            if ( SKYWIRE_OK == skywire_config_example( &skywire ) )
            {
                app_state = SKYWIRE_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_EXAMPLE:
        {
            skywire_example( &skywire );
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

> The example is tested with the NL-SW-HSPA (Telit HE910) Skywire modem and the power on pulse duration
and the AT#GPIO, AT#SLED, AT#DIALMODE, socket and GPS commands are specific for this modem.
In order for the examples to work, user needs to set the APN of the entered SIM card,
as well as the phone number to which he wants to send an SMS or to call.
Enter valid values for the following macros: SIM_APN, SIM_APN_USER, SIM_APN_PASSWORD and PHONE_NUMBER.
 > > Example:
 > > - SIM_APN "internet"
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
