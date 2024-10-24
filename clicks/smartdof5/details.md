
---
# Smart DOF 5 click

> Smart DOF 5 Click is a compact add-on board designed for precise motion and orientation detection in automotive applications. This board features the ASM330LHHXG1, a high-accuracy 6-axis inertial measurement unit (IMU) from STMicroelectronics. It features a 3-axis accelerometer and a 3-axis gyroscope and supports dual operating modes (high-performance and low-power) with flexible communication options through SPI or I2C interfaces. Additionally, it includes the Click Snap format, enabling the autonomous use of the Snap section and integration of external sensors via the I2C Master interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartdof5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smart-dof-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Smart DOF 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart DOF 5 Click driver.

#### Standard key functions :

- `smartdof5_cfg_setup` Config Object Initialization function.
```c
void smartdof5_cfg_setup ( smartdof5_cfg_t *cfg );
```

- `smartdof5_init` Initialization function.
```c
err_t smartdof5_init ( smartdof5_t *ctx, smartdof5_cfg_t *cfg );
```

- `smartdof5_default_cfg` Click Default Configuration function.
```c
err_t smartdof5_default_cfg ( smartdof5_t *ctx );
```

#### Example key functions :

- `smartdof5_get_int_pin` This function returns the interrupt 1 pin logic state.
```c
uint8_t smartdof5_get_int_pin ( smartdof5_t *ctx );
```

- `smartdof5_get_data` This function reads the accelerometer, gyroscope, and temperature measurement data.
```c
err_t smartdof5_get_data ( smartdof5_t *ctx, smartdof5_data_t *data_out );
```

- `smartdof5_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t smartdof5_set_accel_fsr ( smartdof5_t *ctx, uint8_t fsr );
```

## Example Description

> This example demonstrates the use of Smart DOF 5 click board by reading and displaying 
the accelerometer and gyroscope data (X, Y, and Z axis) as well as a temperature measurement in degrees Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof5_cfg_t smartdof5_cfg;  /**< Click config object. */

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
    smartdof5_cfg_setup( &smartdof5_cfg );
    SMARTDOF5_MAP_MIKROBUS( smartdof5_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof5_init( &smartdof5, &smartdof5_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF5_ERROR == smartdof5_default_cfg ( &smartdof5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a data ready indication and then reads the accelerometer, gyroscope, and temperature
measurements. The results are displayed on the USB UART at 12.5 Hz output data rate.

```c
void application_task ( void )
{
    smartdof5_data_t meas_data;
    if ( smartdof5_get_int_pin ( &smartdof5 ) ) 
    {
        if ( SMARTDOF5_OK == smartdof5_get_data ( &smartdof5, &meas_data ) )
        {
            log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
            log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
            log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
            log_printf( &logger, " Gyro X: %.1f dps\r\n", meas_data.gyro.x );
            log_printf( &logger, " Gyro Y: %.1f dps\r\n", meas_data.gyro.y );
            log_printf( &logger, " Gyro Z: %.1f dps\r\n", meas_data.gyro.z );
            log_printf( &logger, " Temperature: %.2f degC\r\n\n", meas_data.temperature );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
