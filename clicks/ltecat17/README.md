
---
# LTE Cat.1 7 Click

> [LTE Cat.1 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6434) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and
sending SMS or TCP/UDP messages, or retrieving data from GNSS using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTECat17

### Example Key Functions

- `ltecat17_cfg_setup` Config Object Initialization function.
```c
void ltecat17_cfg_setup ( ltecat17_cfg_t *cfg );
```

- `ltecat17_init` Initialization function.
```c
err_t ltecat17_init ( ltecat17_t *ctx, ltecat17_cfg_t *cfg );
```

- `ltecat17_set_sim_apn` This function sets APN for sim card.
```c
void ltecat17_set_sim_apn ( ltecat17_t *ctx, uint8_t *sim_apn );
```

- `ltecat17_cmd_run` This function sends a specified command to the Click module.
```c
void ltecat17_cmd_run ( ltecat17_t *ctx, uint8_t *cmd );
```

- `ltecat17_set_power_state` This function sets a desired power state by toggling PWR pin with a specific time for high state.
```c
void ltecat17_set_power_state ( ltecat17_t *ctx, uint8_t state );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ltecat17_cfg_t ltecat17_cfg;  /**< Click config object. */

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
    ltecat17_cfg_setup( &ltecat17_cfg );
    LTECAT17_MAP_MIKROBUS( ltecat17_cfg, MIKROBUS_1 );
    if ( UART_ERROR == ltecat17_init( &ltecat17, &ltecat17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = LTECAT17_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - LTECAT17_POWER_UP: 
   > Powers up the device, performs a device factory reset and reads system information.
 - LTECAT17_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network (used only for SMS or TCP/UDP demo examples).
 - LTECAT17_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report (used only for SMS or TCP/UDP demo examples).
 - LTECAT17_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - LTECAT17_EXAMPLE:
   > Depending on the selected demo example, it sends an SMS message (in PDU or TXT mode) or TCP/UDP message or waits for the GPS fix to retrieve location info from GNSS.
> By default, the TCP/UDP example is selected.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case LTECAT17_POWER_UP:
        {
            if ( LTECAT17_OK == ltecat17_power_up( &ltecat17 ) )
            {
                app_state = LTECAT17_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT17_CONFIG_CONNECTION:
        {
            if ( LTECAT17_OK == ltecat17_config_connection( &ltecat17 ) )
            {
                app_state = LTECAT17_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case LTECAT17_CHECK_CONNECTION:
        {
            if ( LTECAT17_OK == ltecat17_check_connection( &ltecat17 ) )
            {
                app_state = LTECAT17_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT17_CONFIG_EXAMPLE:
        {
            if ( LTECAT17_OK == ltecat17_config_example( &ltecat17 ) )
            {
                app_state = LTECAT17_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case LTECAT17_EXAMPLE:
        {
            ltecat17_example( &ltecat17 );
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
