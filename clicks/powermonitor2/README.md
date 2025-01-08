
---
# Power Monitor 2 Click

> [Power Monitor 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6202) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6202&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Power Monitor 2 Click by reading and displaying the power consumption at 3V3 and 5V of the connected Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMonitor2

### Example Key Functions

- `powermonitor2_cfg_setup` Config Object Initialization function.
```c
void powermonitor2_cfg_setup ( powermonitor2_cfg_t *cfg );
```

- `powermonitor2_init` Initialization function.
```c
err_t powermonitor2_init ( powermonitor2_t *ctx, powermonitor2_cfg_t *cfg );
```

- `powermonitor2_default_cfg` Click Default Configuration function.
```c
err_t powermonitor2_default_cfg ( powermonitor2_t *ctx );
```

- `powermonitor2_set_address` This function sets the device slave address.
```c
err_t powermonitor2_set_address ( powermonitor2_t *ctx, uint8_t slave_address );
```

- `powermonitor2_read_data` This function reads the shunt voltage, bus voltage, current, and power data measurements.
```c
err_t powermonitor2_read_data ( powermonitor2_t *ctx, powermonitor2_data_t *data_out );
```

- `powermonitor2_read_data_avg` This function reads the shunt voltage, bus voltage, current, and power data measurements averaged from num_conv samples.
```c
err_t powermonitor2_read_data_avg ( powermonitor2_t *ctx, uint16_t num_conv, powermonitor2_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    powermonitor2_cfg_t powermonitor2_cfg;  /**< Click config object. */

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
    powermonitor2_cfg_setup( &powermonitor2_cfg );
    POWERMONITOR2_MAP_MIKROBUS( powermonitor2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == powermonitor2_init( &powermonitor2, &powermonitor2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( POWERMONITOR2_ERROR == powermonitor2_default_cfg ( &powermonitor2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage, current, and power measurements from U2 and U3 sensors averaged from 20 samples and displays the results on the USB UART.

```c
void application_task ( void )
{
    powermonitor2_data_t pm_3v3, pm_5v;

    powermonitor2_set_address ( &powermonitor2, powermonitor2.address_3v3 );
    if ( POWERMONITOR2_OK == powermonitor2_read_data_avg ( &powermonitor2, POWERMONITOR2_DEFAULT_NUM_CONV, &pm_3v3 ) )
    {
        log_printf( &logger, " --- 3V3 Power Monitor ---\r\n" );
        log_printf( &logger, " Voltage: %.3f V\r\n", pm_3v3.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", pm_3v3.current );
        log_printf( &logger, " Power: %.2f W\r\n", pm_3v3.power );
        log_printf( &logger, " -------------------------\r\n" );
    }
    
    powermonitor2_set_address ( &powermonitor2, powermonitor2.address_5v );
    if ( POWERMONITOR2_OK == powermonitor2_read_data_avg ( &powermonitor2, POWERMONITOR2_DEFAULT_NUM_CONV, &pm_5v ) )
    {
        log_printf( &logger, " ---- 5V Power Monitor ---\r\n" );
        log_printf( &logger, " Voltage: %.3f V\r\n", pm_5v.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", pm_5v.current );
        log_printf( &logger, " Power: %.2f W\r\n", pm_5v.power );
        log_printf( &logger, " -------------------------\r\n" );
    }

    Delay_ms ( 1000 );
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
