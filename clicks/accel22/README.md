
---
# Accel 22 Click

> [Accel 22 Click](https://www.mikroe.com/?pid_product=MIKROE-4896) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4896&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 22 Click board by reading and displaying Accel data (X, Y, and Z axis) as well as temperature and ADC measurements on the USB UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel22

### Example Key Functions

- `accel22_cfg_setup` Config Object Initialization function.
```c
void accel22_cfg_setup ( accel22_cfg_t *cfg );
```

- `accel22_init` Initialization function.
```c
err_t accel22_init ( accel22_t *ctx, accel22_cfg_t *cfg );
```

- `accel22_default_cfg` Click Default Configuration function.
```c
err_t accel22_default_cfg ( accel22_t *ctx );
```

- `accel22_get_axes` This function reads accel X, Y, and Z axis data in mg.
```c
err_t accel22_get_axes ( accel22_t *ctx, accel22_axes_t *axes );
```

- `accel22_get_temperature` This function reads the temperature in Celsius.
```c
err_t accel22_get_temperature ( accel22_t *ctx, float *temperature );
```

- `accel22_get_adc` This function reads the ADC voltage.
```c
err_t accel22_get_adc ( accel22_t *ctx, float *v_adc );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel22_cfg_t accel22_cfg;  /**< Click config object. */

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
    accel22_cfg_setup( &accel22_cfg );
    ACCEL22_MAP_MIKROBUS( accel22_cfg, MIKROBUS_1 );
    err_t init_flag  = accel22_init( &accel22, &accel22_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL22_ERROR == accel22_default_cfg ( &accel22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays the Accel data (X, Y, and Z axis) as well as temperature and ADC measurements on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    accel22_axes_t axes;
    // Wait for data ready indication
    while ( !accel22_get_int1_pin ( &accel22 ) );
    if ( ACCEL22_OK == accel22_get_axes ( &accel22, &axes ) )
    {
        log_printf( &logger, " X: %.2f mg\r\n", axes.x );
        log_printf( &logger, " Y: %.2f mg\r\n", axes.y );
        log_printf( &logger, " Z: %.2f mg\r\n", axes.z );
    }
    
    if ( ACCEL22_OK == accel22_enable_temperature_measurement ( &accel22 ) )
    {
        float temperature = 0;
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( &accel22 ) );
        if ( ACCEL22_OK == accel22_get_temperature ( &accel22, &temperature ) )
        {
            log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
        }
    }
    
    if ( ACCEL22_OK == accel22_enable_adc_measurement ( &accel22 ) )
    {
        float adc_voltage = 0;
        // Wait for data ready indication
        while ( !accel22_get_int1_pin ( &accel22 ) );
        if ( ACCEL22_OK == accel22_get_adc ( &accel22, &adc_voltage ) )
        {
            log_printf( &logger, " ADC: %.2f V\r\n\n", adc_voltage );
        }
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
