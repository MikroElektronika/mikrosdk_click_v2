
---
# PAC1921 click

PAC1921 click is a versatile power monitoring and measuring device intended for the high speed, low latency measurements. This device can measure current, voltage or the power of the connected load.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pac1921_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/pac1921-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type

# Software Support

We provide a library for the PAC1921 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for PAC1921 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pac1921_cfg_setup ( pac1921_cfg_t *cfg ); 
 
- Initialization function.
> PAC1921_RETVAL pac1921_init ( pac1921_t *ctx, pac1921_cfg_t *cfg );

- Click Default Configuration function.
> void pac1921_default_cfg ( pac1921_t *ctx );


#### Example key functions :

- This function writes data to the specified register address/es and saves the 
  state of the register/s so it doesn't write the same value/s twice.
> void pac1921_write_to_reg ( pac1921_t *ctx, uint8_t reg_addr, uint8_t *write_data, uint8_t len );
 
- This function gathers voltage/power data from the PAC1921 chip and, depending
  on the measurement mode, converts those raw values into a more suitable form.
> float pac1921_get_measured_data ( pac1921_t *ctx, uint8_t measurement_mode, uint8_t sample_num );

- This function sets the digital output on the interrupt pin.
> void pac1921_set_int_pin ( pac1921_t *ctx, uint8_t output );

## Examples Description

> This example showcases how to measure voltage, current or power (load) data using the 
  PAC1921 chip. Required modules are first initialized and after used to read and
  display the measured data. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. Default settings
  are written to three control/configuration registers in the default_cfg(...) function. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    pac1921_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pac1921_cfg_setup( &cfg );
    PAC1921_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pac1921_init( &pac1921, &cfg );
    Delay_ms( 100 );
    pac1921_default_cfg( &pac1921 );
    Delay_ms( 100 );
}
  
```

### Application Task

> This function reads and displays voltage, current or power data from the chip, depending
  on the specified measurement mode and sample count. It does so every half a second. 

```c

void application_task ( )
{
    float read_data;

    read_data = pac1921_get_measured_data( &pac1921, PAC1921_MEASUREMENT_MODE_V_BUS_FREE_RUN,
                                                     PAC1921_SAMPLE_RATE_512 );

    if ( pac1921.aux.measurement_mode_old == PAC1921_MEASUREMENT_MODE_V_POWER_FREE_RUN )
    {
        log_printf( &logger, " * Power: %.2f W * \r\n", read_data );
    }
    else
    {
        log_printf( &logger, " * Voltage: %.2f mV * \r\n", read_data );
    }

    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1921

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
