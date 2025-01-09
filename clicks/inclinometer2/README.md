
---
# Inclinometer 2 Click

> [Inclinometer 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5156) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5156&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Inclinometer 2 Click board by reading and displaying the Accel X and Y axis data (mg) and the temperature (degC) on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer2

### Example Key Functions

- `inclinometer2_cfg_setup` Config Object Initialization function.
```c
void inclinometer2_cfg_setup ( inclinometer2_cfg_t *cfg );
```

- `inclinometer2_init` Initialization function.
```c
err_t inclinometer2_init ( inclinometer2_t *ctx, inclinometer2_cfg_t *cfg );
```

- `inclinometer2_default_cfg` Click Default Configuration function.
```c
err_t inclinometer2_default_cfg ( inclinometer2_t *ctx );
```

- `inclinometer2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t inclinometer2_get_int_pin ( inclinometer2_t *ctx );
```

- `inclinometer2_get_accel` This function checks if the accel data is ready and than reads the accel X and Y axis in mg.
```c
err_t inclinometer2_get_accel ( inclinometer2_t *ctx, float *x_axis, float *y_axis );
```

- `inclinometer2_get_temperature` This function checks if the temperature data is ready and than reads the temperature in Celsius.
```c
err_t inclinometer2_get_temperature ( inclinometer2_t *ctx, float *temperature );
```

### Application Init

> Initializes the driver and performs the Click default configuration which enables the accel data ready interrupt, sets output data rate to 12.5 Hz and accel full-scale range to +-2g.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer2_cfg_t inclinometer2_cfg;  /**< Click config object. */

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
    inclinometer2_cfg_setup( &inclinometer2_cfg );
    INCLINOMETER2_MAP_MIKROBUS( inclinometer2_cfg, MIKROBUS_1 );
    err_t init_flag  = inclinometer2_init( &inclinometer2, &inclinometer2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( INCLINOMETER2_ERROR == inclinometer2_default_cfg ( &inclinometer2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the values of accel X and Y axis as well as the absolute temperature and displays the results on the USB UART. The data sample rate is
set to 12.5Hz by default, therefore the data is being read approximately every 80ms.

```c
void application_task ( void )
{
    // Wait for accel data ready indication
    while ( !inclinometer2_get_int_pin ( &inclinometer2 ) );
    
    float x_axis, y_axis;
    if ( INCLINOMETER2_OK == inclinometer2_get_accel ( &inclinometer2, &x_axis, &y_axis ) )
    {
        log_printf( &logger, " X: %.2f mg\r\n", x_axis );
        log_printf( &logger, " Y: %.2f mg\r\n", y_axis );
    }
    float temperature;
    if ( INCLINOMETER2_OK == inclinometer2_get_temperature ( &inclinometer2, &temperature ) )
    {
        log_printf( &logger, " Temperature: %.2f C\r\n\n", temperature );
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
