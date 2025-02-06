
---
# LightRanger 13 Click

> [LightRanger 13 Click](https://www.mikroe.com/?pid_product=MIKROE-6479) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6479&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This application demonstrates the usage of the LightRanger 13 Click for distance measurement and monitoring.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger13

### Example Key Functions

- `lightranger13_cfg_setup` Config Object Initialization function.
```c
void lightranger13_cfg_setup ( lightranger13_cfg_t *cfg );
```

- `lightranger13_init` Initialization function.
```c
err_t lightranger13_init ( lightranger13_t *ctx, lightranger13_cfg_t *cfg );
```

- `lightranger13_default_cfg` Click Default Configuration function.
```c
err_t lightranger13_default_cfg ( lightranger13_t *ctx );
```

- `lightranger13_set_threshold` This function sets a threshold level and interrupt persistance.
```c
err_t lightranger13_set_threshold ( lightranger13_t *ctx, uint16_t t_low, uint16_t t_high, uint8_t persistance );
```

- `lightranger13_start_measurement` This function starts a measurement (the configuration, factory calibration and state data are used from context object).
```c
err_t lightranger13_start_measurement ( lightranger13_t *ctx );
```

- `lightranger13_read_result` This function reads the measurement results.
```c
err_t lightranger13_read_result ( lightranger13_t *ctx, lightranger13_meas_result_t *result );
```

### Application Init

> Initializes the logger and LightRanger 13 Click with default configuration,
displays device information, performs factory calibration (if enabled), and sets up
distance measurement thresholds (1mm-1000mm) with persistence (5 consecutive times)
to ensure reliable readings. It then starts the measurement process.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger13_cfg_t lightranger13_cfg;  /**< Click config object. */

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
    lightranger13_cfg_setup( &lightranger13_cfg );
    LIGHTRANGER13_MAP_MIKROBUS( lightranger13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger13_init( &lightranger13, &lightranger13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER13_ERROR == lightranger13_default_cfg ( &lightranger13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf( &logger, "--- DEVICE INFO ---\r\n" );
    log_printf( &logger, " App version: %u.%u.%u.%u\r\n",
                ( uint16_t ) lightranger13.info.app_ver[ 0 ], 
                ( uint16_t ) lightranger13.info.app_ver[ 1 ], 
                ( uint16_t ) lightranger13.info.app_ver[ 2 ], 
                ( uint16_t ) lightranger13.info.app_ver[ 3 ] );
    log_printf( &logger, " Chip version: %u.%u\r\n",
                ( uint16_t ) lightranger13.info.chip_ver[ 0 ], 
                ( uint16_t ) lightranger13.info.chip_ver[ 1 ] );
    log_printf( &logger, " Serial number: %.8LX\r\n\n", lightranger13.info.serial_num );
    Delay_ms ( 1000 );

#ifndef FACTORY_CALIBRATION_DISABLE
    log_printf( &logger, "--- FACTORY CALIBRATION ---\r\n" );
    log_printf( &logger, " Calibration environment:\r\n" );
    log_printf( &logger, " - Device has to be in the final (correct) optical stack\r\n" );
    Delay_ms ( 10 );
    log_printf( &logger, " - Cover glass (no smudge on the glass) in front of the device\r\n" );
    log_printf( &logger, " - No target in front of the device within 40cm\r\n" );
    log_printf( &logger, " - Dark room or low ambient light\r\n" );
    log_printf( &logger, " Performing factory calibration in 5 seconds...\r\n" );
    for ( uint8_t cnt = 5; cnt > 0; cnt-- )
    {
        log_printf( &logger, " %u\r\n", ( uint16_t ) cnt );
        Delay_ms ( 1000 );
    }
    if ( LIGHTRANGER13_ERROR == lightranger13_factory_calib ( &lightranger13 ) )
    {
        log_error( &logger, " Factory calibration." );
        for ( ; ; );
    }
    log_printf( &logger, " Factory calibration DONE.\r\n\n" );
    Delay_ms ( 1000 );
#endif

    log_printf( &logger, "--- THRESHOLD AND PERSISTANCE ---\r\n" );
    log_printf( &logger, " Setting threshold: 1mm-1000mm; and persistance: 5 times\r\n" );
    if ( LIGHTRANGER13_ERROR == lightranger13_set_threshold ( &lightranger13, 1, 1000, 5 ) )
    {
        log_error( &logger, " Set threshold." );
        for ( ; ; );
    }
    log_printf( &logger, " Set threshold DONE.\r\n\n" );
    Delay_ms ( 1000 );

    log_printf( &logger, "--- STARTING MEASUREMENT ---\r\n" );
    if ( LIGHTRANGER13_ERROR == lightranger13_start_measurement ( &lightranger13 ) )
    {
        log_error( &logger, " Start measurement." );
        for ( ; ; );
    }
    log_printf( &logger, " Measurement started.\r\n\n" );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt signal, indicating a new measurement is available.
Upon receiving the signal, it reads the distance and temperature data from the sensor
and logs the values to USB UART.

```c
void application_task ( void )
{
    lightranger13_meas_result_t result;
    // Wait for data ready interrupt
    while ( lightranger13_get_int_pin ( &lightranger13 ) );

    lightranger13_clear_interrupts ( &lightranger13 );
    
    if ( LIGHTRANGER13_OK == lightranger13_read_result ( &lightranger13, &result ) )
    {
        log_printf( &logger, " Distance: %u mm\r\n", result.dist_peak );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) result.temperature );
    }
}
```

### Note

> The factory calibration step can be enabled or disabled by commenting/uncommenting the `FACTORY_CALIBRATION_DISABLE` macro.

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
