
---
# UNI Hall 2 Click

> [UNI Hall 2 Click](https://www.mikroe.com/?pid_product=MIKROE-7054) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7054&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of the UNI Hall 2 Click board by reading
and displaying the magnetic flux density measured by the on-board A31015
linear Hall-effect sensor. The field is actuated by the magnetic switch
mounted above the sensor.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UNIHall2

### Example Key Functions

- `unihall2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void unihall2_cfg_setup ( unihall2_cfg_t *cfg );
```

- `unihall2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t unihall2_init ( unihall2_t *ctx, unihall2_cfg_t *cfg );
```

- `unihall2_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void unihall2_enable_device ( unihall2_t *ctx );
```

- `unihall2_disable_device` This function disables the device by setting the EN pin to low logic state.
```c
void unihall2_disable_device ( unihall2_t *ctx );
```

- `unihall2_read_field` This function reads the magnetic flux density measured by the sensor, in Gauss.
```c
err_t unihall2_read_field ( unihall2_t *ctx, float *field );
```

- `unihall2_read_voltage_avg` This function reads a desired number of ADC samples and calculates the average voltage level.
```c
err_t unihall2_read_voltage_avg ( unihall2_t *ctx, uint16_t num_conv, float *voltage_avg );
```

### Application Init

> Initializes the driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    unihall2_cfg_t unihall2_cfg;  /**< Click config object. */

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
    unihall2_cfg_setup( &unihall2_cfg );
    UNIHALL2_MAP_MIKROBUS( unihall2_cfg, MIKROBUS_POSITION_UNIHALL2 );
    if ( ADC_ERROR == unihall2_init( &unihall2, &unihall2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the magnetic flux density in Gauss once per second and logs the result
on the USB UART.

```c
void application_task ( void ) 
{
    float field = 0;

    if ( UNIHALL2_OK == unihall2_read_field( &unihall2, &field ) )
    {
        log_printf( &logger, " Magnetic flux density: %.2f G\r\n", field );
    }
    else
    {
        log_printf( &logger, " Reading magnetic flux density ERROR.\r\n" );
    }

    Delay_ms( 1000 );
}
```

### Note

> If the EN SEL jumper (JP2) is in the VCC position, the device is always
enabled and functions unihall2_enable_device and unihall2_disable_device have no effect.

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
