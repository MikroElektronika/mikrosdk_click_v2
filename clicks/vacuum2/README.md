
---
# Vacuum 2 Click

> [Vacuum 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6528) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6528&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Vacuum 2 Click board. It showcases how to initialize the device, 
perform zero-pressure offset calibration, and measure pressure in Pascals (Pa).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Vacuum2

### Example Key Functions

- `vacuum2_cfg_setup` Config Object Initialization function.
```c
void vacuum2_cfg_setup ( vacuum2_cfg_t *cfg );
```

- `vacuum2_init` Initialization function.
```c
err_t vacuum2_init ( vacuum2_t *ctx, vacuum2_cfg_t *cfg );
```

- `vacuum2_calib_offset` This function calibrates the zero current offset value.
```c
err_t vacuum2_calib_offset ( vacuum2_t *ctx );
```

- `vacuum2_read_vout_avg` This function reads a desired number of sensor voltage output samples and averages it.
```c
err_t vacuum2_read_vout_avg ( vacuum2_t *ctx, uint16_t num_conv, float *vout_avg );
```

- `vacuum2_read_pressure` This function reads the pressure measurement.
```c
err_t vacuum2_read_pressure ( vacuum2_t *ctx, int16_t *pressure );
```

### Application Init

> Initializes the logger and the Vacuum 2 Click driver. The application then performs zero-pressure 
offset calibration to ensure accurate pressure measurements. During the calibration, it is crucial to avoid 
applying pressure to the sensor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vacuum2_cfg_t vacuum2_cfg;  /**< Click config object. */

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
    vacuum2_cfg_setup( &vacuum2_cfg );
    VACUUM2_MAP_MIKROBUS( vacuum2_cfg, MIKROBUS_1 );
    err_t init_flag = vacuum2_init( &vacuum2, &vacuum2_cfg );
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
    if ( VACUUM2_ERROR == vacuum2_calib_offset ( &vacuum2 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads the pressure from the sensor and logs the values in Pascals (Pa).

```c
void application_task ( void )
{
    int16_t pressure = 0;
    if ( VACUUM2_OK == vacuum2_read_pressure ( &vacuum2, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %d Pa\r\n\n", pressure );
    }
}
```

### Note

> The measurable pressure range of the sensor is from -2000 Pa to 2000 Pa.

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
