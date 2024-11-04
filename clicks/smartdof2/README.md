\mainpage Main Page

---
# Smart DOF 2 Click

> Smart DOF 2 Click is a compact add-on board with a highly advanced integrated 6-axis IMU measurement unit. 
> This board features the LSM6DSV16XTR, a high-performance 6-axis IMU with sensor fusion, 
> ASC, MLC, Qvar, and OIS/EIS paths from STMicroelectronics.
> The IMU unit features an accelerometer and gyroscope that can be turned off independently of each other, 
> still allowed to have different ODRs and power modes. The unit can be configured as a finite state machine (FSM), 
> machine learning core (MLC), and Qvar sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartdof2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/smart-dof-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Smart DOF 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart DOF 2 Click driver.

#### Standard key functions :

- `smartdof2_cfg_setup` Config Object Initialization function.
```c
void smartdof2_cfg_setup ( smartdof2_cfg_t *cfg );
```

- `smartdof2_init` Initialization function.
```c
err_t smartdof2_init ( smartdof2_t *ctx, smartdof2_cfg_t *cfg );
```

- `smartdof2_default_cfg` Click Default Configuration function.
```c
err_t smartdof2_default_cfg ( smartdof2_t *ctx );
```

#### Example key functions :

- `smartdof2_get_acc_axis` Smart DOF 2 get accel sensor axes function.
```c
err_t smartdof2_get_acc_axis ( smartdof2_t *ctx, smartdof2_axis_t *acc_axis );
```

- `smartdof2_get_gyro_axis` Smart DOF 2 get gyro sensor axes function.
```c
err_t smartdof2_get_gyro_axis ( smartdof2_t *ctx, smartdof2_axis_t *gyro_axis );
```

- `smartdof2_get_temperature` Smart DOF 2 get temperature function.
```c
err_t smartdof2_get_temperature ( smartdof2_t *ctx, float *temperature );
```

## Example Description

> This library contains API for Smart DOF 2 Click driver.
> The library initializes and defines the I2C or SPI bus drivers 
> to write and read data from registers. 
> The library also includes a function for reading 
> accelerometer and gyroscope X-axis, Y-axis, and Z-axis data
> and the temperature in degrees Celsius.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof2_cfg_t smartdof2_cfg;  /**< Click config object. */

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
    smartdof2_cfg_setup( &smartdof2_cfg );
    SMARTDOF2_MAP_MIKROBUS( smartdof2_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof2_init( &smartdof2, &smartdof2_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF2_ERROR == smartdof2_default_cfg ( &smartdof2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the Smart DOF 2 Click board™.
> Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static smartdof2_axis_t acc_axis, gyro_axis;
    if ( SMARTDOF2_OK == smartdof2_get_acc_axis( &smartdof2, &acc_axis ) )
    {
        if ( SMARTDOF2_OK == smartdof2_get_gyro_axis( &smartdof2, &gyro_axis ) )
        {
            log_printf( &logger, " Accel X: %.2f mg | Gyro X: %.2f mdps\r\n", acc_axis.x, gyro_axis.x );
            log_printf( &logger, " Accel Y: %.2f mg | Gyro Y: %.2f mdps\r\n", acc_axis.y, gyro_axis.y );
            log_printf( &logger, " Accel Z: %.2f mg | Gyro Z: %.2f mdps\r\n", acc_axis.z, gyro_axis.z );
            log_printf( &logger, "--------------------------------------\r\n" );
        }
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
