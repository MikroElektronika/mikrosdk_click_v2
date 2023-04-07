\mainpage Main Page

---
# Accel 29 click

> Accel 29 Click is a compact add-on board that contains an acceleration sensor. This board features the ADXL314, a three-axis ±200g accelerometer from Analog Devices. The ADXL314 offers 16-bit digital output data with a configurable host interface that supports SPI and I2C serial communication. An integrated memory management system with a 32-level FIFO buffer can store data to minimize host processor activity and lower overall system power consumption. Low power modes enable intelligent motion-based power management with threshold sensing and active acceleration measurement at low power dissipation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel29_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-29-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 29 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 29 Click driver.

#### Standard key functions :

- `accel29_cfg_setup` Config Object Initialization function.
```c
void accel29_cfg_setup ( accel29_cfg_t *cfg );
```

- `accel29_init` Initialization function.
```c
err_t accel29_init ( accel29_t *ctx, accel29_cfg_t *cfg );
```

- `accel29_default_cfg` Click Default Configuration function.
```c
err_t accel29_default_cfg ( accel29_t *ctx );
```

#### Example key functions :

- `accel29_calibrate_offset` This function calibrates accel offset to the specified values by setting the OFSX/Y/Z registers.
```c
err_t accel29_calibrate_offset ( accel29_t *ctx, accel29_axes_t calib_axes );
```

- `accel29_get_avg_axes` This function reads a specified number of samples for accel X, Y, and Z axis data in g and averages them.
```c
err_t accel29_get_avg_axes ( accel29_t *ctx, uint16_t num_samples, accel29_axes_t *avg_axes );
```

## Example Description

> This example demonstrates the use of Accel 29 click board by reading and displaying the accelerometer data (X, Y, and Z axis) averaged from 100 samples.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the click default configuration, and calibrates the accel data offsets.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel29_cfg_t accel29_cfg;  /**< Click config object. */

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
    accel29_cfg_setup( &accel29_cfg );
    ACCEL29_MAP_MIKROBUS( accel29_cfg, MIKROBUS_1 );
    err_t init_flag = accel29_init( &accel29, &accel29_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL29_ERROR == accel29_default_cfg ( &accel29 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    accel29_axes_t calib_axes;
    calib_axes.x = ACCEL29_CALIB_X;
    calib_axes.y = ACCEL29_CALIB_Y;
    calib_axes.z = ACCEL29_CALIB_Z;
    if ( ACCEL29_ERROR == accel29_calibrate_offset ( &accel29, calib_axes ) )
    {
        log_error( &logger, " Calibrate offset." );
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
    accel29_axes_t axes;
    if ( ACCEL29_OK == accel29_get_avg_axes ( &accel29, ACCEL29_NUM_OF_SAMPLES, &axes ) )
    {
        log_printf( &logger, " X: %.1f g\r\n", axes.x );
        log_printf( &logger, " Y: %.1f g\r\n", axes.y );
        log_printf( &logger, " Z: %.1f g\r\n\n", axes.z );
    }
}
```

## Note

> This click board should be used for high g applications of up to +-200g. It is not recommended for low g applications because of its high scale factor which is about 48.83 mg per LSB.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel29

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
