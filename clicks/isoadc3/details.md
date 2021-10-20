
---
# ISO ADC 3 click

> ISO ADC 3 Click is a compact add-on board that contains a single-channel precision isolation amplifier. This board features the AMC1100, a precision isolation amplifier with an output separated from the input circuitry by a silicon dioxide barrier that is highly resistant to magnetic interference from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/isoadc3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/iso-adc-3-click)

---

#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the ISOADC3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for ISOADC3 Click driver.

#### Standard key functions :

- `isoadc3_cfg_setup` Config Object Initialization function.
```c
void isoadc3_cfg_setup ( isoadc3_cfg_t *cfg );
```

- `isoadc3_init` Initialization function.
```c
err_t isoadc3_init ( isoadc3_t *ctx, isoadc3_cfg_t *cfg );
```

#### Example key functions :

- `isoadc3_read_adc` Read ADC function.
```c
uint16_t isoadc3_read_adc ( isoadc3_t *ctx );
```

- `isoadc3_get_adc_voltage` Read ADC voltage function.
```c
uint16_t isoadc3_get_adc_voltage ( isoadc3_t *ctx, uint16_t v_ref );
```

- `isoadc3_read_voltage` Read voltage function.
```c
uint16_t isoadc3_read_voltage ( isoadc3_t *ctx, uint16_t v_ref );
```

## Example Description

> This example shows the capabilities of the ISO ADC 3 click.

**The demo application is composed of two sections :**

### Application Init

> Initalizes I2C driver and makes an initial log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc3_cfg_t isoadc3_cfg;  /**< Click config object. */

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
    isoadc3_cfg_setup( &isoadc3_cfg );
    ISOADC3_MAP_MIKROBUS( isoadc3_cfg, MIKROBUS_1 );
    err_t init_flag = isoadc3_init( &isoadc3, &isoadc3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Measures ADC voltage level and prints it via USB UART terminal.

```c

void application_task ( void ) {
    voltage = isoadc3_read_voltage( &isoadc3, ISOADC3_VREF_3V3 );
    log_printf( &logger, " ADC voltage Level: %d mV \r\n", voltage );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ISOADC3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
