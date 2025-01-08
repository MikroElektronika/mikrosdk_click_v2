
---
# Ambient 10 Click

> [Ambient 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4777) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4777&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 10 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient10

### Example Key Functions

- `ambient10_cfg_setup` Config Object Initialization function.
```c
void ambient10_cfg_setup ( ambient10_cfg_t *cfg );
```

- `ambient10_init` Initialization function.
```c
err_t ambient10_init ( ambient10_t *ctx, ambient10_cfg_t *cfg );
```

- `ambient10_set_vref` This function sets the voltage reference for Ambient 10 Click driver.
```c
err_t ambient10_set_vref ( ambient10_t *ctx, float vref );
```

- `ambient10_read_adc_voltage` This function reads raw 12-bit ADC data and converts it to voltage by using I2C serial interface.
```c
err_t ambient10_read_adc_voltage ( ambient10_t *ctx, float *voltage );
```

- `ambient10_voltage_to_lux` This function calculates illuminance (lux) based on the voltage input.
```c
uint16_t ambient10_voltage_to_lux ( ambient10_t *ctx, float voltage );
```

### Application Init

> Initializes the driver and sets the voltage reference.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    ambient10_cfg_t ambient10_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient10_cfg_setup( &ambient10_cfg );
    AMBIENT10_MAP_MIKROBUS( ambient10_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == ambient10_init( &ambient10, &ambient10_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    ambient10_set_vref( &ambient10, AMBIENT10_VREF_3V3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ADC voltage and then calculates the illuminance from it.
> The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 

```c
void application_task ( void )
{
    float voltage = 0;
    
    if ( AMBIENT10_OK == ambient10_read_an_pin_voltage ( &ambient10, &voltage ) )
    {
        log_printf( &logger, " Illuminance : %u Lux\r\n\n", ambient10_voltage_to_lux( &ambient10, voltage ) );
    }
    
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
