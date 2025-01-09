
---
# Piezo Accel Click

> [Piezo Accel Click](https://www.mikroe.com/?pid_product=MIKROE-4559) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4559&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This application demonstrates the performance of Piezo Accel Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PiezoAccel

### Example Key Functions

- `piezoaccel_cfg_setup` Config Object Initialization function.
```c
void piezoaccel_cfg_setup ( piezoaccel_cfg_t *cfg );
```

- `piezoaccel_init` Initialization function.
```c
err_t piezoaccel_init ( piezoaccel_t *ctx, piezoaccel_cfg_t *cfg );
```

- `piezoaccel_default_cfg` Click Default Configuration function.
```c
void piezoaccel_default_cfg ( piezoaccel_t *ctx );
```

- `piezoaccel_adc_raw_read` Piezo Accel read raw adc function.
```c
uint16_t piezoaccel_adc_raw_read ( piezoaccel_t *ctx );
```

- `piezoaccel_adc_voltage_read` Piezo Accel read adc converted to voltage function.
```c
float piezoaccel_adc_voltage_read ( piezoaccel_t *ctx );
```

- `piezoaccel_g_unit_read` Piezo Accel read force of acceleration function.
```c
float piezoaccel_g_unit_read ( piezoaccel_t *ctx, piezoaccel_setup_t *cfg_data );
```

### Application Init

>  The initialization of UART LOG and SPI Click drivers.
Additionally, a default config is performed for
"out of the box" Piezo Accel Click settings.
Calibration is optional and is used to correct
the power supply offset of the sensor.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    piezoaccel_cfg_t piezoaccel_cfg;    /**< Click config object. */

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

    piezoaccel_cfg_setup( &piezoaccel_cfg );
    PIEZOACCEL_MAP_MIKROBUS( piezoaccel_cfg, MIKROBUS_1 );
    err_t init_flag = piezoaccel_init( &piezoaccel, &piezoaccel_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    piezoaccel_default_cfg( &piezoaccel, &setup_cfg_data );
    log_info( &logger, " Application Task " );
    Delay_ms ( 200 );
}
```

### Application Task

>  The ADC is constantly read and converted to a
g-force acceleration unit. Data is sent via LOG
every 20 ms and works on MikroPlot for graphical
representation of the sensor results.

```c
void application_task ( void ) 
{
    float read_val;
    
    read_val = piezoaccel_g_unit_read( &piezoaccel, &setup_cfg_data );
    log_printf( &logger, "%.2f,%.2f\r\n", read_val, time_var );
    time_var += time_incr;
    Delay_ms ( time_incr );
}
```

### Note

>  This demo app is intended to be used with MikroPlot data
visualization tool for clear understanding of the results.
https://www.mikroe.com/mikroplot-data-visualization-tool

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
