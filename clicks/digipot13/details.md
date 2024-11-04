
---
# DIGI POT 13 Click

> DIGI POT 13 Click is a compact add-on board that contains a digitally controlled potentiometer. 
> This board features the MAX5419, a 256-tap non-volatile digital potentiometer from Analog Devices. 
> On this Click board™, one digitally I2C-controlled potentiometer is realized 
> with typical end-to-end resistance values of 200kΩ. It can operate from both 3.3V and 5V power supplies 
> and provides a low 35ppm/ºC end-to-end nominal resistance temperature coefficient and only 5ppm/ºC ratiometric.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot13_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/digi-pot-13-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the DIGI POT 13 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI POT 13 Click driver.

#### Standard key functions :

- `digipot13_cfg_setup` Config Object Initialization function.
```c
void digipot13_cfg_setup ( digipot13_cfg_t *cfg );
```

- `digipot13_init` Initialization function.
```c
err_t digipot13_init ( digipot13_t *ctx, digipot13_cfg_t *cfg );
```

- `digipot13_default_cfg` Click Default Configuration function.
```c
err_t digipot13_default_cfg ( digipot13_t *ctx );
```

#### Example key functions :

- `digipot13_set_resistance` DIGI POT 13 set the resistance function.
```c
err_t digipot13_set_resistance ( digipot13_t *ctx, digipot13_cfg_res_t cfg_res, float res_kohm );
```

- `digipot13_set_wiper_pos` DIGI POT 13 set the wiper position function.
```c
err_t digipot13_set_wiper_pos ( digipot13_t *ctx, uint8_t wiper_pos );
```

- `digipot13_write_data` DIGI POT 13 write data function.
```c
err_t digipot13_write_data ( digipot13_t *ctx, uint8_t cmd, uint8_t data_in );
```

## Example Description

> This library contains API for DIGI POT 13 Click driver.
> The demo application uses a digital potentiometer 
> to change the resistance values.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module, log UART, and additional pins.
> After the driver init, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot13_cfg_t digipot13_cfg;  /**< Click config object. */

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
    digipot13_cfg_setup( &digipot13_cfg );
    DIGIPOT13_MAP_MIKROBUS( digipot13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot13_init( &digipot13, &digipot13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT13_ERROR == digipot13_default_cfg ( &digipot13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the DIGI POT 13 Click board™.
> The demo application iterates through the entire wiper range and 
> sets the resistance in steps of approximately 50 kOhm.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t res_kohm = DIGIPOT13_RES_0_KOHM; res_kohm <= DIGIPOT13_RES_200_KOHM; res_kohm += DIGIPOT13_RES_50_KOHM )
    {
        if ( DIGIPOT13_OK == digipot13_set_resistance( &digipot13, DIGIPOT13_CFG_RES_WH, ( float ) res_kohm ) )
        {
            log_printf( &logger, " Resistance: %.1f kOhm\r\n", ( float ) res_kohm );
            log_printf( &logger, " ----------------------------\r\n" );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT13

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
