
---
# MagAccel click

> Mag&Accel Click is a compact add-on board representing a moving object and magnetic switch as a single solution. This board features the NMH1000, a Hall-effect magnetic field switch, and the FXLS8974CF, a 3-axis low-g accelerometer, both from NXP Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magaccel_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magaccel-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the MagAccel Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MagAccel Click driver.

#### Standard key functions :

- `magaccel_cfg_setup` Config Object Initialization function.
```c
void magaccel_cfg_setup ( magaccel_cfg_t *cfg );
```

- `magaccel_init` Initialization function.
```c
err_t magaccel_init ( magaccel_t *ctx, magaccel_cfg_t *cfg );
```

- `magaccel_default_cfg` Click Default Configuration function.
```c
err_t magaccel_default_cfg ( magaccel_t *ctx );
```

#### Example key functions :

- `magaccel_get_axes_data` This function reads the accelerometer sensor axes data.
```c
err_t magaccel_get_axes_data ( magaccel_t *ctx, magaccel_axes_t *axes );
```

- `magaccel_set_op_mode` This function sets the desired operating mode of the sensor.
```c
err_t magaccel_set_op_mode ( magaccel_t *ctx, uint8_t op_mode );
```

- `magaccel_check_mag_field` This function checks the magnetic field y by reading the states of the FLD (AN) pin.
```c
uint8_t magaccel_check_mag_field ( magaccel_t *ctx );
```

## Example Description

> This library contains API for the Mag&Accel Click driver.
> The library initializes and defines the I2C drivers to 
> write and read data from registers, as well as the default 
> configuration for reading accelerator data.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magaccel_cfg_t magaccel_cfg;  /**< Click config object. */

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
    magaccel_cfg_setup( &magaccel_cfg );
    MAGACCEL_MAP_MIKROBUS( magaccel_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magaccel_init( &magaccel, &magaccel_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGACCEL_ERROR == magaccel_default_cfg ( &magaccel ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}
```

### Application Task

> This example demonstrates the use of the Mag&Accel Click board.
> Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis 
> and the presence of a magnetic field. 
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( MAGACCEL_DATA_READY == magaccel_check_data_ready( &magaccel ) )
    {
        magaccel_axes_t acc_axis;
        magaccel_get_axes_data( &magaccel, &acc_axis );
        
        if ( MAGACCEL_DET_MAG_FIELD == magaccel_check_mag_field( &magaccel ) )
        {
            log_printf( &logger, " Presence of a magnetic field\r\n" );
            log_printf( &logger, "_________________\r\n" );
        }
        
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
        log_printf( &logger, "_________________\r\n" );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagAccel

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
