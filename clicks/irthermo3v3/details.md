
---
# IrThermo 3V3 Click

IrThermo Click 3.3V is a contactless temperature measurement device that relies on the accurate thermopile sensor chip, which encompasses both the thermopile sensor element and the ASSP. The ASSP - signal conditioning circuitry features 17bit ADC and powerful DSP which allow high degree of accuracy and wide temperature measurement range. The IrThermo Click is equipped with both the 10bit PWM interface and the SMBus/I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irthermo3v3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/irthermo-33v-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the IrThermo3V3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IrThermo3V3 Click driver.

#### Standard key functions :

- `irthermo3v3_cfg_setup` Config Object Initialization function.
```c
void irthermo3v3_cfg_setup ( irthermo3v3_cfg_t *cfg );
```

- `irthermo3v3_init` Initialization function.
```c
err_t irthermo3v3_init ( irthermo3v3_t *ctx, irthermo3v3_cfg_t *cfg );
```

#### Example key functions :

- `irthermo3v3_get_t_ambient` Reads Temperature ambient from sensor.
```c
float irthermo3v3_get_t_ambient ( irthermo3v3_t* ctx );
```

- `irthermo3v3_get_t_object` Reads Temperature object1 from sensor.
```c
float irthermo3v3_get_t_object ( irthermo3v3_t* ctx );
```

## Example Description

> This application collects data from the sensor, and logs the results.

**The demo application is composed of two sections :**

### Application Init

> Initializes IrThermo 3V3 Driver.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo3v3_cfg_t irthermo3v3_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init \r\n " );
    log_printf( &logger, "--------------------------------\r\n " );

    // Click initialization.
    irthermo3v3_cfg_setup( &irthermo3v3_cfg );
    IRTHERMO3V3_MAP_MIKROBUS( irthermo3v3_cfg, MIKROBUS_1 );
    err_t init_flag = irthermo3v3_init( &irthermo3v3, &irthermo3v3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task \r\n" );
    log_printf( &logger, " --------------------------------\r\n " );
}

```

### Application Task

> Reading Ambient and Object Temperature and displaying the value periodically.

```c

void application_task ( void ) {
    measured_temperature = irthermo3v3_get_t_ambient( &irthermo3v3 );
    object_temperature = irthermo3v3_get_t_object( &irthermo3v3 );
    log_printf( &logger, " Ambient Temperature: %.2f\r\n ", measured_temperature );
    log_printf( &logger, " Object Temperature: %.2f\r\n ", object_temperature );
    log_printf( &logger, " --------------------------------\r\n " );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IrThermo3V3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
