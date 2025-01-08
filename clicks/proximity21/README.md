
---
# Proximity 21 Click

> [Proximity 21 Click](https://www.mikroe.com/?pid_product=MIKROE-6286) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6286&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Proximity 21 Click board by reading and displaying the target distance in millimeters on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity21

### Example Key Functions

- `proximity21_cfg_setup` Config Object Initialization function.
```c
void proximity21_cfg_setup ( proximity21_cfg_t *cfg );
```

- `proximity21_init` Initialization function.
```c
err_t proximity21_init ( proximity21_t *ctx, proximity21_cfg_t *cfg );
```

- `proximity21_default_cfg` Click Default Configuration function.
```c
err_t proximity21_default_cfg ( proximity21_t *ctx );
```

- `proximity21_get_gpio1_pin` This function returns the GPIO1 (interrupt) pin logic state.
```c
uint8_t proximity21_get_gpio1_pin ( proximity21_t *ctx );
```

- `proximity21_get_result` This function gets the results reported by the sensor.
```c
err_t proximity21_get_result ( proximity21_t *ctx, proximity21_data_t *results );
```

- `proximity21_clear_interrupt` This function clears the data ready interrupt.
```c
err_t proximity21_clear_interrupt ( proximity21_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity21_cfg_t proximity21_cfg;  /**< Click config object. */

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
    proximity21_cfg_setup( &proximity21_cfg );
    PROXIMITY21_MAP_MIKROBUS( proximity21_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity21_init( &proximity21, &proximity21_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY21_ERROR == proximity21_default_cfg ( &proximity21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt, then reads the measurement results and logs
the target distance (millimeters) and signal quality (the higher the value the better the signal quality) to the USB UART.

```c
void application_task ( void )
{
    proximity21_data_t results;
    // Wait for a data ready interrupt
    while ( proximity21_get_gpio1_pin ( &proximity21 ) );

    if ( PROXIMITY21_OK == proximity21_get_result ( &proximity21, &results ) )
    {
        log_printf( &logger, " Distance [mm]: %u\r\n", results.distance_mm );
        log_printf( &logger, " Signal [kcps/SPAD]: %u\r\n\n", results.signal_per_spad_kcps );
        proximity21_clear_interrupt ( &proximity21 );
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
