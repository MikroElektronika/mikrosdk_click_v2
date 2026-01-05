
---
# NB IoT 7 Click

> [NB IoT 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6557) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6557&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to the network and sending TCP/UDP messages using standard "AT" commands.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NBIoT7

### Example Key Functions

- `nbiot7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void nbiot7_cfg_setup ( nbiot7_cfg_t *cfg );
```

- `nbiot7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t nbiot7_init ( nbiot7_t *ctx, nbiot7_cfg_t *cfg );
```

- `nbiot7_set_sim_apn` This function sets APN for sim card.
```c
void nbiot7_set_sim_apn ( nbiot7_t *ctx, uint8_t *sim_apn );
```

- `nbiot7_cmd_set` This function sets a value to a specified command of the Click module.
```c
void nbiot7_cmd_set ( nbiot7_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `nbiot7_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void nbiot7_cmd_get ( nbiot7_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot7_cfg_t nbiot7_cfg;  /**< Click config object. */

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
    nbiot7_cfg_setup( &nbiot7_cfg );
    NBIOT7_MAP_MIKROBUS( nbiot7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == nbiot7_init( &nbiot7, &nbiot7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = NBIOT7_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - NBIOT7_POWER_UP: 
   > Powers up the device, enables command echo, and reads system information.
 - NBIOT7_CONFIG_CONNECTION: 
   > Sets configuration to device to be able to connect to the network.
 - NBIOT7_CHECK_CONNECTION:
   > Waits for the network registration indicated via CEREG command and then checks the signal quality report.
 - NBIOT7_CONFIG_EXAMPLE:
   > Configures device for the selected example.
 - NBIOT7_EXAMPLE:
   > Sends a TCP/UDP message to the echo server.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case NBIOT7_POWER_UP:
        {
            if ( NBIOT7_OK == nbiot7_power_up( &nbiot7 ) )
            {
                app_state = NBIOT7_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_CONFIG_CONNECTION:
        {
            if ( NBIOT7_OK == nbiot7_config_connection( &nbiot7 ) )
            {
                app_state = NBIOT7_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_CHECK_CONNECTION:
        {
            if ( NBIOT7_OK == nbiot7_check_connection( &nbiot7 ) )
            {
                app_state = NBIOT7_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_CONFIG_EXAMPLE:
        {
            if ( NBIOT7_OK == nbiot7_config_example( &nbiot7 ) )
            {
                app_state = NBIOT7_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case NBIOT7_EXAMPLE:
        {
            nbiot7_example( &nbiot7 );
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

> In order for the example to work, user needs to set the SIM_APN of entered SIM card.

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
