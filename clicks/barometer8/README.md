
---
# Barometer 8 Click

> [Barometer 8 Click](https://www.mikroe.com/?pid_product=MIKROE-5128) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5128&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Barometer 8 Click board by reading and displaying the pressure and temperature values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer8

### Example Key Functions

- `barometer8_cfg_setup` Config Object Initialization function.
```c
void barometer8_cfg_setup ( barometer8_cfg_t *cfg );
```

- `barometer8_init` Initialization function.
```c
err_t barometer8_init ( barometer8_t *ctx, barometer8_cfg_t *cfg );
```

- `barometer8_default_cfg` Click Default Configuration function.
```c
err_t barometer8_default_cfg ( barometer8_t *ctx );
```

- `barometer8_write_register` This function writes a desired data byte to the selected register.
```c
err_t barometer8_write_register ( barometer8_t *ctx, uint8_t reg, uint8_t data_in );
```

- `barometer8_read_register` This function reads a data byte from the selected register.
```c
err_t barometer8_read_register ( barometer8_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `barometer8_read_data` This function reads the pressure and temperature raw data and converts them to mBar and Celsius.
```c
err_t barometer8_read_data ( barometer8_t *ctx, float *pressure, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer8_cfg_t barometer8_cfg;  /**< Click config object. */

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
    barometer8_cfg_setup( &barometer8_cfg );
    BAROMETER8_MAP_MIKROBUS( barometer8_cfg, MIKROBUS_1 );
    err_t init_flag  = barometer8_init( &barometer8, &barometer8_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BAROMETER8_ERROR == barometer8_default_cfg ( &barometer8 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the pressure and temperature data on the USB UART every 250ms approximately, as per output data rate (ODR) bits configuration.

```c
void application_task ( void )
{
    float pressure, temperature;
    if ( BAROMETER8_OK == barometer8_read_data ( &barometer8, &pressure, &temperature ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms ( 5 );
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
