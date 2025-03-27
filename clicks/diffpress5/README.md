
---
# Diff Press 5 Click

> [Diff Press 5 Click](https://www.mikroe.com/?pid_product=MIKROE-6527) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6527&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Diff Press 5 Click board. It showcases how to initialize the device, 
calibrate the zero-pressure offset, and read the differential pressure data in Pascals (Pa) from the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DiffPress5

### Example Key Functions

- `diffpress5_cfg_setup` Config Object Initialization function.
```c
void diffpress5_cfg_setup ( diffpress5_cfg_t *cfg );
```

- `diffpress5_init` Initialization function.
```c
err_t diffpress5_init ( diffpress5_t *ctx, diffpress5_cfg_t *cfg );
```

- `diffpress5_default_cfg` Click Default Configuration function.
```c
err_t diffpress5_default_cfg ( diffpress5_t *ctx );
```

- `diffpress5_calib_offset` This function calibrates the zero current offset value.
```c
err_t diffpress5_calib_offset ( diffpress5_t *ctx );
```

- `diffpress5_read_vout_avg` This function reads a desired number of sensor voltage output samples and averages it.
```c
err_t diffpress5_read_vout_avg ( diffpress5_t *ctx, uint16_t num_conv, float *vout_avg );
```

- `diffpress5_read_pressure` This function reads the differential pressure measurement.
```c
err_t diffpress5_read_pressure ( diffpress5_t *ctx, uint16_t *pressure );
```

### Application Init

> Initializes the logger and the Diff Press 5 Click driver. The application then performs zero-pressure 
offset calibration to ensure accurate pressure measurements. During the calibration, it is crucial to avoid 
applying pressure to the sensor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    diffpress5_cfg_t diffpress5_cfg;  /**< Click config object. */

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
    diffpress5_cfg_setup( &diffpress5_cfg );
    DIFFPRESS5_MAP_MIKROBUS( diffpress5_cfg, MIKROBUS_1 );
    err_t init_flag = diffpress5_init( &diffpress5, &diffpress5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating zero pressure offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no pressure is applied to the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( DIFFPRESS5_ERROR == diffpress5_calib_offset ( &diffpress5 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the differential pressure from the sensor and logs the values in Pascals (Pa).

```c
void application_task ( void )
{
    uint16_t pressure = 0;
    if ( DIFFPRESS5_OK == diffpress5_read_pressure ( &diffpress5, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %u Pa\r\n\n", pressure );
    }
}
```

### Note

> The measurable pressure range of the sensor is 0 to 10000 Pa.

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
