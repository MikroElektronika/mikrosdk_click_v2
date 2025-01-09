
---
# VCP Monitor 4 Click

> [VCP Monitor 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4763) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4763&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jul 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example application showcases ability of Click board
to be configured for different readings and read temperature, 
voltage, current and power.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPMonitor4

### Example Key Functions

- `vcpmonitor4_cfg_setup` Config Object Initialization function.
```c
void vcpmonitor4_cfg_setup ( vcpmonitor4_cfg_t *cfg );
```

- `vcpmonitor4_init` Initialization function.
```c
err_t vcpmonitor4_init ( vcpmonitor4_t *ctx, vcpmonitor4_cfg_t *cfg );
```

- `vcpmonitor4_default_cfg` Click Default Configuration function.
```c
err_t vcpmonitor4_default_cfg ( vcpmonitor4_t *ctx );
```

- `vcpmonitor4_get_vbus` Get BUS voltage.
```c
err_t vcpmonitor4_get_vbus ( vcpmonitor4_t *ctx, float *vbus )
```

- `vcpmonitor4_get_current` Get Current.
```c
err_t vcpmonitor4_get_current ( vcpmonitor4_t *ctx, float *current )
```

- `vcpmonitor4_get_power` Get Shunt voltage.
```c
err_t vcpmonitor4_get_power ( vcpmonitor4_t *ctx, float *power )
```

### Application Init

> Initialization of communication modules (SPI, UART) and 
additional alert pin. Reads Manufacturer and Device ID,
Configurates device for reading all device measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor4_cfg_t vcpmonitor4_cfg;  /**< Click config object. */

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
    vcpmonitor4_cfg_setup( &vcpmonitor4_cfg );
    VCPMONITOR4_MAP_MIKROBUS( vcpmonitor4_cfg, MIKROBUS_1 );
    err_t init_flag  = vcpmonitor4_init( &vcpmonitor4, &vcpmonitor4_cfg );
    VCPMONITOR4_SET_DATA_SAMPLE_EDGE
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    uint32_t temp_data = 0;
    vcpmonitor4_generic_read( &vcpmonitor4, VCPMONITOR4_REG_MANUFACTURER_ID, &temp_data );
    log_printf( &logger, " > Manufacturer ID: \t0x%.4X\r\n", temp_data );
    
    vcpmonitor4_generic_read( &vcpmonitor4, VCPMONITOR4_REG_DEVICE_ID, &temp_data );
    log_printf( &logger, " > Device ID: \t\t0x%.4X\r\n", temp_data );
    
    vcpmonitor4_default_cfg ( &vcpmonitor4 );
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> In span of 500ms reads and calculates data for IC temperature,
Bus voltage in V, Shunt voltage in mV, and current and power for device.

```c
void application_task ( void )
{
    float read_data;
    vcpmonitor4_get_temperature( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Temperature:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_vbus( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Vbus[V]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_vshunt( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Vshunt[mV]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_current( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Current[A]:\t%.2f \r\n", read_data );
    
    vcpmonitor4_get_power( &vcpmonitor4, &read_data );
    log_printf( &logger, " > Power[W]:\t%.2f \r\n", read_data );
    log_printf( &logger, "*************************\r\n" );
    
    Delay_ms ( 500 );
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
