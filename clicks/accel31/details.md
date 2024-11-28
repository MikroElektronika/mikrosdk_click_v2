
---
# Accel 31 Click

> Accel 31 Click is a compact add-on board designed for precise motion and orientation detection in space-constrained devices. This board features the BMA580, a triaxial low-g accelerometer from Bosch Sensortec, which offers a 16-bit digital resolution with measurement ranges of ±2, ±4, ±8, and ±16 g, along with flexible output data rates from 1.56Hz to 6.4kHz, enabling high adaptability and accuracy. The BMA580 supports advanced power modes, including high-performance and low-power, self-wake-up functionality, and bone conduction-based voice activity detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel31_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/accel-31-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2024.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel 31 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Accel 31 Click driver.

#### Standard key functions :

- `accel31_cfg_setup` Config Object Initialization function.
```c
void accel31_cfg_setup ( accel31_cfg_t *cfg );
```

- `accel31_init` Initialization function.
```c
err_t accel31_init ( accel31_t *ctx, accel31_cfg_t *cfg );
```

- `accel31_default_cfg` Click Default Configuration function.
```c
err_t accel31_default_cfg ( accel31_t *ctx );
```

#### Example key functions :

- `accel31_get_data` This function reads the accelerometer and temperature measurement data.
```c
err_t accel31_get_data ( accel31_t *ctx, accel31_data_t *data_out );
```

- `accel31_set_accel_odr` This function sets the accel measurement output data rate.
```c
err_t accel31_set_accel_odr ( accel31_t *ctx, uint8_t odr );
```

- `accel31_set_accel_fsr` This function sets the accel measurement full scale range.
```c
err_t accel31_set_accel_fsr ( accel31_t *ctx, uint8_t fsr );
```

## Example Description

> This example demonstrates the use of Accel 31 Click board by reading and displaying 
the accelerometer data (X, Y, and Z axis) and a temperature measurement in degrees Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel31_cfg_t accel31_cfg;  /**< Click config object. */

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
    accel31_cfg_setup( &accel31_cfg );
    ACCEL31_MAP_MIKROBUS( accel31_cfg, MIKROBUS_1 );
    err_t init_flag = accel31_init( &accel31, &accel31_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ACCEL31_ERROR == accel31_default_cfg ( &accel31 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Checks for a new data ready indication and then reads the accelerometer and temperature
measurements. The results are displayed on the USB UART at 12.5 Hz output data rate.

```c
void application_task ( void )
{
    accel31_data_t meas_data;
    if ( ACCEL31_OK == accel31_get_data ( &accel31, &meas_data ) )
    {
        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
        log_printf( &logger, " Temperature: %d degC\r\n\n", ( int16_t ) meas_data.temperature );
        Delay_ms ( 80 );
    }
}
```

## Note

> The Click board determines the communication protocol at the first communication check
after power-up. In the case of I2C, the IC responds with NACK on the first check,
which blocks the I2C bus on some MCUs. Re-running the program (without power cycling
the Click board power supply) should unlock the communication and solve this issue.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel31

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
