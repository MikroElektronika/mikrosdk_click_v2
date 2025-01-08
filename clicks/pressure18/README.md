
---
# Pressure 18 Click

> [Pressure 18 Click](https://www.mikroe.com/?pid_product=MIKROE-5296) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5296&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Pressure 18 Click board by reading and displaying the pressure and temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure18

### Example Key Functions

- `pressure18_cfg_setup` Config Object Initialization function.
```c
void pressure18_cfg_setup ( pressure18_cfg_t *cfg );
```

- `pressure18_init` Initialization function.
```c
err_t pressure18_init ( pressure18_t *ctx, pressure18_cfg_t *cfg );
```

- `pressure18_default_cfg` Click Default Configuration function.
```c
err_t pressure18_default_cfg ( pressure18_t *ctx );
```

- `pressure18_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure18_get_int_pin ( pressure18_t *ctx );
```

- `pressure18_read_data` This function reads the sensor measurements data: pressure in Pascals and temperature in Celsius.
```c
err_t pressure18_read_data ( pressure18_t *ctx, float *pressure, float *temperature );
```

- `pressure18_soft_reset` This function performs the software reset feature.
```c
err_t pressure18_soft_reset ( pressure18_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure18_cfg_t pressure18_cfg;  /**< Click config object. */

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
    pressure18_cfg_setup( &pressure18_cfg );
    PRESSURE18_MAP_MIKROBUS( pressure18_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure18_init( &pressure18, &pressure18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE18_ERROR == pressure18_default_cfg ( &pressure18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt and then reads the pressure and temperature data and displays them on the USB UART every 320ms approximately.

```c
void application_task ( void )
{
    if ( pressure18_get_int_pin ( &pressure18 ) )
    {
        float pressure, temperature;
        if ( PRESSURE18_OK == pressure18_read_data ( &pressure18, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure * PRESSURE18_PA_TO_MBAR );
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
