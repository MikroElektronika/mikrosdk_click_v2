
---
# IrThermo 5V click

IrThermo click 5V is a contactless temperature measurement device that relies on the accurate thermopile sensor chip, which encompasses both the thermopile sensor element and the ASSP. The ASSP - signal conditioning circuitry features 17bit ADC and powerful DSP which allow high degree of accuracy and wide temperature measurement range. The IrThermo click is equipped with both the 10bit PWM interface and the SMBus/I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irthermo5v_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/irthermo-5v-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the IrThermo5V Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IrThermo5V Click driver.

#### Standard key functions :

- `irthermo5v_cfg_setup` Config Object Initialization function.
```c
void irthermo5v_cfg_setup ( irthermo5v_cfg_t *cfg );
```

- `irthermo5v_init` Initialization function.
```c
err_t irthermo5v_init ( irthermo5v_t *ctx, irthermo5v_cfg_t *cfg );
```

#### Example key functions :

- `irthermo5v_get_t_ambient` Reads Temperature ambient from sensor.
```c
float irthermo5v_get_t_ambient ( irthermo5v_t* ctx );
```

- `irthermo5v_get_t_object` Reads Temperature object1 from sensor.
```c
float irthermo5v_get_t_object ( irthermo5v_t* ctx );
```

## Example Description

> This application collects data from the sensor, and logs the results.

**The demo application is composed of two sections :**

### Application Init

> Initializes IrThermo 5V Driver.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    irthermo5v_cfg_t irthermo5v_cfg;  /**< Click config object. */

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
    irthermo5v_cfg_setup( &irthermo5v_cfg );
    IRTHERMO5V_MAP_MIKROBUS( irthermo5v_cfg, MIKROBUS_1 );
    err_t init_flag = irthermo5v_init( &irthermo5v, &irthermo5v_cfg );
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
    measured_temperature = irthermo5v_get_t_ambient( &irthermo5v );
    object_temperature = irthermo5v_get_t_object( &irthermo5v );
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
- Click.IrThermo5V

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
