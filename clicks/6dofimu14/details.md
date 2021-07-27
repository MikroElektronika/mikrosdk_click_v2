
---
# 6DOF IMU 14 click

6DOF IMU 14 Click is a compact add-on board that contains a 6-axis MEMS motion tracking device combining a 3-axis gyroscope and a 3-axis accelerometer. This board features the ICM-42688-P, high precision 6-axis MEMS motion tracking device, from TDK InvenSense.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-14-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the 6DOFIMU14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOFIMU14 Click driver.

#### Standard key functions :

- `c6dofimu14_cfg_setup` Config Object Initialization function.
```c
void c6dofimu14_cfg_setup ( c6dofimu14_cfg_t *cfg );
```

- `c6dofimu14_init` Initialization function.
```c
C6DOFIMU14_RETVAL c6dofimu14_init ( c6dofimu14_t *ctx, c6dofimu14_cfg_t *cfg );
```

- `c6dofimu14_default_cfg` Click Default Configuration function.
```c
void c6dofimu14_default_cfg ( c6dofimu14_t *ctx );
```

#### Example key functions :

- `c6dofimu14_get_data` This function reads accel and gyro data for all three axis.
```c
err_t c6dofimu14_get_data ( c6dofimu14_t *ctx, c6dofimu14_axis_t *acc_axis, c6dofimu14_axis_t *gyro_axis );
```

- `c6dofimu14_get_temperature` This function reads the raw temperature data and converts it to Celsius.
```c
err_t c6dofimu14_get_temperature ( c6dofimu14_t *ctx, float *temp );
```

- `c6dofimu14_software_reset` This function performs the device software reset.
```c
err_t c6dofimu14_software_reset ( c6dofimu14_t *ctx );
```

## Example Description

> This example demonstrates the use of 6DOF IMU 14 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and configures the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu14_cfg_t c6dofimu14_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c6dofimu14_cfg_setup( &c6dofimu14_cfg );
    C6DOFIMU14_MAP_MIKROBUS( c6dofimu14_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu14_init( &c6dofimu14, &c6dofimu14_cfg );
    if ( ( init_flag == I2C_MASTER_ERROR ) || ( init_flag == SPI_MASTER_ERROR ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );

    if ( c6dofimu14_default_cfg ( &c6dofimu14 ) != C6DOFIMU14_OK ) 
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads accel, gyro, and temperature data and displays the results on the USB UART approximately every 500ms.

```c

void application_task ( void )
{
    float temperature;
    c6dofimu14_axis_t accel;
    c6dofimu14_axis_t gyro;
    
    c6dofimu14_get_data( &c6dofimu14, &accel, &gyro );
    c6dofimu14_get_temperature( &c6dofimu14, &temperature );
        
    log_printf( &logger, " Accel X: %d | Gyro X: %d\r\n", accel.x, gyro.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d\r\n", accel.y, gyro.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d\r\n", accel.z, gyro.z );
    log_printf( &logger, " Temperature: %.2f C\r\n", temperature );
    log_printf( &logger, "----------------------------------\r\n");
        
    Delay_ms( 500 );
}

```

## Note

> In the case of I2C, the example doesn't work properly on some of the 8-bit PICs (ex. PIC18F97J94).

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
