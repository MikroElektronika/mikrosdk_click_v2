\mainpage Main Page

---
# VCP Monitor 3 click

VCP Monitor 3 Click is a high precision Voltage, Current and Power measurement Click board™ with an input capable of taking up to 15V. It features the LTC2947, from Analog Devices, a high precision power and energy monitor with an internal sense resistor supporting up to ±30A.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/vcp-monitor-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the VcpMonitor3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for VcpMonitor3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vcpmonitor3_cfg_setup ( vcpmonitor3_cfg_t *cfg ); 
 
- Initialization function.
> VCPMONITOR3_RETVAL vcpmonitor3_init ( vcpmonitor3_t *ctx, vcpmonitor3_cfg_t *cfg );

- Click Default Configuration function.
> void vcpmonitor3_default_cfg ( vcpmonitor3_t *ctx );


#### Example key functions :

- Function is used to get current in Amperes.
> float vcpmonitor3_read_i ( vcpmonitor3_t *ctx );
 
- Function is used to get power in Watts.
> float vcpmonitor3_read_p ( vcpmonitor3_t *ctx );

- Function is used to get voltage in Volts.
> float vcpmonitor3_read_v ( vcpmonitor3_t *ctx );

## Examples Description

> VCP Monitor 3 Click show it's full usage by reading current, voltage, power, die temperature 
> and voltage at DVCC using SPI or I2C communication protocol.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes SPI or I2C driver and sets up the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vcpmonitor3_cfg_setup( &cfg );
    VCPMONITOR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor3_init( &vcpmonitor3, &cfg );

    vcpmonitor3_default_cfg( &vcpmonitor3 );
}
  
```

### Application Task

> This example shows capabilities of VCP Monitor 3 Click board
> by reading current, voltage, power, die temperature and 
> voltage at DVCC and displaying the results via USART terminal.

```c

void application_task ( void )
{
    cur_data = vcpmonitor3_read_i( &vcpmonitor3 );
    log_printf( &logger, "Current : %.2f A\r\n", cur_data );

    pow_data = vcpmonitor3_read_p( &vcpmonitor3 );
    log_printf( &logger, "Power : %.2f W\r\n", pow_data );

    volt_data = vcpmonitor3_read_v( &vcpmonitor3 );
    log_printf( &logger, "Voltage : %.2f V\r\n", volt_data );

    die_temp = vcpmonitor3_read_temp( &vcpmonitor3 );
    log_printf( &logger, "Die Temperature : %.2f %s\r\n", die_temp, deg_cel );

    volt_vcc = vcpmonitor3_read_vcc( &vcpmonitor3 );
    log_printf( &logger, "Voltage at DVCC : %.2f V\r\n", volt_vcc );

    log_printf( &logger, " ------------------------------- \r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.VcpMonitor3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
