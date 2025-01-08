
---
# Accel 27 Click

> [Accel 27 Click](https://www.mikroe.com/?pid_product=MIKROE-5528) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5528&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2022.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of Accel 27 Click board by reading and displaying the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel27

### Example Key Functions

- `accel27_cfg_setup` Config Object Initialization function.
```c
void accel27_cfg_setup ( accel27_cfg_t *cfg );
```

- `accel27_init` Initialization function.
```c
err_t accel27_init ( accel27_t *ctx, accel27_cfg_t *cfg );
```

- `accel27_default_cfg` Click Default Configuration function.
```c
err_t accel27_default_cfg ( accel27_t *ctx );
```

- `accel27_get_int1_pin` This function returns the interrupt 1 (INT1) pin logic state.
```c
uint8_t accel27_get_int1_pin ( accel27_t *ctx );
```

- `accel27_get_axes` This function reads accel X, Y, and Z axis data in g.
```c
err_t accel27_get_axes ( accel27_t *ctx, accel27_axes_t *axes );
```

- `accel27_reset_device` This function performs the chip software reset.
```c
err_t accel27_reset_device ( accel27_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel27_cfg_t accel27_cfg;  /**< Click config object. */

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
    accel27_cfg_setup( &accel27_cfg );
    ACCEL27_MAP_MIKROBUS( accel27_cfg, MIKROBUS_1 );
    err_t init_flag = accel27_init( &accel27, &accel27_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL27_ERROR == accel27_default_cfg ( &accel27 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays on the USB UART the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

```c
void application_task ( void )
{
    accel27_axes_t axes = { 0 };
    uint16_t cnt = 0;
    while ( cnt < NUM_OF_SAMPLES )
    {
        // Wait for data ready indication
        while ( !accel27_get_int1_pin ( &accel27 ) );

        accel27_axes_t tmp_axes;
        if ( ACCEL27_OK == accel27_get_axes ( &accel27, &tmp_axes ) )
        {
            axes.x += tmp_axes.x;
            axes.y += tmp_axes.y;
            axes.z += tmp_axes.z;
            cnt++;
        }
    }
    axes.x = axes.x / NUM_OF_SAMPLES;
    axes.y = axes.y / NUM_OF_SAMPLES;
    axes.z = axes.z / NUM_OF_SAMPLES;
    log_printf( &logger, " X: %.1f g\r\n", axes.x );
    log_printf( &logger, " Y: %.1f g\r\n", axes.y );
    log_printf( &logger, " Z: %.1f g\r\n\n", axes.z );
}
```

### Note

> This Click board should be used for high g applications of up to +-400g. It is not recommended
for low g applications because of its high scale factor which is about 200 mg per LSB.

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
