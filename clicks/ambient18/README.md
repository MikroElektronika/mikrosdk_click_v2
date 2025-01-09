
---
# Ambient 18 Click

> [Ambient 18 Click](https://www.mikroe.com/?pid_product=MIKROE-4943) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4943&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 18 Click board by measuring and displaying the illuminance value in Lux.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient18

### Example Key Functions

- `ambient18_cfg_setup` Config Object Initialization function.
```c
void ambient18_cfg_setup ( ambient18_cfg_t *cfg );
```

- `ambient18_init` Initialization function.
```c
err_t ambient18_init ( ambient18_t *ctx, ambient18_cfg_t *cfg );
```

- `ambient18_set_gain_mode` This function sets the gain mode.
```c
void ambient18_set_gain_mode ( ambient18_t *ctx, uint8_t mode );
```

- `ambient18_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t ambient18_read_voltage ( ambient18_t *ctx, float *voltage );
```

- `ambient18_voltage_to_lux` This function calculates illuminance (lux) based on the voltage input.
```c
int32_t ambient18_voltage_to_lux ( ambient18_t *ctx, float voltage );
```

### Application Init

> Initializes the driver and sets the gain mode to M-Gain which can detect the illuminance of up to 1000 lux.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient18_cfg_t ambient18_cfg;  /**< Click config object. */

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
    ambient18_cfg_setup( &ambient18_cfg );
    AMBIENT18_MAP_MIKROBUS( ambient18_cfg, MIKROBUS_1 );
    err_t init_flag = ambient18_init( &ambient18, &ambient18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    ambient18_set_gain_mode ( &ambient18, AMBIENT18_MODE_M_GAIN );
    log_printf( &logger, " M-Gain mode selected.\r\n Up to 1000 lux can be measured.\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ADC voltage and then calculates the illuminance from it.
The calculated value of illuminance in lux is being displayed on the USB UART 
approximately once per second.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( AMBIENT18_OK == ambient18_read_voltage ( &ambient18, &voltage ) ) 
    {
        log_printf( &logger, " Illuminance : %ld Lux\r\n\n", ambient18_voltage_to_lux( &ambient18, voltage ) );
        Delay_ms ( 1000 );
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
