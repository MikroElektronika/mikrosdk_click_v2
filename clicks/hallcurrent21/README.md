
---
# Hall Current 21 Click

> [Hall Current 21 Click](https://www.mikroe.com/?pid_product=MIKROE-6449) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6449&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Hall Current 21 Click board by reading and displaying the input current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent21

### Example Key Functions

- `hallcurrent21_cfg_setup` Config Object Initialization function.
```c
void hallcurrent21_cfg_setup ( hallcurrent21_cfg_t *cfg );
```

- `hallcurrent21_init` Initialization function.
```c
err_t hallcurrent21_init ( hallcurrent21_t *ctx, hallcurrent21_cfg_t *cfg );
```

- `hallcurrent21_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level of the selected input channel.
```c
err_t hallcurrent21_read_voltage_avg ( hallcurrent21_t *ctx, uint8_t channel, uint16_t num_conv, float *voltage_avg );
```

- `hallcurrent21_calib_resolution` This function reads the sensor voltage reference and calibrates the data resolution at a known load current.
```c
err_t hallcurrent21_calib_resolution ( hallcurrent21_t *ctx, float calib_current );
```

- `hallcurrent21_read_current` This function reads the input current level [A].
```c
err_t hallcurrent21_read_current ( hallcurrent21_t *ctx, float *current );
```

### Application Init

> Initializes the driver and calibrates the data resolution at 3A load current.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent21_cfg_t hallcurrent21_cfg;  /**< Click config object. */

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
    hallcurrent21_cfg_setup( &hallcurrent21_cfg );
    HALLCURRENT21_MAP_MIKROBUS( hallcurrent21_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == hallcurrent21_init( &hallcurrent21, &hallcurrent21_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at %.1fA during the calibration process.\r\n", 
                HALLCURRENT21_CALIBRATING_CURRENT );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( HALLCURRENT21_ERROR == hallcurrent21_calib_resolution ( &hallcurrent21, 
                                                                 HALLCURRENT21_CALIBRATING_CURRENT ) )
    {
        log_error( &logger, " Calibrate resolution." );
        for ( ; ; );
    }
    log_printf( &logger, " Data resolution calibration DONE.\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float current = 0;
    if ( HALLCURRENT21_OK == hallcurrent21_read_current ( &hallcurrent21, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
}
```

### Note

> The measurement range is approximately: +/- 65A.

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
