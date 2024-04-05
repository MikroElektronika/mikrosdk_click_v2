
---
# Magneto 13 click

> Magneto 13 Click is a compact add-on board with an accurate and reliable magnetic device. 
> This board features the MA736, a contactless digital angle sensor from Monolithic Power Systems. 
> It is a MagAlpha sensor that detects the absolute angular position of a permanent magnet, 
> typically a diametrically magnetized cylinder or a rotating shaft. 
> The MA736 sensor supports a wide range of magnetic field strengths, end-of-shaft, 
> and side-shaft (off-axis mounting) spatial configurations.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto13_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-13-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Magneto 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto 13 Click driver.

#### Standard key functions :

- `magneto13_cfg_setup` Config Object Initialization function.
```c
void magneto13_cfg_setup ( magneto13_cfg_t *cfg );
```

- `magneto13_init` Initialization function.
```c
err_t magneto13_init ( magneto13_t *ctx, magneto13_cfg_t *cfg );
```

- `magneto13_default_cfg` Click Default Configuration function.
```c
err_t magneto13_default_cfg ( magneto13_t *ctx );
```

#### Example key functions :

- `magneto13_get_angle` Magneto 13 gets the angular position function.
```c
err_t magneto13_get_angle ( magneto13_t *ctx, float *angle );
```

- `magneto13_get_field_strength` Magneto 13 gets the magnetic field strength function.
```c
err_t magneto13_get_field_strength ( magneto13_t *ctx, uint8_t *field_strength );
```

- `magneto13_set_mag_field_thd` Magneto 13 sets the magnetic field threshold function.
```c
err_t magneto13_set_mag_field_thd ( magneto13_t *ctx, uint8_t mglt, uint8_t mght );
```

## Example Description

> This library contains API for the Magneto 13 Click driver.
> The demo application reads and displays 
> the magnet's angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneto13_cfg_t magneto13_cfg;  /**< Click config object. */

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
    magneto13_cfg_setup( &magneto13_cfg );
    MAGNETO13_MAP_MIKROBUS( magneto13_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneto13_init( &magneto13, &magneto13_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO13_ERROR == magneto13_default_cfg ( &magneto13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------- \r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Magneto 13 Click board™.
> Reads and displays the magnet's angular position in degrees.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t field_strength = 0;
    static float angle = 0;
    if ( MAGNETO13_OK == magneto13_get_field_strength( &magneto13, &field_strength ) )
    {
        if ( ( MAGNETO13_FLD_ST_OK == field_strength ) && ( MAGNETO13_OK == magneto13_get_angle( &magneto13, &angle ) ) )
        {
            log_printf( &logger, " Angle: %.2f [deg]\r\n", angle );
            log_printf( &logger, " -------------------- \r\n" );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
