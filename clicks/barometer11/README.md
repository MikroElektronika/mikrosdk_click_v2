
---
# Barometer 11 Click

> [Barometer 11 Click](https://www.mikroe.com/?pid_product=MIKROE-6636) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6636&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : ADC/I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Barometer 11 Click board by initializing
the device and reading the barometric pressure data in millibar units.
The pressure value is periodically logged to the USB UART every second.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Barometer11

### Example Key Functions

- `barometer11_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void barometer11_cfg_setup ( barometer11_cfg_t *cfg );
```

- `barometer11_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t barometer11_init ( barometer11_t *ctx, barometer11_cfg_t *cfg );
```

- `barometer11_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t barometer11_read_voltage_avg ( barometer11_t *ctx, uint16_t num_conv, float *voltage_avg );
```

- `barometer11_read_pressure` This function reads the pressure level [mBar].
```c
err_t barometer11_read_pressure ( barometer11_t *ctx, float *pressure );
```

### Application Init

> Initializes the logger and the Barometer 11 Click driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    barometer11_cfg_t barometer11_cfg;  /**< Click config object. */

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
    barometer11_cfg_setup( &barometer11_cfg );
    BAROMETER11_MAP_MIKROBUS( barometer11_cfg, MIKROBUS_1 );
    err_t init_flag = barometer11_init( &barometer11, &barometer11_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the pressure data every second.

```c
void application_task ( void )
{
    float pressure = 0;
    if ( BAROMETER11_OK == barometer11_read_pressure ( &barometer11, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %.1f mBar\r\n\n", pressure );
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
