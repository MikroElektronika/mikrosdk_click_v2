
---
# Magneto 12 click

> Magneto 12 Click is a compact add-on board that contains an accurate and reliable magnetic sensing device. This board features the A31315, a magnetic position sensor designed for on- and off-axis rotary and linear stroke position measurement from Allegro Microsystems. This sensor integrates vertical and planar Hall-effect elements with precision temperature-compensating circuitry to detect two out of three magnetic field components (X and Y). Using configurable signal processing (the user is allowed to process the output signal in analog or digital form), linearization and angle calculation allows the A31315 to accurately resolve the absolute rotary (full 360° and short-stroke <360°) or linear position of a moving magnetic target.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto12_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2022.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the Magneto 12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto 12 Click driver.

#### Standard key functions :

- `magneto12_cfg_setup` Config Object Initialization function.
```c
void magneto12_cfg_setup ( magneto12_cfg_t *cfg );
```

- `magneto12_init` Initialization function.
```c
err_t magneto12_init ( magneto12_t *ctx, magneto12_cfg_t *cfg );
```

#### Example key functions :

- `magneto12_read_voltage` This function reads raw ADC value and converts it to proportional voltage level.
```c
err_t magneto12_read_voltage ( magneto12_t *ctx, float *voltage );
```

- `magneto12_set_vref` This function sets the voltage reference for Magneto 12 click driver.
```c
err_t magneto12_set_vref ( magneto12_t *ctx, float vref );
```

- `magneto12_read_angle` This function reads the sensor output voltage and converts it to angular position in degrees.
```c
err_t magneto12_read_angle ( magneto12_t *ctx, float *angle );
```

## Example Description

> This example demonstrates the use of Magneto 12 click board by reading and displaying the magnet's angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto12_cfg_t magneto12_cfg;  /**< Click config object. */

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
    magneto12_cfg_setup( &magneto12_cfg );
    MAGNETO12_MAP_MIKROBUS( magneto12_cfg, MIKROBUS_1 );
    err_t init_flag = magneto12_init( &magneto12, &magneto12_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.

```c

void application_task ( void )
{
    float angle = 0;
    if ( MAGNETO12_OK == magneto12_read_angle ( &magneto12, &angle ) )
    {
        log_printf( &logger, " Angle: %.2f degrees\r\n\n", angle );
    }
    Delay_ms ( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
