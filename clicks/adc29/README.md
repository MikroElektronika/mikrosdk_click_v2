
---
# ADC 29 Click

> [ADC 29 Click](https://www.mikroe.com/?pid_product=MIKROE-7032) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7032&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jun 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the ADC 29 Click board by reading
the voltage levels from the single-ended analog input and displaying 
the results via UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC29

### Example Key Functions

- `adc29_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void adc29_cfg_setup ( adc29_cfg_t *cfg );
```

- `adc29_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t adc29_init ( adc29_t *ctx, adc29_cfg_t *cfg );
```

- `adc29_read_raw_adc` This function triggers a single conversion and reads the raw 12-bit ADC result by using SPI serial interface.
```c
err_t adc29_read_raw_adc ( adc29_t *ctx, uint16_t *raw_adc );
```

- `adc29_read_voltage` This function triggers a single conversion and reads the ADC result, then converts it to a voltage in volts.
```c
err_t adc29_read_voltage ( adc29_t *ctx, float *voltage );
```

- `adc29_recalibrate` This function initiates a manual self-calibration of the ADC by transmitting 1024 SCLK pulses.
```c
err_t adc29_recalibrate ( adc29_t *ctx );
```

### Application Init

> Initializes the driver and waits for the device power-on auto-calibration to complete.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc29_cfg_t adc29_cfg;  /**< Click config object. */

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
    adc29_cfg_setup( &adc29_cfg );
    ADC29_MAP_MIKROBUS( adc29_cfg, MIKROBUS_POSITION_ADC29 );
    if ( SPI_MASTER_ERROR == adc29_init( &adc29, &adc29_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage from the analog input and displays the result
on the USB UART once per second.

```c
void application_task ( void )
{
    float voltage = 0;

    if ( ADC29_OK == adc29_read_voltage( &adc29, &voltage ) )
    {
        log_printf( &logger, " AIN Voltage: %.3f V\r\n", voltage );
    }
    Delay_ms( 1000 );
}
```

### Note

> The absolute maximum input voltage is -0.3 V to 3.3 V (VREF + 0.3 V).
Do not apply voltages outside this range to the analog input.

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
