
---
# Current 11 Click

> [Current 11 Click](https://www.mikroe.com/?pid_product=MIKROE-6166) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6166&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2024.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Current 11 Click board by reading and displaying the input current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current11

### Example Key Functions

- `current11_cfg_setup` Config Object Initialization function.
```c
void current11_cfg_setup ( current11_cfg_t *cfg );
```

- `current11_init` Initialization function.
```c
err_t current11_init ( current11_t *ctx, current11_cfg_t *cfg );
```

- `current11_set_vref` This function sets the voltage reference for Current 11 Click driver.
```c
err_t current11_set_vref ( current11_t *ctx, float vref );
```

- `current11_calibrate_offset` This function calibrates the zero current offset value.
```c
err_t current11_calibrate_offset ( current11_t *ctx );
```

- `current11_read_current` This function reads the input current level [A] based on CURRENT11_NUM_CONVERSIONS of voltage measurements.
```c
err_t current11_read_current ( current11_t *ctx, float *current );
```

### Application Init

> Initializes the driver and calibrates the zero current offset.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current11_cfg_t current11_cfg;  /**< Click config object. */

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
    current11_cfg_setup( &current11_cfg );
    CURRENT11_MAP_MIKROBUS( current11_cfg, MIKROBUS_1 );
    err_t init_flag = current11_init( &current11, &current11_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( CURRENT11_ERROR == current11_calibrate_offset ( &current11 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Calibration DONE.\r\n" );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input current measurements and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    float current = 0;
    if ( CURRENT11_OK == current11_read_current ( &current11, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
        Delay_ms ( 1000 );
    }
}
```

### Note

> For better accuracy, set the voltage reference by using the current11_set_vref function,
increase the number of conversions by modifying the CURRENT11_NUM_CONVERSIONS macro, 
and adjust the CURRENT11_COUPLING_FACTOR_G_A value.

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
