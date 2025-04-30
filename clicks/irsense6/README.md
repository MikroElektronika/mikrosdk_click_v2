
---
# IR Sense 6 Click

> [IR Sense 6 Click](https://www.mikroe.com/?pid_product=MIKROE-6570) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6570&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the functionality of the IR Sense 6 Click board, 
which measures ambient and object temperatures using an infrared sensor. 
The example initializes the device and continuously logs temperature readings.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.IRSense6

### Example Key Functions

- `irsense6_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void irsense6_cfg_setup ( irsense6_cfg_t *cfg );
```

- `irsense6_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t irsense6_init ( irsense6_t *ctx, irsense6_cfg_t *cfg );
```

- `irsense6_enable_device` This function enables the IR Sense 6 device by setting the EN pin high.
```c
void irsense6_enable_device ( irsense6_t *ctx );
```

- `irsense6_disable_device` This function disables the IR Sense 6 device by setting the EN pin low.
```c
void irsense6_disable_device ( irsense6_t *ctx );
```

- `irsense6_read_data` This function reads the object and ambient temperature data from the IR Sense 6 sensor.
```c
err_t irsense6_read_data ( irsense6_t *ctx, float *obj_temp, float *amb_temp );
```

### Application Init

> Initializes the driver and enables the device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense6_cfg_t irsense6_cfg;  /**< Click config object. */

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
    irsense6_cfg_setup( &irsense6_cfg );
    IRSENSE6_MAP_MIKROBUS( irsense6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irsense6_init( &irsense6, &irsense6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    irsense6_enable_device ( &irsense6 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads and logs ambient and object temperatures. The readings are displayed in degrees Celsius.

```c
void application_task ( void )
{
    float obj_temp = 0;
    float amb_temp = 0;
    if ( IRSENSE6_OK == irsense6_read_data ( &irsense6, &obj_temp, &amb_temp ) )
    {
        log_printf ( &logger, " Ambient temperature: %.1f degC\r\n", amb_temp );
        log_printf ( &logger, " Object temperature: %.1f degC\r\n\n", obj_temp );
        Delay_ms ( 500 );
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
