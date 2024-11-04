
---
# Smart DOF 3 Click

> Smart DOF 3 Click is a compact add-on board with a highly advanced integrated system-in-package (SIP) accelerometer
> and gyroscope sensors. This board features the ISM330IS, an iNEMO inertial module from STMicroelectronics. 
> The inertial module consists of an always-on 3-axis accelerometer 
> and 3-axis gyroscope with ISPU (intelligent sensor processing unit). 
> In addition, the ISM330IS can be configured to allow connection with external I2C sensors.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartdof3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/smart-dof-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Smart DOF 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart DOF 3 Click driver.

#### Standard key functions :

- `smartdof3_cfg_setup` Config Object Initialization function.
```c
void smartdof3_cfg_setup ( smartdof3_cfg_t *cfg );
```

- `smartdof3_init` Initialization function.
```c
err_t smartdof3_init ( smartdof3_t *ctx, smartdof3_cfg_t *cfg );
```

- `smartdof3_default_cfg` Click Default Configuration function.
```c
err_t smartdof3_default_cfg ( smartdof3_t *ctx );
```

#### Example key functions :

- `smartdof3_get_acc_axis` Smart DOF 3 get the accel sensor axes function.
```c
err_t smartdof3_get_acc_axis ( smartdof3_t *ctx, smartdof3_axis_t *acc_axis );
```

- `smartdof3_get_gyro_axis` Smart DOF 3 get the gyro sensor axes function.
```c
err_t smartdof3_get_gyro_axis ( smartdof3_t *ctx, smartdof3_axis_t *gyro_axis );
```

- `smartdof3_get_temperature` Smart DOF 3 get the temperature function.
```c
err_t smartdof3_get_temperature ( smartdof3_t *ctx, float *temperature );
```

## Example Description

> This library contains API for Smart DOF 3 Click driver.
> The library initializes and defines the I2C and SPI bus drivers to 
> write and read data from registers, as well as the default 
> configuration for reading accelerator and gyroscope data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C or SPI module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartdof3_cfg_t smartdof3_cfg;  /**< Click config object. */

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
    smartdof3_cfg_setup( &smartdof3_cfg );
    SMARTDOF3_MAP_MIKROBUS( smartdof3_cfg, MIKROBUS_1 );
    err_t init_flag = smartdof3_init( &smartdof3, &smartdof3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTDOF3_ERROR == smartdof3_default_cfg ( &smartdof3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Smart DOF 3 Click board™.
> Measures and displays acceleration and gyroscope data for X-axis, Y-axis, and Z-axis.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static smartdof3_axis_t acc_axis, gyro_axis;
    if ( ( SMARTDOF3_OK == smartdof3_get_acc_axis( &smartdof3, &acc_axis ) ) &&
         ( SMARTDOF3_OK == smartdof3_get_gyro_axis( &smartdof3, &gyro_axis ) ) )
    {
        log_printf( &logger, " Accel X: %.2f mg | Gyro X: %.2f dps\r\n", acc_axis.x, gyro_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg | Gyro Y: %.2f dps\r\n", acc_axis.y, gyro_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg | Gyro Z: %.2f dps\r\n", acc_axis.z, gyro_axis.z );
        log_printf( &logger, "--------------------------------------\r\n" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartDOF3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
