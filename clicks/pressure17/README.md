
---
# Pressure 17 Click

> [Pressure 17 Click](https://www.mikroe.com/?pid_product=MIKROE-4944) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4944&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Pressure 17 Click board by reading and displaying the pressure and temperature data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure17

### Example Key Functions

- `pressure17_cfg_setup` Config Object Initialization function.
```c
void pressure17_cfg_setup ( pressure17_cfg_t *cfg );
```

- `pressure17_init` Initialization function.
```c
err_t pressure17_init ( pressure17_t *ctx, pressure17_cfg_t *cfg );
```

- `pressure17_default_cfg` Click Default Configuration function.
```c
err_t pressure17_default_cfg ( pressure17_t *ctx );
```

- `pressure17_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure17_get_int_pin ( pressure17_t *ctx );
```

- `pressure17_read_data` This function checks if the data is ready and then reads the pressure and temperature raw data and converts them to millibar and Celsius respectfully.
```c
err_t pressure17_read_data ( pressure17_t *ctx, float *pressure, float *temperature );
```

- `pressure17_write_register` This function writes a data byte to the selected register by using I2C serial interface.
```c
err_t pressure17_write_register ( pressure17_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure17_cfg_t pressure17_cfg;  /**< Click config object. */

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
    pressure17_cfg_setup( &pressure17_cfg );
    PRESSURE17_MAP_MIKROBUS( pressure17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pressure17_init( &pressure17, &pressure17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE17_ERROR == pressure17_default_cfg ( &pressure17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt and then reads the pressure [mbar] and temperature [C] data
and displays the results on the USB UART approximately every 200ms.

```c
void application_task ( void )
{
    if ( !pressure17_get_int_pin ( &pressure17 ) )
    {
        float pressure, temperature;
        if ( PRESSURE17_OK == pressure17_read_data ( &pressure17, &pressure, &temperature ) )
        {
            log_printf ( &logger, " Pressure: %.2f mbar\r\n Temperature: %.2f C\r\n\n", pressure, temperature );
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
