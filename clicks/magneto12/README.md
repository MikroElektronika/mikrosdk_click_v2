
---
# Magneto 12 Click

> [Magneto 12 Click](https://www.mikroe.com/?pid_product=MIKROE-4991) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4991&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of Magneto 12 Click board by reading and displaying the magnet's angular position in degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto12

### Example Key Functions

- `magneto12_cfg_setup` Config Object Initialization function.
```c
void magneto12_cfg_setup ( magneto12_cfg_t *cfg );
```

- `magneto12_init` Initialization function.
```c
err_t magneto12_init ( magneto12_t *ctx, magneto12_cfg_t *cfg );
```

- `magneto12_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t magneto12_read_voltage ( magneto12_t *ctx, float *voltage );
```

- `magneto12_set_vref` This function sets the voltage reference for Magneto 12 Click driver.
```c
err_t magneto12_set_vref ( magneto12_t *ctx, float vref );
```

- `magneto12_read_angle` This function reads the sensor output voltage and converts it to angular position in degrees.
```c
err_t magneto12_read_angle ( magneto12_t *ctx, float *angle );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto12_cfg_t magneto12_cfg;  /**< Click config object. */

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
    magneto12_cfg_setup( &magneto12_cfg );
    MAGNETO12_MAP_MIKROBUS( magneto12_cfg, MIKROBUS_1 );
    err_t init_flag = magneto12_init( &magneto12, &magneto12_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle = 0;
    if ( MAGNETO12_OK == magneto12_read_angle ( &magneto12, &angle ) )
    {
        log_printf( &logger, " Angle: %.2f degrees\r\n\n", angle );
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
