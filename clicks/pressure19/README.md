
---
# Pressure 19 Click

> [Pressure 19 Click](https://www.mikroe.com/?pid_product=MIKROE-5089) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5089&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Pressure 19 Click board by reading and displaying the absolute pressure value in mBar.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure19

### Example Key Functions

- `pressure19_cfg_setup` Config Object Initialization function.
```c
void pressure19_cfg_setup ( pressure19_cfg_t *cfg );
```

- `pressure19_init` Initialization function.
```c
err_t pressure19_init ( pressure19_t *ctx, pressure19_cfg_t *cfg );
```

- `pressure19_get_pressure` This function reads the output voltage and converts it to pressure in mBar.
```c
err_t pressure19_get_pressure ( pressure19_t *ctx, uint16_t *pressure );
```

- `pressure19_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t pressure19_read_voltage ( pressure19_t *ctx, float *voltage );
```

- `pressure19_set_vref` This function sets the voltage reference for Pressure 19 Click driver.
```c
err_t pressure19_set_vref ( pressure19_t *ctx, float vref );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    pressure19_cfg_t pressure19_cfg;    /**< Click config object. */

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
    pressure19_cfg_setup( &pressure19_cfg );
    PRESSURE19_MAP_MIKROBUS( pressure19_cfg, MIKROBUS_1 );
    err_t init_flag = pressure19_init( &pressure19, &pressure19_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the absolute pressure value [mBar] on the USB UART approximately once per seconds.

```c
void application_task ( void )
{
    uint16_t pressure;
    if ( PRESSURE19_OK == pressure19_get_pressure ( &pressure19, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %u mBar\r\n\n", pressure );
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
