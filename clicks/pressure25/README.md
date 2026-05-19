
---
# Pressure 25 Click

> [Pressure 25 Click](https://www.mikroe.com/?pid_product=MIKROE-6937) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6937&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Mar 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Pressure 25 Click board for
measuring pressure and temperature data. The application reads sensor
values via the I2C interface and displays the measured results on
the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure25

### Example Key Functions

- `pressure25_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pressure25_cfg_setup ( pressure25_cfg_t *cfg );
```

- `pressure25_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pressure25_init ( pressure25_t *ctx, pressure25_cfg_t *cfg );
```

- `pressure25_send_cmd` This function sends a command byte over the I2C interface.
```c
err_t pressure25_send_cmd ( pressure25_t *ctx, uint8_t cmd );
```

- `pressure25_get_int_pin` This function reads the current logic level of the INT pin.
```c
uint8_t pressure25_get_int_pin ( pressure25_t *ctx );
```

- `pressure25_get_press_temp` This function triggers a compensated pressure and temperature acquisition and converts values to kPa and degC.
```c
err_t pressure25_get_press_temp ( pressure25_t *ctx, float *press, float *temp );
```

### Application Init

> Initializes the logger and Pressure 25 Click driver.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure25_cfg_t pressure25_cfg;  /**< Click config object. */

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
    pressure25_cfg_setup( &pressure25_cfg );
    PRESSURE25_MAP_MIKROBUS( pressure25_cfg, MIKROBUS_POSITION_PRESSURE25 );
    if ( PRESSURE25_ERROR == pressure25_init( &pressure25, &pressure25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads pressure and temperature values from the sensor and
logs the results to the serial terminal.

```c
void application_task ( void ) 
{
    float pressure = 0.0f;
    float temperature = 0.0f;

    if ( PRESSURE25_OK == pressure25_get_press_temp( &pressure25, &pressure, &temperature ) )
    {
        log_printf( &logger, " Pressure: %.2f kPa\r\n", pressure );
        log_printf( &logger, " Temperature: %.1f degC\r\n\n", temperature );
    }
    else
    {
        log_error( &logger, " Error reading data.\r\n" );
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
