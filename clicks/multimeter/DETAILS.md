
---
# Multimeter click

<Multimeter click is a Click board™ designed to measure voltage, current, resistance, and capacitance properties of the components, connected to the input terminals. Each property measurement is done on a separate terminal.>

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/multimeter_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/multimeter-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Multimeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Multimeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void multimeter_cfg_setup ( multimeter_cfg_t *cfg ); 
 
- Initialization function.
> MULTIMETER_RETVAL multimeter_init ( multimeter_t *ctx, multimeter_cfg_t *cfg );

- Click Default Configuration function.
> void multimeter_default_cfg ( multimeter_t *ctx );

#### Example key functions :

- This function reads and returns resistance data.
> float multimeter_read_resistance ( multimeter_t *ctx );
 
- This function reads and returns voltage data.
> float multimeter_read_voltage ( multimeter_t *ctx );

- This function reads and returns current data.
> float multimeter_read_current ( multimeter_t *ctx );

## Examples Description

> This example showcases how to configure, initialize and use the Multimeter click. The
  click measures resistance in Ohms, voltage in mVs, current in mAs and capacitance in nFs
  using a dual CMOS and quad CMOS op-amps, an ADC and other on board modules. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. Additional 
  calibration of the measurement components is done in the default_cfg(...) function.

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    multimeter_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    multimeter_cfg_setup( &cfg );
    MULTIMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    multimeter_init( &multimeter, &cfg );
    multimeter_default_cfg( &multimeter );
}
  
```

### Application Task

> This function measures and displays resistance, voltage, current and capacitance data.
  It does so every second. 

```c

void application_task ( )
{
    float resistance;
    float voltage;
    float current;
    float capacitance;

    resistance = multimeter_read_resistance( &multimeter );
    log_printf( &logger, " * Resistance: %.3f Ohms * \r\n", resistance );

    voltage = multimeter_read_voltage( &multimeter );
    log_printf( &logger, " * Voltage: %.3f mV * \r\n", voltage );

    current = multimeter_read_current( &multimeter );
    log_printf( &logger, " * Current: %.3f mA * \r\n", current );

    capacitance = multimeter_read_capacitance( &multimeter );
    log_printf( &logger, " * Capacitance: %.3f nF * \r\n", capacitance );

    log_printf( &logger, "------------------------\r\n" );
    Delay_1sec( );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Multimeter

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
