\mainpage Main Page

---
# Magneto 11 click

> Magneto 11 Click is a compact add-on board that contains an accurate and reliable magnetic sensing device. This board features the AS5510, a linear hall sensor with 10-bit resolution, and an I2C interface from ams AG. It can measure the absolute position of lateral movement of a simple 2-pole magnet. A lateral stroke of 0.5mm ~ 2mm can be measured with air gaps around 1.0mm, depending on the magnet size. The AS5510 may be switched to a Power-Down state when it is not used to conserve power. This Click board™ is suitable for position sensing applications requiring a small magnetic range where noise is a critical design parameter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto11_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-11-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Magneto 11 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto 11 Click driver.

#### Standard key functions :

- `magneto11_cfg_setup` Config Object Initialization function.
```c
void magneto11_cfg_setup ( magneto11_cfg_t *cfg );
```

- `magneto11_init` Initialization function.
```c
err_t magneto11_init ( magneto11_t *ctx, magneto11_cfg_t *cfg );
```

- `magneto11_default_cfg` Click Default Configuration function.
```c
err_t magneto11_default_cfg ( magneto11_t *ctx );
```

#### Example key functions :

- `magneto11_get_magnetic_field` This function reads the magnetic field strength in milliTesla.
```c
err_t magneto11_get_magnetic_field ( magneto11_t *ctx, float *mag_field );
```

- `magneto11_set_sensitivity` This function writes specified data to the sensitivity register.
```c
err_t magneto11_set_sensitivity ( magneto11_t *ctx, uint8_t sensitivity );
```

- `magneto11_set_config` This function writes specified data to the config register.
```c
err_t magneto11_set_config ( magneto11_t *ctx, uint8_t config );
```

## Example Description

> This example demonstrates the use of Magneto 11 click board by reading and displaying the magnetic field strength value.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto11_cfg_t magneto11_cfg;  /**< Click config object. */

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
    magneto11_cfg_setup( &magneto11_cfg );
    MAGNETO11_MAP_MIKROBUS( magneto11_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == magneto11_init( &magneto11, &magneto11_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO11_ERROR == magneto11_default_cfg ( &magneto11 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnetic field strength value in milliTesla and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    float magnetic_field;
    if ( MAGNETO11_OK == magneto11_get_magnetic_field ( &magneto11, &magnetic_field ) )
    {
        log_printf ( &logger, " Magnetic Field: %.3f mT \r\n\n", magnetic_field );
        Delay_ms ( 200 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto11

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
