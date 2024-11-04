
---
# Compass 7 Click

> Compass 7 Click is a compact add-on board perfect for applications like an electronic compass. This board features the MMC5633NJL, a monolithic complete 3-axis AMR magnetic sensor with on-chip signal processing and an integrated digital bus from MEMSIC. It can measure magnetic fields within the full-scale range of ±30 Gauss (G) with up to 0.0625mG per LSB resolution at 20bits operation mode and 2mG total RMS noise level, enabling heading accuracy of ±1º in electronic compass applications. Also, an integrated SET/RESET function eliminates thermal variation-induced offset error (Null field output) and clears the residual magnetization resulting from powerful external fields.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/compass-7-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Compass 7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Compass 7 Click driver.

#### Standard key functions :

- `compass7_cfg_setup` Config Object Initialization function.
```c
void compass7_cfg_setup ( compass7_cfg_t *cfg );
```

- `compass7_init` Initialization function.
```c
err_t compass7_init ( compass7_t *ctx, compass7_cfg_t *cfg );
```

- `compass7_default_cfg` Click Default Configuration function.
```c
err_t compass7_default_cfg ( compass7_t *ctx );
```

#### Example key functions :

- `compass7_set_measurement_mode` This function sets the control and ODR registers for the selected measurement mode.
```c
err_t compass7_set_measurement_mode ( compass7_t *ctx, uint8_t mode );
```

- `compass7_get_magnetic_flux` This function reads the raw values of X, Y, and Z axis and converts them to magnetic flux data in Gauss.
```c
err_t compass7_get_magnetic_flux ( compass7_t *ctx, compass7_magnetic_flux_t *flux );
```

- `compass7_get_temperature` This function reads the temperature measurements in Celsius.
```c
err_t compass7_get_temperature ( compass7_t *ctx, float *temperature );
```

## Example Description

> This example demonstrates the use of Compass 7 Click board by reading and displaying the magnetic field strength of 3-axis as well as the temperature measurements in Celsius.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    compass7_cfg_t compass7_cfg;  /**< Click config object. */

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
    compass7_cfg_setup( &compass7_cfg );
    COMPASS7_MAP_MIKROBUS( compass7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == compass7_init( &compass7, &compass7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COMPASS7_ERROR == compass7_default_cfg ( &compass7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Starts the single magnetic measurement and reads the magnetic field strength of 3-axis in Gauss, then starts the temperature measurement and reads the temperature in Celsius.
The results are being displayed on the USB UART every 100ms approximately.

```c
void application_task ( void )
{
    compass7_magnetic_flux_t magnetic_flux;
    float temperature;
    if ( ( COMPASS7_OK == compass7_set_measurement_mode ( &compass7, COMPASS7_MEAS_SINGLE_M ) ) &&
         ( COMPASS7_OK == compass7_get_magnetic_flux ( &compass7, &magnetic_flux ) ) )
    {
        log_printf ( &logger, " X: %.2f G\r\n", magnetic_flux.x_axis );
        log_printf ( &logger, " Y: %.2f G\r\n", magnetic_flux.y_axis );
        log_printf ( &logger, " Z: %.2f G\r\n", magnetic_flux.z_axis );
    }
    if ( ( COMPASS7_OK == compass7_set_measurement_mode ( &compass7, COMPASS7_MEAS_SINGLE_T ) ) &&
         ( COMPASS7_OK == compass7_get_temperature ( &compass7, &temperature ) ) )
    {
        log_printf ( &logger, " Temperature: %.2f C\r\n\n", temperature );
    }
    Delay_ms ( 100 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
