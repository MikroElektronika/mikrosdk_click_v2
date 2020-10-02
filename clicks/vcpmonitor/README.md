\mainpage Main Page
 
---
# VCP monitor click

The VCP Monitor Click is add-on board power monitor system. This Click board™ is based on INA260AIPWR - precision digital current and power monitor with low-drift, integrated precision shunt resistor, from Texas Instruments. Therefore, using VCP Monitor Click, current, voltage and power can be monitored.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](https://www.mikroe.com/vcp-monitor-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the VCPmonitor Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for VCPmonitor Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vcpmonitor_cfg_setup ( vcpmonitor_cfg_t *cfg ); 
 
- Initialization function.
> VCPMONITOR_RETVAL vcpmonitor_init ( vcpmonitor_t *ctx, vcpmonitor_cfg_t *cfg );

- Click Default Configuration function.
> void vcpmonitor_default_cfg ( vcpmonitor_t *ctx );


#### Example key functions :

- This function reads current data in mA.
> float vcpmonitor_get_current ( vcpmonitor_t *ctx );
 
- This function reads power data in mW.
> float vcpmonitor_get_power ( vcpmonitor_t *ctx );

- This function reads voltage data in mV.
> float vcpmonitor_get_voltage ( vcpmonitor_t *ctx );

## Examples Description

> The VCP Monitor Click is add-on board power monitor system. This Click board is 
> based on precision digital current and power monitor with low-drift, integrated 
> precision shunt resistor. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, check device ID 
> and manufacture ID, start default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    vcpmonitor_cfg_setup( &cfg );
    VCPMONITOR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor_init( &vcpmonitor, &cfg );
    
    vcpmonitor_get_id_value( &vcpmonitor, &manufacture_id, &did_id );
    log_printf( &logger, ">> Manufacture ID: 0x%d\r\n", manufacture_id );
    log_printf( &logger, ">> Device ID: 0x%d\r\n", did_id );
    
    vcpmonitor_default_cfg(&vcpmonitor );
    log_printf( &logger, ">> Default config...\r\n" );
    Delay_ms( 500 );
}
  
```

### Application Task

> Reads Current, Voltage and Power data. 
> This data logs to USB UART every 1500ms.

```c

void application_task ( void )
{
    float current_data;
    float voltage_data;
    float power_data;
    
    current_data = vcpmonitor_get_current( &vcpmonitor );
   
    log_printf( &logger, ">> Current data: %.2f\r\n", current_data );
    log_printf( &logger, " mA\r\n" );
     
    voltage_data = vcpmonitor_get_voltage( &vcpmonitor );
    log_printf( &logger, ">> Voltage data:%.2f\r\n ", voltage_data );
    log_printf( &logger, " mV\r\n" );
    
    power_data = vcpmonitor_get_power( &vcpmonitor );
    log_printf( &logger, ">> Power data: %.2f\r\n", power_data );
    log_printf( &logger, " mW\r\n" );
    
    log_printf( &logger, " ------------------------------- \r\n" );
    Delay_ms( 1500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.VCPmonitor

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
