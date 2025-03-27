
---
# PWR Meter 3 Click

> [PWR Meter 3 Click](https://www.mikroe.com/?pid_product=MIKROE-6257) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6257&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of PWR Meter 3 Click board by reading and displaying the voltage, current, and power RMS measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PWRMeter3

### Example Key Functions

- `pwrmeter3_cfg_setup` Config Object Initialization function.
```c
void pwrmeter3_cfg_setup ( pwrmeter3_cfg_t *cfg );
```

- `pwrmeter3_init` Initialization function.
```c
err_t pwrmeter3_init ( pwrmeter3_t *ctx, pwrmeter3_cfg_t *cfg );
```

- `pwrmeter3_default_cfg` Click Default Configuration function.
```c
err_t pwrmeter3_default_cfg ( pwrmeter3_t *ctx );
```

- `pwrmeter3_get_dio0_pin` This function returns the DIO0 pin logic state.
```c
uint8_t pwrmeter3_get_dio0_pin ( pwrmeter3_t *ctx );
```

- `pwrmeter3_get_dio1_pin` This function returns the DIO1 pin logic state.
```c
uint8_t pwrmeter3_get_dio1_pin ( pwrmeter3_t *ctx );
```

- `pwrmeter3_read_average_rms` This function reads the voltage and current RMS measurements averaged from a specified number of samples.
```c
err_t pwrmeter3_read_average_rms ( pwrmeter3_t *ctx, float *v_rms, float *i_rms, uint16_t num_avg );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the DC measurement
and VRMS thresholds to about 28V for overvoltage and about 9.3V for undervoltage flag.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pwrmeter3_cfg_t pwrmeter3_cfg;  /**< Click config object. */

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
    pwrmeter3_cfg_setup( &pwrmeter3_cfg );
    PWRMETER3_MAP_MIKROBUS( pwrmeter3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pwrmeter3_init( &pwrmeter3, &pwrmeter3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PWRMETER3_ERROR == pwrmeter3_default_cfg ( &pwrmeter3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage and current RMS values averaged from 500 samples, then calculates the power from it
and displays the results on the USB UART. Also if an UV or OV flag is detected it will be logged accordingly.

```c
void application_task ( void )
{
    float v_rms, i_rms;
    if ( PWRMETER3_OK == pwrmeter3_read_average_rms ( &pwrmeter3, &v_rms, &i_rms, PWRMETER3_DEF_AVG_SAMPLES ) )
    {
        if ( !pwrmeter3_get_dio0_pin ( &pwrmeter3 ) )
        {
            log_printf ( &logger, " Over-voltage detected!\r\n" );
        }
        if ( !pwrmeter3_get_dio1_pin ( &pwrmeter3 ) )
        {
            log_printf ( &logger, " Under-voltage detected!\r\n" );
        }
        log_printf ( &logger, " Voltage: %.2f V\r\n", v_rms );
        log_printf ( &logger, " Current: %.2f A\r\n", i_rms );
        log_printf ( &logger, " Power: %.2f W\r\n\n", i_rms * v_rms );
    }
}
```

### Note

> In case of 15A or 60A versions of PWR Meter 3 Click board the PWRMETER3_MAX_CURRENT macro from pwrmeter3.h file
must be adjusted for accurate current measurements.

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
