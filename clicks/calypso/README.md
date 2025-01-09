
---
# Calypso Click

> [Calypso Click](https://www.mikroe.com/?pid_product=MIKROE-6274) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6274&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2024.
- **Type**          : UART type

# Software Support

## Example Description

> This example demonstrates the use of Calypso Click board by processing the incoming data and displaying them on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Calypso

### Example Key Functions

- `calypso_cfg_setup` Config Object Initialization function.
```c
void calypso_cfg_setup ( calypso_cfg_t *cfg );
```

- `calypso_init` Initialization function.
```c
err_t calypso_init ( calypso_t *ctx, calypso_cfg_t *cfg );
```

- `calypso_default_cfg` Click Default Configuration function.
```c
err_t calypso_default_cfg ( calypso_t *ctx );
```

- `calypso_set_app_mode` This function is used to set selected APP mode of Calypso Click board.
```c
err_t calypso_set_app_mode ( calypso_t *ctx, uint8_t mode_sel );
```

- `calypso_hw_reset` This function is used to perform HW reset.
```c
void calypso_hw_reset ( calypso_t *ctx );
```

- `calypso_send_cmd` This function is used to send a desired command.
```c
void calypso_send_cmd ( calypso_t *ctx, uint8_t *at_cmd_buf );
```

### Application Init

> Initializes the driver and places AT command mode, tests the communication, and after that restarts the device, and performs example configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    calypso_cfg_t calypso_cfg;  /**< Click config object. */

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
    calypso_cfg_setup( &calypso_cfg );
    CALYPSO_MAP_MIKROBUS( calypso_cfg, MIKROBUS_1 );
    if ( UART_ERROR == calypso_init( &calypso, &calypso_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CALYPSO_ERROR == calypso_default_cfg ( &calypso ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    calypso_configure_for_example( );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> It creates a connection to the TCP-UDP echo server, sends a message to it reads it back, displaces it on the UART terminal, and then closes the connection.

```c
void application_task ( void ) 
{
    calypso_example( );
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
