
---
# Charger 30 Click

> [Charger 30 Click](https://www.mikroe.com/?pid_product=MIKROE-6610) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6610&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Charger 30 Click board by reading and logging
the charging status, input and battery voltage, current consumption, and fault diagnostics.
The demo configures the default setup and then periodically polls for system status
and fault information.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger30

### Example Key Functions

- `charger30_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void charger30_cfg_setup ( charger30_cfg_t *cfg );
```

- `charger30_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t charger30_init ( charger30_t *ctx, charger30_cfg_t *cfg );
```

- `charger30_default_cfg` This function executes a default configuration of Charger 30 Click board.
```c
err_t charger30_default_cfg ( charger30_t *ctx );
```

- `charger30_read_status` This function reads multiple status and monitoring registers and stores the values into the provided status structure.
```c
err_t charger30_read_status ( charger30_t *ctx, charger30_status_t *status );
```

### Application Init

> Initializes the logger and the Charger 30 Click driver and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger30_cfg_t charger30_cfg;  /**< Click config object. */

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
    charger30_cfg_setup( &charger30_cfg );
    CHARGER30_MAP_MIKROBUS( charger30_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == charger30_init( &charger30, &charger30_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CHARGER30_ERROR == charger30_default_cfg ( &charger30 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads and logs charger status and fault registers along with voltage, current.

```c
void application_task ( void )
{
    charger30_status_t status;
    if ( CHARGER30_OK == charger30_read_status ( &charger30, &status ) )
    {
        charger30_display_status ( status.status );
        charger30_display_fault ( status.fault );
        log_printf ( &logger, " VBAT: %u mV\r\n", status.vbat );
        log_printf ( &logger, " VSYS: %u mV\r\n", status.vsys );
        log_printf ( &logger, " NTC: %.1f %%\r\n", status.ntc );
        log_printf ( &logger, " VIN: %u mV\r\n", status.vin );
        log_printf ( &logger, " Ichg: %.1f mA\r\n", status.ichg );
        log_printf ( &logger, " Iin: %.1f mA\r\n", status.iin );
        log_printf ( &logger, " Iin_dpm: %u mA\r\n\n", status.iin_dpm );
    }
    Delay_ms ( 1000 );
}
```

### Note

> Ensure a valid power supply and a battery are connected for proper functionality.

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
