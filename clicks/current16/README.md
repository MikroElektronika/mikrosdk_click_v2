
---
# Current 16 Click

> [Current 16 Click](https://www.mikroe.com/?pid_product=MIKROE-6790) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6790&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Current 16 Click board by reading and displaying the input current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current16

### Example Key Functions

- `current16_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void current16_cfg_setup ( current16_cfg_t *cfg );
```

- `current16_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t current16_init ( current16_t *ctx, current16_cfg_t *cfg );
```

- `current16_calib_offset` This function calibrates the zero current offset value.
```c
err_t current16_calib_offset ( current16_t *ctx );
```

- `current16_calib_resolution` This function calibrates the data resolution at the known load current.
```c
err_t current16_calib_resolution ( current16_t *ctx, float calib_current );
```

- `current16_read_current` This function reads the input current level [A].
```c
err_t current16_read_current ( current16_t *ctx, float *current );
```

### Application Init

> Initializes the driver and calibrates the zero current offset and data resolution at 3A load current.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current16_cfg_t current16_cfg;  /**< Click config object. */

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
    current16_cfg_setup( &current16_cfg );
    CURRENT16_MAP_MIKROBUS( current16_cfg, MIKROBUS_1 );
    if ( CURRENT16_OK != current16_init( &current16, &current16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating zero current offset in 5 seconds...\r\n" );
    log_printf( &logger, " Make sure no current flows through the sensor during the calibration process.\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT16_ERROR == current16_calib_offset ( &current16 ) )
    {
        log_error( &logger, " Calibrate offset." );
        for ( ; ; );
    }
    log_printf( &logger, " Offset calibration DONE.\r\n\n" );

    log_printf( &logger, " Calibrating data resolution in 5 seconds...\r\n" );
    log_printf( &logger, " Keep the load current set at %.1f A during the calibration process.\r\n", 
                CURRENT16_CALIBRATING_CURRENT );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( CURRENT16_ERROR == current16_calib_resolution ( &current16, CURRENT16_CALIBRATING_CURRENT ) )
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
    if ( CURRENT16_OK == current16_read_current ( &current16, &current ) ) 
    {
        log_printf( &logger, " Current : %.1f A\r\n\n", current );
    }
    Delay_ms ( 1000 );
}
```

### Note

> The measurement range is approximately: +/- 12A.

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
