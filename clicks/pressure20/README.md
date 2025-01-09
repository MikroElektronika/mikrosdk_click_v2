
---
# Pressure 20 Click

> [Pressure 20 Click](https://www.mikroe.com/?pid_product=MIKROE-5153) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5153&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Pressure 20 Click board by reading and displaying the pressure and temperature data on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure20

### Example Key Functions

- `pressure20_cfg_setup` Config Object Initialization function.
```c
void pressure20_cfg_setup ( pressure20_cfg_t *cfg );
```

- `pressure20_init` Initialization function.
```c
err_t pressure20_init ( pressure20_t *ctx, pressure20_cfg_t *cfg );
```

- `pressure20_default_cfg` Click Default Configuration function.
```c
err_t pressure20_default_cfg ( pressure20_t *ctx );
```

- `pressure20_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t pressure20_get_int_pin ( pressure20_t *ctx );
```

- `pressure20_clear_interrupts` This function reads and clears the interrupt status register.
```c
err_t pressure20_clear_interrupts ( pressure20_t *ctx );
```

- `pressure20_read_data` This function reads the pressure [mBar] and temperature [Celsius] data.
```c
err_t pressure20_read_data ( pressure20_t *ctx, float *pressure, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure20_cfg_t pressure20_cfg;  /**< Click config object. */

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
    pressure20_cfg_setup( &pressure20_cfg );
    PRESSURE20_MAP_MIKROBUS( pressure20_cfg, MIKROBUS_1 );
    err_t init_flag  = pressure20_init( &pressure20, &pressure20_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PRESSURE20_ERROR == pressure20_default_cfg ( &pressure20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, clears the interrupts and than reads
the pressure [mBar] and temperature [Celsius] data and displays them on the USB UART
at the set output data rate (25Hz by default).

```c
void application_task ( void )
{
    // Wait for the data ready interrupt
    while ( pressure20_get_int_pin ( &pressure20 ) );
    float pressure, temperature;
    if ( ( PRESSURE20_OK == pressure20_clear_interrupts ( &pressure20 ) ) &&
         ( PRESSURE20_OK == pressure20_read_data ( &pressure20, &pressure, &temperature ) ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
