
---
# Pressure 24 Click

> [Pressure 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6892) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6892&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Pressure 24 Click board for
measuring pressure and temperature data. The application reads sensor
values via the SPI interface and displays the measured results on
the serial terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure24

### Example Key Functions

- `pressure24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pressure24_cfg_setup ( pressure24_cfg_t *cfg );
```

- `pressure24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pressure24_init ( pressure24_t *ctx, pressure24_cfg_t *cfg );
```

- `pressure24_get_identifier` This function triggers an identifier acquisition and reads the identifier response word.
```c
err_t pressure24_get_identifier ( pressure24_t *ctx, uint16_t *identifier );
```

- `pressure24_get_pressure` This function triggers a 14-bit pressure acquisition and calculates the result in millibars.
```c
err_t pressure24_get_pressure ( pressure24_t *ctx, float *press );
```

- `pressure24_get_temperature` This function triggers a 14-bit temperature acquisition and calculates the result in degrees Celsius.
```c
err_t pressure24_get_temperature ( pressure24_t *ctx, float *temp );
```

### Application Init

> Initializes the logger and Pressure 24 Click driver and verifies the device identifier.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pressure24_cfg_t pressure24_cfg;  /**< Click config object. */

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
    pressure24_cfg_setup( &pressure24_cfg );
    PRESSURE24_MAP_MIKROBUS( pressure24_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pressure24_init( &pressure24, &pressure24_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t identifier = 0;
    if ( PRESSURE24_OK == pressure24_get_identifier ( &pressure24, &identifier ) )
    {
        log_printf ( &logger, " Identifier: 0x%.4X\r\n", identifier );
    }

    if ( PRESSURE24_IDENTIFIER_SPI_ID != ( identifier & PRESSURE24_IDENTIFIER_SPI_ID_MASK ) )
    {
        log_error( &logger, " SPI ID read fail." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads pressure and temperature values from the sensor and logs the results to the serial terminal.

```c
void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;
    if ( PRESSURE24_OK == pressure24_get_pressure ( &pressure24, &pressure ) )
    {
        log_printf ( &logger, " Pressure: %.1f mBar\r\n", pressure );
    }
    if ( PRESSURE24_OK == pressure24_get_temperature ( &pressure24, &temperature ) )
    {
        log_printf ( &logger, " Temperature: %.1f degC\r\n\n", temperature );
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
