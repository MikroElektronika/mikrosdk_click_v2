
---
# Thermo 27 Click

> [Thermo 27 Click](https://www.mikroe.com/?pid_product=MIKROE-5509) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5509&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2022.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Thermo 27 Click board by reading and displaying the temperature measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo27

### Example Key Functions

- `thermo27_cfg_setup` Config Object Initialization function.
```c
void thermo27_cfg_setup ( thermo27_cfg_t *cfg );
```

- `thermo27_init` Initialization function.
```c
err_t thermo27_init ( thermo27_t *ctx, thermo27_cfg_t *cfg );
```

- `thermo27_default_cfg` Click Default Configuration function.
```c
err_t thermo27_default_cfg ( thermo27_t *ctx );
```

- `thermo27_write_register` Thermo 27 register writing function.
```c
err_t thermo27_write_register ( thermo27_t *ctx, uint8_t reg, uint16_t data_in );
```

- `thermo27_get_device_id` Thermo 27 get device id function.
```c
err_t thermo27_get_device_id ( thermo27_t *ctx, uint16_t *device_id );
```

- `thermo27_read_temp` Thermo 27 get read temperature function.
```c
err_t thermo27_read_temp ( thermo27_t *ctx, float *temp_out );
```

### Application Init

> Initializes the driver and reads the device id, and after that resets the device and performs default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    thermo27_cfg_t thermo27_cfg;  /**< Click config object. */

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
    thermo27_cfg_setup( &thermo27_cfg );
    THERMO27_MAP_MIKROBUS( thermo27_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == thermo27_init( &thermo27, &thermo27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    uint16_t device_id;
    thermo27_get_device_id( &thermo27, &device_id );
    if ( THERMO27_DEVICE_ID != device_id )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( THERMO27_ERROR == thermo27_default_cfg( &thermo27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
   
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ======================= \r\n");
}
```

### Application Task

> Reads the temperature measurement in degrees Celsius and displays the results on the USB UART at a rate of once per second.

```c
void application_task ( void ) 
{
    float temperature;
    uint8_t status;
    
    thermo27_get_alert_reg( &thermo27, &status );
    if ( THERMO27_DATA_READY_FLAG & status )
    {
        thermo27_read_temp( &thermo27, &temperature );
        log_printf( &logger, " Temperature: %f degC \r\n", temperature );
        log_printf( &logger, " ======================= \r\n");
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
