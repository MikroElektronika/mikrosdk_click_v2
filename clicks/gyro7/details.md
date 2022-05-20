
---
# Gyro 7 click

> Gyro 7 Click is a compact add-on board that contains a high-performance gyroscope. This board features the ICG-1020S, a dual-axis MEMS angular rate sensor (gyroscope) from TDK InvenSense. The ICG-1020S provides extremely low RMS noise as well as noise density. The high-resolution gyroscope supports a full-scale programmable range of ±46.5dps to ±374dps, a fast sample rate at up to 32kHz, an SPI serial interface, and extremely low power consumption. This Click board™ is designed for optical image stabilization (OIS) applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gyro-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Apr 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Gyro 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Gyro 7 Click driver.

#### Standard key functions :

- `gyro7_cfg_setup` Config Object Initialization function.
```c
void gyro7_cfg_setup ( gyro7_cfg_t *cfg );
```

- `gyro7_init` Initialization function.
```c
err_t gyro7_init ( gyro7_t *ctx, gyro7_cfg_t *cfg );
```

- `gyro7_default_cfg` Click Default Configuration function.
```c
err_t gyro7_default_cfg ( gyro7_t *ctx );
```

#### Example key functions :

- `gyro7_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t gyro7_get_int_pin ( gyro7_t *ctx );
```

- `gyro7_read_gyroscope` This function reads the gyroscope X and Y axis in degrees per second (dps).
```c
err_t gyro7_read_gyroscope ( gyro7_t *ctx, float *x_axis, float *y_axis );
```

- `gyro7_read_temperature` This function reads the internal temperature in Celsius.
```c
err_t gyro7_read_temperature ( gyro7_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Gyro 7 click board by reading and displaying
the values of X and Y axis in degrees per second and the chip internal temperature in Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the sample rate
to 40 Hz, gyroscope resolution to 374 dps, and enables the data ready interrupt.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gyro7_cfg_t gyro7_cfg;  /**< Click config object. */

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
    gyro7_cfg_setup( &gyro7_cfg );
    GYRO7_MAP_MIKROBUS( gyro7_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == gyro7_init( &gyro7, &gyro7_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GYRO7_ERROR == gyro7_default_cfg ( &gyro7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the values of X and Y gyroscope axis as well as
the chip internal temperature and displays the results on the USB UART. The data sample rate is
set to 40Hz by default, therefore the data is being read approximately every 25ms.

```c
void application_task ( void )
{
    if ( gyro7_get_int_pin ( &gyro7 ) )
    {
        float x_axis, y_axis, temperature;
        if ( GYRO7_OK == gyro7_read_gyroscope ( &gyro7, &x_axis, &y_axis ) )
        {
            log_printf( &logger, " X : %.2f dps\r\n", x_axis );
            log_printf( &logger, " Y : %.2f dps\r\n", y_axis );
        }
        if ( GYRO7_OK == gyro7_read_temperature ( &gyro7, &temperature ) )
        {
            log_printf( &logger, " Temperature : %.2f C\r\n\n", temperature );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
