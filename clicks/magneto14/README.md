\mainpage Main Page

---
# Magneto 14 click

> Magneto 14 Click is a compact add-on board with an accurate and reliable magnetic device. This board features the MA735, a contactless angle sensor with ABZ, and PWM output from Monolithic Power Systems. The MA735 sensor has a 9-bit to 13-bit resolution of the absolute angle encoder.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-14-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : SPI type


# Software Support

We provide a library for the Magneto 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magneto 14 Click driver.

#### Standard key functions :

- `magneto14_cfg_setup` Config Object Initialization function.
```c
void magneto14_cfg_setup ( magneto14_cfg_t *cfg );
```

- `magneto14_init` Initialization function.
```c
err_t magneto14_init ( magneto14_t *ctx, magneto14_cfg_t *cfg );
```

- `magneto14_default_cfg` Click Default Configuration function.
```c
err_t magneto14_default_cfg ( magneto14_t *ctx );
```

#### Example key functions :

- `magneto14_get_angle` Magneto 14 gets the angular position function.
```c
err_t magneto14_get_angle ( magneto14_t *ctx, float *angle );
```

- `magneto14_get_field_strength` Magneto 14 gets the magnetic field strength function.
```c
err_t magneto14_get_field_strength ( magneto14_t *ctx, uint8_t *field_strength );
```

- `magneto14_get_mgh` Magneto 14 gets the MGH function.
```c
uint8_t magneto14_get_mgh ( magneto14_t *ctx );
```

## Example Description

> This library contains API for the Magneto 14 Click driver.
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
    magneto14_cfg_t magneto14_cfg;  /**< Click config object. */

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
    magneto14_cfg_setup( &magneto14_cfg );
    MAGNETO14_MAP_MIKROBUS( magneto14_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneto14_init( &magneto14, &magneto14_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETO14_ERROR == magneto14_default_cfg ( &magneto14 ) )
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

> This example demonstrates the use of the Magneto 14 Click board™.
> Reads and displays the magnet's angular position in degrees.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t field_strength = 0;
    static float angle = 0;
    if ( MAGNETO14_OK == magneto14_get_field_strength( &magneto14, &field_strength ) )
    {
        if ( ( MAGNETO14_FLD_ST_OK == field_strength ) && 
             ( MAGNETO14_MGH_ST_OK == magneto14_get_mgh( &magneto14 ) ) && 
             ( MAGNETO14_OK == magneto14_get_angle( &magneto14, &angle ) ) )
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
- Click.Magneto14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
