
---
# LightRanger 10 Click

> [LightRanger 10 Click](https://www.mikroe.com/?pid_product=MIKROE-5206) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5206&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of LightRanger 10 Click board by reading and displaying the target object distance in millimeters.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger10

### Example Key Functions

- `lightranger10_cfg_setup` Config Object Initialization function.
```c
void lightranger10_cfg_setup ( lightranger10_cfg_t *cfg );
```

- `lightranger10_init` Initialization function.
```c
err_t lightranger10_init ( lightranger10_t *ctx, lightranger10_cfg_t *cfg );
```

- `lightranger10_default_cfg` Click Default Configuration function.
```c
err_t lightranger10_default_cfg ( lightranger10_t *ctx );
```

- `lightranger10_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t lightranger10_get_int_pin ( lightranger10_t *ctx );
```

- `lightranger10_clear_interrupts` This function clears the interrupts.
```c
err_t lightranger10_clear_interrupts ( lightranger10_t *ctx );
```

- `lightranger10_get_distance` This function reads the target object distance in millimeters.
```c
err_t lightranger10_get_distance ( lightranger10_t *ctx, uint16_t *distance_mm );
```

### Application Init

> Initializes the driver, performs the Click default configuration, and then calibrates the sensor to the object positioned at 200mm distance from the sensor.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger10_cfg_t lightranger10_cfg;  /**< Click config object. */

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
    lightranger10_cfg_setup( &lightranger10_cfg );
    LIGHTRANGER10_MAP_MIKROBUS( lightranger10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger10_init( &lightranger10, &lightranger10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER10_ERROR == lightranger10_default_cfg ( &lightranger10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_printf( &logger, " --- Sensor calibration --- \r\n" );
    log_printf( &logger, " Place an object at 200mm distance from sensor in the next 5 seconds.\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " Sensor calibration is in progress...\r\n" );
    if ( LIGHTRANGER10_ERROR == lightranger10_calibrate_distance ( &lightranger10, 200 ) )
    {
        log_error( &logger, " Sensor calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then clears the interrupt and reads the target distance in millimeters and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    while ( lightranger10_get_int_pin ( &lightranger10 ) );
    
    uint16_t distance_mm;
    if ( ( LIGHTRANGER10_OK == lightranger10_clear_interrupts ( &lightranger10 ) ) && 
         ( LIGHTRANGER10_OK == lightranger10_get_distance ( &lightranger10, &distance_mm ) ) )
    {
        log_printf ( &logger, " Distance: %u mm \r\n\n", distance_mm );
    }
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
