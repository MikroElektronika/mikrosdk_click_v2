
---
# Inclinometer 4 Click

> [Inclinometer 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6259) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6259&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Inclinometer 4 Click board by reading and displaying accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer4

### Example Key Functions

- `inclinometer4_cfg_setup` Config Object Initialization function.
```c
void inclinometer4_cfg_setup ( inclinometer4_cfg_t *cfg );
```

- `inclinometer4_init` Initialization function.
```c
err_t inclinometer4_init ( inclinometer4_t *ctx, inclinometer4_cfg_t *cfg );
```

- `inclinometer4_default_cfg` Click Default Configuration function.
```c
err_t inclinometer4_default_cfg ( inclinometer4_t *ctx );
```

- `inclinometer4_get_int2_pin` This function returns the interrupt 2 (INT2) pin logic state.
```c
uint8_t inclinometer4_get_int2_pin ( inclinometer4_t *ctx );
```

- `inclinometer4_get_data` This function reads accel X, Y, and Z axis data in g and temperature in degrees Celsius.
```c
err_t inclinometer4_get_data ( inclinometer4_t *ctx, inclinometer4_data_t *data_out );
```

- `inclinometer4_set_mode` This function sets the device operating mode to standby or active.
```c
err_t inclinometer4_set_mode ( inclinometer4_t *ctx, uint8_t mode );
```

### Application Init

> Initializes the driver and performs the Click default configuration which enables data ready interrupt on INT2 pin and sets full scale range to +/-2G and output data rate to 160ms.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer4_cfg_t inclinometer4_cfg;  /**< Click config object. */

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
    inclinometer4_cfg_setup( &inclinometer4_cfg );
    INCLINOMETER4_MAP_MIKROBUS( inclinometer4_cfg, MIKROBUS_1 );
    err_t init_flag = inclinometer4_init( &inclinometer4, &inclinometer4_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER4_ERROR == inclinometer4_default_cfg ( &inclinometer4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt, then reads and displays the accel data (X, Y, and Z axis) as well as temperature measurements on the USB UART.

```c
void application_task ( void )
{
    inclinometer4_data_t accel_data;
    
    // Wait for a data ready interrupt
    while ( inclinometer4_get_int2_pin ( &inclinometer4 ) );

    if ( INCLINOMETER4_OK == inclinometer4_get_data ( &inclinometer4, &accel_data ) )
    {
        log_printf( &logger, " X: %.3f g\r\n", accel_data.x );
        log_printf( &logger, " Y: %.3f g\r\n", accel_data.y );
        log_printf( &logger, " Z: %.3f g\r\n", accel_data.z );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) accel_data.temperature );
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
