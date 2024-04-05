\mainpage Main Page

---
# DIGI POT 14 click

> DIGI POT 14 Click is a compact add-on board that contains a digitally controlled potentiometer. This board features the TPL0102, a dual-channel digital potentiometer with non-volatile memory from Texas Instruments. It is a 100K resistance end-to-end potentiometer with a 256-position resolution, where the wiper position can be stored in EEPROM. It can operate from both 3.3V and 5V power supplies and provides a typical 92ppm/ºC end-to-end nominal resistance temperature coefficient and only 4ppm/ºC ratiometric.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-14-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the DIGI POT 14 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGI POT 14 Click driver.

#### Standard key functions :

- `digipot14_cfg_setup` Config Object Initialization function.
```c
void digipot14_cfg_setup ( digipot14_cfg_t *cfg );
```

- `digipot14_init` Initialization function.
```c
err_t digipot14_init ( digipot14_t *ctx, digipot14_cfg_t *cfg );
```

- `digipot14_default_cfg` Click Default Configuration function.
```c
err_t digipot14_default_cfg ( digipot14_t *ctx );
```

#### Example key functions :

- `digipot14_reg_write` DIGI POT 14 register write function.
```c
err_t digipot14_reg_write ( digipot14_t *ctx, uint8_t reg, uint8_t data_in );
```

- `digipot14_set_pot_a_wiper` DIGI POT 14 set the wiper position of potentiometer A function.
```c
err_t digipot14_set_pot_a_wiper ( digipot14_t *ctx, uint8_t wiper_pos );
```

- `digipot14_set_pot_b_wiper` DIGI POT 14 set the wiper position of potentiometer B function.
```c
err_t digipot14_set_pot_b_wiper ( digipot14_t *ctx, uint8_t wiper_pos );
```

## Example Description

> This library contains API for DIGI POT 14 Click driver.
  The demo application uses a digital potentiometer 
  to change the resistance values.

**The demo application is composed of two sections :**

### Application Init

> The initialization of I2C module, log UART, and additional pins.
  After the driver init, the app executes a default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot14_cfg_t digipot14_cfg;  /**< Click config object. */

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
    digipot14_cfg_setup( &digipot14_cfg );
    DIGIPOT14_MAP_MIKROBUS( digipot14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot14_init( &digipot14, &digipot14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT14_ERROR == digipot14_default_cfg ( &digipot14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the DIGI POT 14 Click board™.
  The demo application iterates through the entire wiper range.
  Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( uint8_t wiper_val = DIGIPOT14_MIN_POSITION; wiper_val <= DIGIPOT14_MAX_POSITION; wiper_val++ )
    {
        
        digipot14_set_pot_a_wiper( &digipot14, wiper_val );
        digipot14_set_pot_b_wiper( &digipot14, wiper_val );
        log_printf( &logger, " Resistance = %.3f KOhm \r\n", 
                    ( DIGIPOT14_MAX_RESISTANCE_KOHM * ( wiper_val / DIGIPOT14_MAX_POSITION_NUM ) ) );
        Delay_ms ( 1000 );
    }
}
```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT14

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
