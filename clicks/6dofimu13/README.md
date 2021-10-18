\mainpage Main Page

---
# 6DOF IMU 13 click

6DOF IMU 13 Click is a compact add-on board that contains an eCompass that consists of a 3-axis linear accelerometer and a 3-axis magnetic field sensor. This board features the MC6470, an accelerometer and magnetometer for a 6 DoF (6 Degrees of Freedom) sensor solution, from mCube Inc.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/6dofimu13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/6dof-imu-13-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the 6DOFIMU13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for 6DOFIMU13 Click driver.

#### Standard key functions :

- `c6dofimu13_cfg_setup` Config Object Initialization function.
```c
void c6dofimu13_cfg_setup ( c6dofimu13_cfg_t *cfg );
```

- `c6dofimu13_init` Initialization function.
```c
C6DOFIMU13_RETVAL c6dofimu13_init ( c6dofimu13_t *ctx, c6dofimu13_cfg_t *cfg );
```

- `c6dofimu13_default_cfg` Click Default Configuration function.
```c
void c6dofimu13_default_cfg ( c6dofimu13_t *ctx );
```

#### Example key functions :

- `c6dofimu13_mag_get_data` This function reads magnetometer X, Y, and Z-Axis data.
```c
err_t c6dofimu13_mag_get_data ( c6dofimu13_t *ctx, float *mag_x, float *mag_y, float *mag_z );
```

- `c6dofimu13_accel_init` This function initializes accelerometer.
```c
err_t c6dofimu13_accel_init ( c6dofimu13_t *ctx, uint8_t samp_rate, uint8_t samp_range, uint8_t samp_res );
```

- `c6dofimu13_accel_get_data` This function reads accelerometer X, Y, and Z-Axis data.
```c
err_t c6dofimu13_accel_get_data ( c6dofimu13_t *ctx, float *accel_x, float *accel_y, float *accel_z );
```

## Example Description

> This example demonstrates the use of 6DOF IMU 13 click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, and sets the device default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c6dofimu13_cfg_t c6dofimu13_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );

    log_info( &logger, " Application Init " );

    // Click initialization.

    c6dofimu13_cfg_setup( &c6dofimu13_cfg );
    C6DOFIMU13_MAP_MIKROBUS( c6dofimu13_cfg, MIKROBUS_1 );
    err_t init_flag = c6dofimu13_init( &c6dofimu13, &c6dofimu13_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    c6dofimu13_default_cfg ( &c6dofimu13 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measures acceleration and magnetometer data and displays the results on the USB UART every second.

```c

void application_task ( void )
{
    float acc_x, acc_y, acc_z;
    float mag_x, mag_y, mag_z;

    c6dofimu13_accel_get_data( &c6dofimu13, &acc_x, &acc_y, &acc_z );
    c6dofimu13_mag_get_data( &c6dofimu13, &mag_x, &mag_y, &mag_z );

    log_printf( &logger, " Accel X: %.3f g\t Mag X: %.2f uT\r\n", acc_x, mag_x );
    log_printf( &logger, " Accel Y: %.3f g\t Mag Y: %.2f uT\r\n", acc_y, mag_y );
    log_printf( &logger, " Accel Z: %.3f g\t Mag Z: %.2f uT\r\n", acc_z, mag_z );
    log_printf( &logger, "----------------------------------\r\n");

    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.6DOFIMU13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
