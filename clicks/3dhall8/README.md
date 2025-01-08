
---
# 3D Hall 8 Click

> [3D Hall 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4498) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4498&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Jan 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This application shows capability of 3D Hall 8 Click board. 
It configures device and reads sensor data. Sensor is capeable 
of reading magnetic flux density from 3 axes and temperature.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall8

### Example Key Functions

- `c3dhall8_cfg_setup` Config Object Initialization function.
```c
void c3dhall8_cfg_setup ( c3dhall8_cfg_t *cfg );
```

- `c3dhall8_init` Initialization function.
```c
err_t c3dhall8_init ( c3dhall8_t *ctx, c3dhall8_cfg_t *cfg );
```

- `c3dhall8_default_cfg` Click Default Configuration function.
```c
void c3dhall8_default_cfg ( c3dhall8_t *ctx );
```

- `c3dhall8_generic_write` 3D Hall 8 I2C writing function.
```c
err_t c3dhall8_generic_write ( c3dhall8_t *ctx, uint8_t reg, uint8_t tx_buf )
```

- `c3dhall8_read_sensor_data` Reading sensor data function.
```c
void c3dhall8_read_sensor_data ( c3dhall8_t *ctx, c3dhall8_data_t *sensor_data );
```

- `c3dhall8_get_xyz_magnetic_matching` Calculating magnetic matching.
```c
float c3dhall8_get_xyz_magnetic_matching ( c3dhall8_t *ctx, c3dhall8_data_t sensor_data );
```

### Application Init

> Initialization of device communication and application log and configures device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3dhall8_cfg_t c3dhall8_cfg;  /**< Click config object. */
    uint8_t rx_data;

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

    c3dhall8_cfg_setup( &c3dhall8_cfg );
    C3DHALL8_MAP_MIKROBUS( c3dhall8_cfg, MIKROBUS_1 );
    err_t init_flag = c3dhall8_init( &c3dhall8, &c3dhall8_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_printf( &logger," > Setting configuration...\r\n" );
    c3dhall8_default_cfg ( &c3dhall8 ); 

    log_info( &logger, " Application Task " );
    log_printf( &logger, "**************************************\r\n" );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads data from the device and logs it in span of 500ms.

```c
void application_task ( void ) 
{
    c3dhall8_data_t sens_data;
    c3dhall8_read_sensor_data( &c3dhall8, &sens_data );
    
    log_printf( &logger, "> X[mT]: %.2f\r\n> Y[mT]: %.2f\r\n> Z[mT]: %.2f \r\n> Temperature[C]: %.2f\r\n", 
                sens_data.x_axis, sens_data.y_axis, sens_data.z_axis, sens_data.temperature );
    float magnetic_match = c3dhall8_get_xyz_magnetic_matching( &c3dhall8, sens_data );
    log_printf( &logger, "> XYZ magnetic matching: %.2f\r\n", magnetic_match );
    log_printf( &logger, "**************************************\r\n" );

    Delay_ms ( 500 );
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
