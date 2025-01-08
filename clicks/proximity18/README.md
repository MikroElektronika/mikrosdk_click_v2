
---
# Proximity 18 Click

> [Proximity 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5300) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5300&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 18 Click board by reading and displaying the proximity data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity18

### Example Key Functions

- `proximity18_cfg_setup` Config Object Initialization function.
```c
void proximity18_cfg_setup ( proximity18_cfg_t *cfg );
```

- `proximity18_init` Initialization function.
```c
err_t proximity18_init ( proximity18_t *ctx, proximity18_cfg_t *cfg );
```

- `proximity18_default_cfg` Click Default Configuration function.
```c
err_t proximity18_default_cfg ( proximity18_t *ctx );
```

- `proximity18_start_measurement` This function starts the measurement by setting the one time trigger bit in the PS_CONF3_MS register.
```c
err_t proximity18_start_measurement ( proximity18_t *ctx );
```

- `proximity18_wait_for_data_ready` This function waits for the MPX data ready interrupt flag.
```c
err_t proximity18_wait_for_data_ready ( proximity18_t *ctx );
```

- `proximity18_read_proximity` This function reads the proximity data from all 3 sensors.
```c
err_t proximity18_read_proximity ( proximity18_t *ctx, uint16_t *ps1_data, uint16_t *ps2_data, uint16_t *ps3_data );
```

### Application Init

> Initializes the driver and logger, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity18_cfg_t proximity18_cfg;  /**< Click config object. */

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
    proximity18_cfg_setup( &proximity18_cfg );
    PROXIMITY18_MAP_MIKROBUS( proximity18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity18_init( &proximity18, &proximity18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY18_ERROR == proximity18_default_cfg ( &proximity18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the proximity data from 3 sensors in a multiplex mode and displays it on the USB UART
approximately once per second. The higher the proximity value, the closer the detected object is.

```c
void application_task ( void )
{
    uint16_t ps1_data, ps2_data, ps3_data;
    if ( PROXIMITY18_ERROR == proximity18_start_measurement ( &proximity18 ) )
    {
        log_error ( &logger, " Start measurement." );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( PROXIMITY18_ERROR == proximity18_wait_for_data_ready ( &proximity18 ) )
    {
        log_error ( &logger, " Wait for data ready." );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    if ( PROXIMITY18_ERROR == proximity18_read_proximity ( &proximity18, &ps1_data, &ps2_data, &ps3_data ) )
    {
        log_error ( &logger, " Read proximity." );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_printf ( &logger, " PS1 data: %u\r\n", ps1_data );
        log_printf ( &logger, " PS2 data: %u\r\n", ps2_data );
        log_printf ( &logger, " PS3 data: %u\r\n\n", ps3_data );
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
