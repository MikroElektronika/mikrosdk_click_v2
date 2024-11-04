
---
# Gyro 6 Click

> Gyro 6 Click is a compact add-on board that contains a high-performance gyroscope. This board features the IAM-20380, a 3-axis, digital-output X-, Y-, and Z-axis angular rate sensor (gyroscope) from TDK InvenSense. It has a full-scale programmable range of ±250DPS, ±500DPS, ±1000DPS, and ±2000DPS with a factory-calibrated initial sensitivity and configurable host interface that supports both SPI and I2C serial communication.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gyro-6-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2021.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Gyro6 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Gyro6 Click driver.

#### Standard key functions :

- `gyro6_cfg_setup` Config Object Initialization function.
```c
void gyro6_cfg_setup ( gyro6_cfg_t *cfg );
```

- `gyro6_init` Initialization function.
```c
err_t gyro6_init ( gyro6_t *ctx, gyro6_cfg_t *cfg );
```

- `gyro6_default_cfg` Click Default Configuration function.
```c
err_t gyro6_default_cfg ( gyro6_t *ctx );
```

#### Example key functions :

- `gyro6_get_axis` This function reads the gyroscope values for all three axis.
```c
err_t gyro6_get_axis ( gyro6_t *ctx, float *x_axis, float *y_axis, float *z_axis );
```

- `gyro6_read_die_temperature` This function reads the chip internal temperature.
```c
err_t gyro6_read_die_temperature ( gyro6_t *ctx, float *temperature );
```

- `gyro6_set_low_power_mode` This function enables low power mode and sets the sample rate and average sample data.
```c
err_t gyro6_set_low_power_mode ( gyro6_t *ctx, uint8_t sample_rate, uint8_t average );
```

## Example Description

> This example demonstrates the use of Gyro 6 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    gyro6_cfg_t gyro6_cfg;  /**< Click config object. */

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
    gyro6_cfg_setup( &gyro6_cfg );
    GYRO6_MAP_MIKROBUS( gyro6_cfg, MIKROBUS_1 );
    err_t init_flag  = gyro6_init( &gyro6, &gyro6_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    if ( GYRO6_ERROR == gyro6_default_cfg ( &gyro6 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data to be ready, then reads the values of all three axis
> and displays the results on the USB UART. The data sample rate is set to 10Hz by default,
> therefore the data is being read approximately every 100ms.

```c

void application_task ( void )
{
    if ( gyro6_get_int_pin ( &gyro6 ) )
    {
        float x_axis_value = 0;
        float y_axis_value = 0;
        float z_axis_value = 0;

        if ( GYRO6_OK == gyro6_get_axis ( &gyro6, &x_axis_value, &y_axis_value, &z_axis_value ) )
        {
            log_printf( &logger, " X : %.2f\r\n", x_axis_value );
            log_printf( &logger, " Y : %.2f\r\n", y_axis_value );
            log_printf( &logger, " Z : %.2f\r\n\n", z_axis_value );
        }
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro6

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
