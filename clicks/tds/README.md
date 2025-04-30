
---
# TDS Click

> [TDS Click](https://www.mikroe.com/?pid_product=MIKROE-6597) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6597&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the usage of the TDS Click board, which measures the Total 
Dissolved Solids (TDS) in water. The application initializes the TDS Click board, 
establishes communication, and continuously reads the TDS value in parts per million (ppm).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.TDS

### Example Key Functions

- `tds_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void tds_cfg_setup ( tds_cfg_t *cfg );
```

- `tds_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t tds_init ( tds_t *ctx, tds_cfg_t *cfg );
```

- `tds_set_vref` This function sets the voltage reference for TDS Click driver.
```c
err_t tds_set_vref ( tds_t *ctx, float vref );
```

- `tds_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t tds_read_voltage_avg ( tds_t *ctx, uint16_t num_conv, float *voltage_avg );
```

- `tds_read_ppm` This function reads the TDS measurement value in ppm.
```c
err_t tds_read_ppm ( tds_t *ctx, float *data_out );
```

### Application Init

> Initializes the logger and configures the TDS Click board. It sets up communication 
using either ADC or I2C, verifies proper initialization, and prepares the device for measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tds_cfg_t tds_cfg;  /**< Click config object. */

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
    tds_cfg_setup( &tds_cfg );
    TDS_MAP_MIKROBUS( tds_cfg, MIKROBUS_1 );
    err_t init_flag = tds_init( &tds, &tds_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the TDS value from the sensor and logs it in ppm (parts per million).

```c
void application_task ( void )
{
    float tds_ppm = 0;
    if ( TDS_OK == tds_read_ppm ( &tds, &tds_ppm ) ) 
    {
        log_printf( &logger, " TDS Value : %.1f ppm\r\n\n", tds_ppm );
        Delay_ms ( 1000 );
    }
}
```

### Note

> Ensure a proper TDS probe is attached to the Click board for accurate measurements.

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
