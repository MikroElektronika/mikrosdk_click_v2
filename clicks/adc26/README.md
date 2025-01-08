
---
# ADC 26 Click

> [ADC 26 Click](https://www.mikroe.com/?pid_product=MIKROE-6416) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6416&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of ADC 26 Click board by reading and
displaying the voltage levels from IN0-IN1 differential and IN2-IN3
single-ended analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC26

### Example Key Functions

- `adc26_cfg_setup` Config Object Initialization function.
```c
void adc26_cfg_setup ( adc26_cfg_t *cfg );
```

- `adc26_init` Initialization function.
```c
err_t adc26_init ( adc26_t *ctx, adc26_cfg_t *cfg );
```

- `adc26_default_cfg` Click Default Configuration function.
```c
err_t adc26_default_cfg ( adc26_t *ctx );
```

- `adc26_start_conversion` This function starts a single-shot conversion for the selected MUX channel and gain level (full-scale range).
```c
err_t adc26_start_conversion ( adc26_t *ctx, uint8_t mux, uint8_t pga );
```

- `adc26_get_alert_pin` This function returns the ALERT (data ready) pin logic state.
```c
uint8_t adc26_get_alert_pin ( adc26_t *ctx );
```

- `adc26_read_voltage` This function reads the RAW ADC measurement and converts it to a voltage level.
```c
err_t adc26_read_voltage ( adc26_t *ctx, float *voltage );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc26_cfg_t adc26_cfg;  /**< Click config object. */

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
    adc26_cfg_setup( &adc26_cfg );
    ADC26_MAP_MIKROBUS( adc26_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc26_init( &adc26, &adc26_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC26_ERROR == adc26_default_cfg ( &adc26 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the voltage levels from IN0-IN1 differential (+/- 2.048V) and
IN2-IN3 single-ended (+/- 4.096V) analog input channels and displays
the results on the USB UART once per second approximately.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( ADC26_OK == adc26_start_conversion ( &adc26, ADC26_MUX_P_AIN0_N_AIN1, ADC26_PGA_2_048V ) )
    {
        while ( adc26_get_alert_pin ( &adc26 ) ); // Waits for a data ready indication
        
        if ( ADC26_OK == adc26_read_voltage ( &adc26, &voltage ) )
        {
            log_printf ( &logger, " Voltage between IN0[P] and IN1[N]: %.3f V\r\n", voltage );
        }
    }
    if ( ADC26_OK == adc26_start_conversion ( &adc26, ADC26_MUX_P_AIN2_N_GND, ADC26_PGA_4_096V ) )
    {
        while ( adc26_get_alert_pin ( &adc26 ) ); // Waits for a data ready indication
        
        if ( ADC26_OK == adc26_read_voltage ( &adc26, &voltage ) )
        {
            log_printf ( &logger, " Voltage between IN2 and GND: %.3f V\r\n", voltage );
        }
    }
    if ( ADC26_OK == adc26_start_conversion ( &adc26, ADC26_MUX_P_AIN3_N_GND, ADC26_PGA_4_096V ) )
    {
        while ( adc26_get_alert_pin ( &adc26 ) ); // Waits for a data ready indication
        
        if ( ADC26_OK == adc26_read_voltage ( &adc26, &voltage ) )
        {
            log_printf ( &logger, " Voltage between IN3 and GND: %.3f V\r\n\n", voltage );
        }
    }
    Delay_ms ( 1000 );
}
```

### Note

> Do not apply more than VCC + 0.3 V to the analog inputs of the device.

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
