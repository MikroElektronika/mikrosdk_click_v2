\mainpage Main Page
 
---
# VCP Monitor 2 click

VCP Monitor 2 Click is a three-channel, high-side current and bus voltage monitor with alert indication function ensuring the intended application works within desired operating conditions. Featured chip INA3221-Q1, by Texas Instruments, monitors both shunt voltage drops and bus supply voltages, in addition to having programmable conversion times and averaging modes for these signals.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](https://www.mikroe.com/vcp-monitor-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Vcpmonitor2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Vcpmonitor2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vcpmonitor2_cfg_setup ( vcpmonitor2_cfg_t *cfg ); 
 
- Initialization function.
> VCPMONITOR2_RETVAL vcpmonitor2_init ( vcpmonitor2_t *ctx, vcpmonitor2_cfg_t *cfg );

#### Example key functions :

- Get Manufacture ID.
> uint16_t vcpmonitor2_get_manifacture_id ( vcpmonitor2_t *ctx );
 
- Get DIE ID.
> uint16_t vcpmonitor2_get_die_id ( vcpmonitor2_t *ctx );

- Get BUS voltage in mV.
> float vcpmonitor2_get_bus_voltage ( vcpmonitor2_t *ctx, uint8_t channel );

## Examples Description

> VCP Monitor 2 Click is a three-channel, high-side current and bus voltage monitor with alert indication 
> function ensuring the intended application works within desired operating conditions.

**The demo application is composed of two sections :**

### Application Init 

> Initiaization driver init, device configuration for measurement, alert status reset and configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vcpmonitor2_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    vcpmonitor2_cfg_setup( &cfg );
    VCPMONITOR2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    vcpmonitor2_init( &vcpmonitor2, &cfg );

    check_id = vcpmonitor2_get_manifacture_id( &vcpmonitor2 );
    log_printf( &logger, ">> Manufacture ID: 0x %d\r\n", check_id );

    vcpmonitor2_default_cfg( &vcpmonitor2 );
}
  
```

### Application Task

> Display Voltage on the BUS and Shunt, current and power data. 

```c

void application_task ( void )
{
    log_printf( &logger, ">> CHANNEL 1 <<\r\n" );
    display_channel_data( VCPMONITOR2_CHANNEL_1 );

    log_printf( &logger, ">> CHANNEL 2 <<\r\n" );
    display_channel_data( VCPMONITOR2_CHANNEL_2 );

    log_printf( &logger, ">> CHANNEL 3 <<\r\n" );
    display_channel_data( VCPMONITOR2_CHANNEL_3 );

    display_alert_status( );
    
    Delay_ms( 4000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Vcpmonitor2

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
