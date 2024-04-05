\mainpage Main Page

---
# LIN Hall 2 click

> LIN Hall 2 Click is a compact add-on board representing a linear Hall-effect sensing solution. This board features the TMAG5253, a low-power linear Hall-effect sensor from Texas Instruments. The sensor responds proportionally to the magnetic flux density with a magnetic sensitivity range of ±80mT and outputs proportional analog voltage.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/linhall2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lin-hall-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : ADC type


# Software Support

We provide a library for the LIN Hall 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LIN Hall 2 Click driver.

#### Standard key functions :

- `linhall2_cfg_setup` Config Object Initialization function.
```c
void linhall2_cfg_setup ( linhall2_cfg_t *cfg );
```

- `linhall2_init` Initialization function.
```c
err_t linhall2_init ( linhall2_t *ctx, linhall2_cfg_t *cfg );
```

#### Example key functions :

- `linhall2_read_an_pin_voltage` LIN Hall 2 read AN pin voltage level function.
```c
err_t linhall2_read_an_pin_voltage ( linhall2_t *ctx, float *data_out );
```

- `linhal2_set_en_pin` LIN Hall 2 set EN pin state function.
```c
void linhal2_set_en_pin ( linhall2_t *ctx, uint8_t pin_state );
```

- `linhal2_get_flux_density` LIN Hall 2 read flux density function.
```c
err_t linhal2_get_flux_density ( linhall2_t *ctx, float *data_out );
```

## Example Description

> This is an example which demonstrates the use of LIN Hall 2 Click board by measuring 
  magnetic field density and showing it in mT as well as detecting the orientation of the magnet.

**The demo application is composed of two sections :**

### Application Init

> The initialization of ADC module and log UART.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    linhall2_cfg_t linhall2_cfg;  /**< Click config object. */

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
    linhall2_cfg_setup( &linhall2_cfg );
    LINHALL2_MAP_MIKROBUS( linhall2_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == linhall2_init( &linhall2, &linhall2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    linhal2_set_en_pin( &linhall2, LINHALL2_ENABLE_DEVICE );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> The demo application reads the Magnetic field density and showing it in mT 
 as well as the orientation of the magnet.

```c

void application_task ( void ) 
{
    float mag_flux = 0;
    if ( LINHALL2_OK == linhal2_get_flux_density ( &linhall2, &mag_flux ) ) 
    {
        log_printf( &logger, " Magnetic flux density: %.3f[mT]\r\n", mag_flux );
        if ( 0 < mag_flux )
        {
            log_printf( &logger, " Magnetic field oriented South \r\n\n" );
        }
        else
        {
            log_printf( &logger, " Magnetic field oriented North \r\n\n" );
        }
        Delay_ms ( 1000 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LINHall2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
