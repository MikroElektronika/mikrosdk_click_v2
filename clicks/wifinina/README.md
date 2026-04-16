
---
# WiFi NINA Click

> [WiFi NINA Click](https://www.mikroe.com/?pid_product=MIKROE-2921) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2921&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Feb 2026.
- **Type**          : UART type

# Software Support

## Example Description

> Application example shows device capability of connecting to a WiFi network and
sending TCP/UDP messages to an echo server.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.WiFiNINA

### Example Key Functions

- `wifinina_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void wifinina_cfg_setup ( wifinina_cfg_t *cfg );
```

- `wifinina_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t wifinina_init ( wifinina_t *ctx, wifinina_cfg_t *cfg );
```

- `wifinina_hw_reset` This function resets the device by toggling the RST pin state.
```c
void wifinina_hw_reset ( wifinina_t *ctx );
```

- `wifinina_cmd_run` This function sends a specified command to the Click module.
```c
void wifinina_cmd_run ( wifinina_t *ctx, uint8_t *cmd );
```

- `wifinina_cmd_set` This function sets a value to a specified command of the Click module.
```c
void wifinina_cmd_set ( wifinina_t *ctx, uint8_t *cmd, uint8_t *value );
```

- `wifinina_cmd_get` This function is used to get the value of a given command from the Click module.
```c
void wifinina_cmd_get ( wifinina_t *ctx, uint8_t *cmd );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    wifinina_cfg_t wifinina_cfg;  /**< Click config object. */

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
    wifinina_cfg_setup( &wifinina_cfg );
    WIFININA_MAP_MIKROBUS( wifinina_cfg, MIKROBUS_POSITION_WIFININA );
    if ( UART_ERROR == wifinina_init( &wifinina, &wifinina_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );

    app_state = WIFININA_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}
```

### Application Task

> Application task is split in few stages:
 - WIFININA_POWER_UP: 
   > Powers up the device, performs a factory reset and reads system information.
 - WIFININA_CONFIGURE_CONNECTION: 
   > Configures connection to WiFi.
 - WIFININA_WAIT_FOR_CONNECTION:
   > Checks the connection to WiFi access point.
 - WIFININA_EXAMPLE:
   > Sends a TCP/UDP message to an echo server over a WiFi network.

```c
void application_task ( void )
{
    switch ( app_state )
    {
        case WIFININA_POWER_UP:
        {
            if ( WIFININA_OK == wifinina_power_up( &wifinina ) )
            {
                app_state = WIFININA_CONFIGURE_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIGURE CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case WIFININA_CONFIGURE_CONNECTION:
        {
            if ( WIFININA_OK == wifinina_config_connection( &wifinina ) )
            {
                app_state = WIFININA_WAIT_FOR_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case WIFININA_WAIT_FOR_CONNECTION:
        {
            if ( WIFININA_OK == wifinina_check_connection( &wifinina ) )
            {
                app_state = WIFININA_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case WIFININA_EXAMPLE:
        {
            wifinina_example( &wifinina );
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
