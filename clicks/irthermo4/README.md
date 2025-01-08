
---
# IR Thermo 4 Click

> [IR Thermo 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6135) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6135&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of IR Thermo 4 Click board by reading and displaying the ambient and object temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRThermo4

### Example Key Functions

- `irthermo4_cfg_setup` Config Object Initialization function.
```c
void irthermo4_cfg_setup ( irthermo4_cfg_t *cfg );
```

- `irthermo4_init` Initialization function.
```c
err_t irthermo4_init ( irthermo4_t *ctx, irthermo4_cfg_t *cfg );
```

- `irthermo4_default_cfg` Click Default Configuration function.
```c
err_t irthermo4_default_cfg ( irthermo4_t *ctx );
```

- `irthermo4_read_ambient_temp` This function reads and calculates the ambient temperature in degrees Celsius.
```c
err_t irthermo4_read_ambient_temp ( irthermo4_t *ctx, float *t_amb );
```

- `irthermo4_read_object_temp` This function reads and calculates the object temperature in degrees Celsius.
```c
err_t irthermo4_read_object_temp ( irthermo4_t *ctx, float *t_obj, float t_amb );
```

- `irthermo4_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t irthermo4_get_int_pin ( irthermo4_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo4_cfg_t irthermo4_cfg;  /**< Click config object. */

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
    irthermo4_cfg_setup( &irthermo4_cfg );
    IRTHERMO4_MAP_MIKROBUS( irthermo4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irthermo4_init( &irthermo4, &irthermo4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRTHERMO4_ERROR == irthermo4_default_cfg ( &irthermo4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the ambient and object temperature measurements twice per second and displays the results on the USB UART.

```c
void application_task ( void )
{
    float ambient_temp = 0;
    float object_temp = 0;
    if ( IRTHERMO4_OK == irthermo4_read_ambient_temp ( &irthermo4, &ambient_temp ) )
    {
        log_printf ( &logger, " Ambient temperature: %.2f degC\r\n", ambient_temp );
        if ( IRTHERMO4_OK == irthermo4_read_object_temp ( &irthermo4, &object_temp, ambient_temp ) )
        {
            log_printf ( &logger, " Object temperature: %.2f degC\r\n\n", object_temp );
        }
    }
    Delay_ms ( 500 );
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
