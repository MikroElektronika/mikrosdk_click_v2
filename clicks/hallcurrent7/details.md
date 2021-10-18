
---
# Hall Current 7 click

> Hall Current 7 Click is a compact add-on board that provides economical and precise solutions for AC or DC current sensing. This board features the ACS770, a thermally enhanced, fully integrated, Hall effect-based high precision linear current sensor with 100µΩ current conductor from Allegro MicroSystems. Applied current flows directly into the integrated conductor generating a magnetic field, and an integrated low-hysteresis core concentrates the magnetic field sensed by the Hall element with a typical accuracy of ±1% and 120 kHz bandwidth.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for HallCurrent7 Click driver.

#### Standard key functions :

- `hallcurrent7_cfg_setup` Config Object Initialization function.
```c
void hallcurrent7_cfg_setup ( hallcurrent7_cfg_t *cfg );
```

- `hallcurrent7_init` Initialization function.
```c
err_t hallcurrent7_init ( hallcurrent7_t *ctx, hallcurrent7_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent7_read_voltage` Read voltage function.
```c
uint16_t hallcurrent7_read_voltage ( hallcurrent7_t *ctx, uint16_t v_ref );
```

- `hallcurrent7_calc_current` Calculate current function.
```c
int16_t hallcurrent7_calc_current ( hallcurrent7_t *ctx, uint16_t v_ref );
```

- `hallcurrent7_avg_current` Calculate Average current function.
```c
int16_t hallcurrent7_avg_current ( hallcurrent7_t *ctx, uint16_t v_ref );
```

## Example Description

> This example shows the capabilities of the Hall Current 7 click board.

**The demo application is composed of two sections :**

### Application Init

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent7_cfg_t hallcurrent7_cfg;  /**< Click config object. */

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
    hallcurrent7_cfg_setup( &hallcurrent7_cfg );
    HALLCURRENT7_MAP_MIKROBUS( hallcurrent7_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent7_init( &hallcurrent7, &hallcurrent7_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measuring current passing through the on board Hall Effect Sensor and displaying data every two seconds.

```c

void application_task ( void ) {
    current = hallcurrent7_avg_current( &hallcurrent7, HALLCURRENT7_VREF_5000_mV );
    log_printf( &logger, "Current: %d mA\r\n", current );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 2000 );
}

```

## Note

> In order to get correct calculations user should change "v_ref" value to his own power supply voltage.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
