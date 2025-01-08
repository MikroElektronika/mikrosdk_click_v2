
---
# Ultrasonic 5 Click

> [Ultrasonic 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5804) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5804&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of Ultrasonic 5 Click board by reading the measurements from the connected ultrasonic sensor and displaying it on a Serial Plot.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ultrasonic5

### Example Key Functions

- `ultrasonic5_cfg_setup` Config Object Initialization function.
```c
void ultrasonic5_cfg_setup ( ultrasonic5_cfg_t *cfg );
```

- `ultrasonic5_init` Initialization function.
```c
err_t ultrasonic5_init ( ultrasonic5_t *ctx, ultrasonic5_cfg_t *cfg );
```

- `ultrasonic5_default_cfg` Click Default Configuration function.
```c
err_t ultrasonic5_default_cfg ( ultrasonic5_t *ctx );
```

- `ultrasonic5_clear_io1_pin` This function clears the IO1 pin to low logic state.
```c
void ultrasonic5_clear_io1_pin ( ultrasonic5_t *ctx );
```

- `ultrasonic5_pwm_start` This function starts the PWM module output.
```c
err_t ultrasonic5_pwm_start ( ultrasonic5_t *ctx );
```

- `ultrasonic5_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t ultrasonic5_read_an_pin_voltage ( ultrasonic5_t *ctx, float *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic5_cfg_t ultrasonic5_cfg;  /**< Click config object. */

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
    ultrasonic5_cfg_setup( &ultrasonic5_cfg );
    ULTRASONIC5_MAP_MIKROBUS( ultrasonic5_cfg, MIKROBUS_1 );
    if ( ULTRASONIC5_OK != ultrasonic5_init( &ultrasonic5, &ultrasonic5_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ULTRASONIC5_OK != ultrasonic5_default_cfg ( &ultrasonic5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Performs a burst generation which starts the measurement and then reads the next 200 ADC samples and displays the results on the USB UART (SerialPlot).

```c
void application_task ( void )
{
    float voltage = 0;
    // Burst generation / Start measurement
    ultrasonic5_set_duty_cycle ( &ultrasonic5, ULTRASONIC5_DEF_DYTY );
    ultrasonic5_pwm_start( &ultrasonic5 );
    ultrasonic5_clear_io1_pin ( &ultrasonic5 );
    Delay_500us ( );
    ultrasonic5_set_io1_pin ( &ultrasonic5 );
    ultrasonic5_pwm_stop( &ultrasonic5 );
    // Read and log the next 200 ADC samples which we will plot on a Serial Plotter
    for ( uint16_t cnt = 0; cnt < 200; cnt++ )
    {
        if ( ULTRASONIC5_OK == ultrasonic5_read_an_pin_voltage ( &ultrasonic5, &voltage ) ) 
        {
            log_printf( &logger, "%.3f\r\n", voltage );
        }
    }
}
```

### Note

> In order to get valid measuremets a proper ultrasonic sensor must be connected to OUTA and OUTB.
We have used an UTR-1440K-TT-R sensor for the test. We recommend using the SerialPlot tool
for data visualizing. Refer to the datasheet "Application Curves" section in order to check
and compare the results from the plotter.

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
