
---
# PAC1711 Click

> [PAC1711 Click](https://www.mikroe.com/?pid_product=MIKROE-6801) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6801&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the PAC1711 Click board for 
current, voltage, and power monitoring. The application reads and 
logs bus voltage, sense current, power values, as well as min/max 
and average measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1711

### Example Key Functions

- `pac1711_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pac1711_cfg_setup ( pac1711_cfg_t *cfg );
```

- `pac1711_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pac1711_init ( pac1711_t *ctx, pac1711_cfg_t *cfg );
```

- `pac1711_default_cfg` This function executes a default configuration of PAC1711 Click board.
```c
err_t pac1711_default_cfg ( pac1711_t *ctx );
```

- `pac1711_set_fsr` This function configures full-scale ranges (FSR) for V(SENSE) and V(BUS).
```c
err_t pac1711_set_fsr ( pac1711_t *ctx, uint8_t vsense_fsr, uint8_t vbus_fsr );
```

- `pac1711_refresh` This function issues a REFRESH command to update measurement registers.
```c
err_t pac1711_refresh ( pac1711_t *ctx );
```

- `pac1711_read_data` This function reads accumulated count, voltage, current, and power data, and converts raw codes into SI units, storing the results to the output structure.
```c
err_t pac1711_read_data ( pac1711_t *ctx, pac1711_data_t *data_out );
```

### Application Init

> Initializes the logger and PAC1711 Click driver, then applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1711_cfg_t pac1711_cfg;  /**< Click config object. */

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
    pac1711_cfg_setup( &pac1711_cfg );
    PAC1711_MAP_MIKROBUS( pac1711_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pac1711_init( &pac1711, &pac1711_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PAC1711_ERROR == pac1711_default_cfg ( &pac1711 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically refreshes the measurements and logs voltage, current, and power data. Updates are provided every second.

```c
void application_task ( void )
{
    pac1711_data_t meas_data;
    if ( PAC1711_OK == pac1711_refresh ( &pac1711 ) )
    {
        Delay_ms ( 1 );
        if ( PAC1711_OK == pac1711_read_data ( &pac1711, &meas_data ) )
        {
            log_printf ( &logger, " ACC_COUNT: %lu\r\n", meas_data.acc_count );
            log_printf ( &logger, " ACC_DATA: 0x%.6LX%.8LX\r\n", meas_data.acc_data_msb, meas_data.acc_data_lsb );
            log_printf ( &logger, " VBUS: %.3f V\r\n", meas_data.vbus );
            log_printf ( &logger, " ISENSE: %.3f A\r\n", meas_data.isense );
            log_printf ( &logger, " VBUS_AVG: %.3f V\r\n", meas_data.vbus_avg );
            log_printf ( &logger, " ISENSE_AVG: %.3f A\r\n", meas_data.isense_avg );
            log_printf ( &logger, " POWER: %.3f W\r\n", meas_data.power );
            log_printf ( &logger, " VBUS_MIN: %.3f V\r\n", meas_data.vbus_min );
            log_printf ( &logger, " VBUS_MAX: %.3f V\r\n", meas_data.vbus_max );
            log_printf ( &logger, " ISENSE_MIN: %.3f A\r\n", meas_data.isense_min );
            log_printf ( &logger, " ISENSE_MAX: %.3f A\r\n", meas_data.isense_max );
            log_printf ( &logger, " POWER_MIN: %.3f W\r\n", meas_data.power_min );
            log_printf ( &logger, " POWER_MAX: %.3f W\r\n\n", meas_data.power_max );
            Delay_ms ( 1000 );
        }
    }
}
```

### Note

> Ensure that the PAC1711 Click is properly connected to measure the target load current and supply voltage.

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
