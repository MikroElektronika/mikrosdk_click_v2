
---
# Pressure 21 Click

> [Pressure 21 Click](https://www.mikroe.com/?pid_product=MIKROE-5274) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5274&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Pressure 21 Click board by reading and displaying the pressure and temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure21

### Example Key Functions

- `pressure21_cfg_setup` Config Object Initialization function.
```c
void pressure21_cfg_setup ( pressure21_cfg_t *cfg );
```

- `pressure21_init` Initialization function.
```c
err_t pressure21_init ( pressure21_t *ctx, pressure21_cfg_t *cfg );
```

- `pressure21_default_cfg` Click Default Configuration function.
```c
err_t pressure21_default_cfg ( pressure21_t *ctx );
```

- `pressure21_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure21_get_int_pin ( pressure21_t *ctx );
```

- `pressure21_get_sensor_data` This function reads the sensor measurements data: pressure in Pascals and temperature in Celsius.
```c
err_t pressure21_get_sensor_data ( pressure21_t *ctx, float *pressure, float *temperature );
```

- `pressure21_write_register` This function writes a desired data to the selected register.
```c
err_t pressure21_write_register ( pressure21_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure21_cfg_t pressure21_cfg;  /**< Click config object. */

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
    pressure21_cfg_setup( &pressure21_cfg );
    PRESSURE21_MAP_MIKROBUS( pressure21_cfg, MIKROBUS_1 );
    err_t init_flag = pressure21_init( &pressure21, &pressure21_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE21_ERROR == pressure21_default_cfg ( &pressure21 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt and then reads the pressure and temperature data and displays them on the USB UART approximately once per second.

```c
void application_task ( void )
{
    if ( pressure21_get_int_pin ( &pressure21 ) )
    {
        float pressure, temperature;
        if ( PRESSURE21_OK == pressure21_get_sensor_data ( &pressure21, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.2f mBar\r\n", pressure * PRESSURE21_PA_TO_MBAR );
            log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
        }
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
