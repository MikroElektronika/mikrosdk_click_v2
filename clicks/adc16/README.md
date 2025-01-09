
---
# ADC 16 Click

> [ADC 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4937) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4937&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of ADC 16 Click board by reading the voltage from the two analog input channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC16

### Example Key Functions

- `adc16_cfg_setup` Config Object Initialization function.
```c
void adc16_cfg_setup ( adc16_cfg_t *cfg );
```

- `adc16_init` Initialization function.
```c
err_t adc16_init ( adc16_t *ctx, adc16_cfg_t *cfg );
```

- `adc16_default_cfg` Click Default Configuration function.
```c
err_t adc16_default_cfg ( adc16_t *ctx );
```

- `adc16_single_register_write` This function writes a single data to the selected register.
```c
err_t adc16_single_register_write ( adc16_t *ctx, uint8_t reg, uint8_t data_in );
```

- `adc16_single_register_read` This function reads a single data from the selected register.
```c
err_t adc16_single_register_read ( adc16_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `adc16_get_voltage` This function reads the voltage from two analog input single-ended channels.
```c
err_t adc16_get_voltage ( adc16_t *ctx, float *ain0_voltage, float *ain1_voltage );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the two analog input channels to single-ended mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adc16_cfg_t adc16_cfg;  /**< Click config object. */

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
    adc16_cfg_setup( &adc16_cfg );
    ADC16_MAP_MIKROBUS( adc16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == adc16_init( &adc16, &adc16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADC16_ERROR == adc16_default_cfg ( &adc16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the voltage from the two analog input channels on the USB UART approximately every 100ms.

```c
void application_task ( void )
{
    float ain0_voltage, ain1_voltage;
    if ( ADC16_OK == adc16_get_voltage ( &adc16, &ain0_voltage, &ain1_voltage ) )
    {
        log_printf ( &logger, " AIN0 voltage: %.3f V \r\n", ain0_voltage );
        log_printf ( &logger, " AIN1 voltage: %.3f V \r\n\n", ain1_voltage );
        Delay_ms ( 100 );
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
