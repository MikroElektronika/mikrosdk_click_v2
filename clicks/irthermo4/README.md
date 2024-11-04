\mainpage Main Page

---
# IR Thermo 4 Click

> IR Thermo 4 Click is a compact add-on board for precise remote sensing applications. This board features the TPiS 1T 1386 L5.5 H thermopile sensor from Excelitas, known for its high accuracy and narrow 5° field of view (FoV). This sensor, part of the CaliPile™ family, features factory-calibrated data stored in EEPROM, ensuring reliable and accurate performance. The sensor also comes in an isothermal TO-39 package with an integrated lens hood for minimized stray light and enhanced thermal stability, making it ideal for challenging environmental conditions. With a built-in ADC and multiple filter options, the sensor's data is easily accessible via an I2C interface. IR Thermo 4 Click is well-suited for remote skin temperature monitoring, over-temperature protection, human presence sensing, and motion detection.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irthermo4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-thermo-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the IR Thermo 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Thermo 4 Click driver.

#### Standard key functions :

- `irthermo4_cfg_setup` Config Object Initialization function.
```c
void irthermo4_cfg_setup ( irthermo4_cfg_t *cfg );
```

- `irthermo4_init` Initialization function.
```c
err_t irthermo4_init ( irthermo4_t *ctx, irthermo4_cfg_t *cfg );
```

- `irthermo4_default_cfg` Click Default Configuration function.
```c
err_t irthermo4_default_cfg ( irthermo4_t *ctx );
```

#### Example key functions :

- `irthermo4_read_ambient_temp` This function reads and calculates the ambient temperature in degrees Celsius.
```c
err_t irthermo4_read_ambient_temp ( irthermo4_t *ctx, float *t_amb );
```

- `irthermo4_read_object_temp` This function reads and calculates the object temperature in degrees Celsius.
```c
err_t irthermo4_read_object_temp ( irthermo4_t *ctx, float *t_obj, float t_amb );
```

- `irthermo4_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t irthermo4_get_int_pin ( irthermo4_t *ctx );
```

## Example Description

> This example demonstrates the use of IR Thermo 4 Click board by reading and displaying the ambient and object temperature measurements.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo4_cfg_t irthermo4_cfg;  /**< Click config object. */

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
    irthermo4_cfg_setup( &irthermo4_cfg );
    IRTHERMO4_MAP_MIKROBUS( irthermo4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irthermo4_init( &irthermo4, &irthermo4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRTHERMO4_ERROR == irthermo4_default_cfg ( &irthermo4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ambient and object temperature measurements twice per second and displays the results on the USB UART.

```c
void application_task ( void )
{
    float ambient_temp = 0;
    float object_temp = 0;
    if ( IRTHERMO4_OK == irthermo4_read_ambient_temp ( &irthermo4, &ambient_temp ) )
    {
        log_printf ( &logger, " Ambient temperature: %.2f degC\r\n", ambient_temp );
        if ( IRTHERMO4_OK == irthermo4_read_object_temp ( &irthermo4, &object_temp, ambient_temp ) )
        {
            log_printf ( &logger, " Object temperature: %.2f degC\r\n\n", object_temp );
        }
    }
    Delay_ms ( 500 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRThermo4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
