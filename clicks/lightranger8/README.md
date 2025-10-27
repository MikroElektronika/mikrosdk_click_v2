
---
# LightRanger 8 Click

> [LightRanger 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4492) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4492&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Nikolic
- **Date**          : jan 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo application shows an example of distance measurement via VL53L3 ranging sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger8

### Example Key Functions

- `lightranger8_cfg_setup` Config Object Initialization function.
```c
void lightranger8_cfg_setup ( lightranger8_cfg_t *cfg );
```

- `lightranger8_init` Initialization function.
```c
err_t lightranger8_init ( lightranger8_t *ctx, lightranger8_cfg_t *cfg );
```

- `lightranger8_default_cfg` Click Default Configuration function.
```c
err_t lightranger8_default_cfg ( lightranger8_t *ctx );
```

- `lightranger8_set_measurement_timing_budget` This function sets the timing budget of the VL53Lx ranging sensor.
```c
err_t lightranger8_set_measurement_timing_budget ( lightranger8_t *ctx, uint32_t budget_us );
```

- `lightranger8_start_measurement` This function enables the range measuring with the adjusted intermeasurement period.
```c
void lightranger8_start_measurement ( lightranger8_t *ctx, uint32_t period_ms );
```

- `lightranger8_get_distance` This function returns the corrected measured distance from the VL53Lx ranging sensor described in milimeters.
```c
uint16_t lightranger8_get_distance ( lightranger8_t *ctx );
```

### Application Init

> Initialization of I2C module, log UART and additional pins.
After driver init, the app powers the device and performs
default settings of the ranging sensor including distance
mode and timing budget. The optional calibration helps
improvement of the accuracy on the targeted distance.
This process takes 10 second ( which can by modifed by
simply lowering the Delay_ms ( ) value ) so the user can
place an object on the exact location. When calibration is
finished, device starts the measurement with intermeasurement
period set by the user.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;                           /**< Logger config object. */
    lightranger8_cfg_t lightranger8_cfg;         /**< Click config object. */

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

    lightranger8_cfg_setup( &lightranger8_cfg );
    LIGHTRANGER8_MAP_MIKROBUS( lightranger8_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger8_init( &lightranger8, &lightranger8_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    lightranger8_power_on( &lightranger8 );
    log_printf( &logger, " Wait until the configuration of the chip is completed...\r\n" );
    if ( lightranger8_default_cfg( &lightranger8 ) != 0 ) {
        log_error( &logger, " Sensor config error. " );
        for ( ; ; );
    }
    lightranger8_set_distance_mode( &lightranger8, LIGHTRANGER8_DISTANCE_MODE_MEDIUM );
    lightranger8_set_measurement_timing_budget( &lightranger8, budget_us );
    Delay_ms ( 1000 );

    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " For calibration place an object at %.1f cm distance from sensor.\r\n", ( float ) calibration_distance_mm / 10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " ---------------    Sensor calibration is in progress...     ---------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    lightranger8_calibrate_offset( &lightranger8, calibration_distance_mm, period_ms, &offset );
    Delay_ms ( 500 );
    
    lightranger8_start_measurement( &lightranger8, period_ms );
    log_printf( &logger, " -------------------------------------------------------------------------\r\n" );
    log_printf( &logger, " -------------    Sensor measurement commencing...    -------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> A new data ready is checked as soon as possible which signals
the time required for the ranging sensor to perform the
measurement. An acquired distance is shown on the LOG with
the 2 seconds delay so the terminal is possible to read.

```c
void application_task ( void ) 
{
    uint16_t distance;
    
    while ( lightranger8_get_interrupt_state( &lightranger8 ) != 0 ) {
        Delay_1ms();
    }

    distance = lightranger8_get_distance( &lightranger8 );
    log_printf( &logger, " ----------------------\r\n" );
    log_printf( &logger, " Distance: %.1f cm \r\n", ( float ) distance / 10 );
    lightranger8_system_interrupt_clear ( &lightranger8 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
