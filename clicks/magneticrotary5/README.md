
---
# Magnetic Rotary 5 Click

> [Magnetic Rotary 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5691) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5691&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2022.
- **Type**          : ADC/GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Magnetic Rotary 5 Click board by reading and displaying
the magnet angular position as well as the AGC and multi turn counter values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary5

### Example Key Functions

- `magneticrotary5_cfg_setup` Config Object Initialization function.
```c
void magneticrotary5_cfg_setup ( magneticrotary5_cfg_t *cfg );
```

- `magneticrotary5_init` Initialization function.
```c
err_t magneticrotary5_init ( magneticrotary5_t *ctx, magneticrotary5_cfg_t *cfg );
```

- `magneticrotary5_default_cfg` Click Default Configuration function.
```c
err_t magneticrotary5_default_cfg ( magneticrotary5_t *ctx );
```

- `magneticrotary5_read_angle` This function reads the magnetic angle and automatic gain control (AGC) values measured by the sensor.
```c
err_t magneticrotary5_read_angle ( magneticrotary5_t *ctx, uint8_t *agc, uint16_t *angle );
```

- `magneticrotary5_read_mt_cnt` This function reads the multi turn counter value. With each zero transition in any direction, the output of a special counter is incremented or decremented.
```c
err_t magneticrotary5_read_mt_cnt ( magneticrotary5_t *ctx, int16_t *mt_cnt );
```

- `magneticrotary5_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t magneticrotary5_read_voltage ( magneticrotary5_t *ctx, float *voltage );
```

### Application Init

> Initializes the driver and resets the multi turn counter to zero.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary5_cfg_t magneticrotary5_cfg;  /**< Click config object. */

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
    magneticrotary5_cfg_setup( &magneticrotary5_cfg );
    MAGNETICROTARY5_MAP_MIKROBUS( magneticrotary5_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == magneticrotary5_init( &magneticrotary5, &magneticrotary5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY5_ERROR == magneticrotary5_default_cfg ( &magneticrotary5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet angular position in degrees as well as the voltage from AN pin which is
proportional to the angular position. Also reads the AGC and multi turn counter values.
The results will be displayed on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    uint8_t agc = 0;
    uint16_t angle = 0;
    int16_t mt_cnt = 0;
    float voltage = 0;
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_angle ( &magneticrotary5, &agc, &angle ) )
    {
        log_printf ( &logger, "\r\n AGC: %u\r\n Angle: %u\r\n", ( uint16_t ) agc, angle );
    }
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_mt_cnt ( &magneticrotary5, &mt_cnt ) )
    {
        log_printf ( &logger, " Multi turn counter: %d\r\n", mt_cnt );
    }
    if ( MAGNETICROTARY5_OK == magneticrotary5_read_voltage ( &magneticrotary5, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f V\r\n", voltage );
    }
    Delay_ms ( 100 );
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
