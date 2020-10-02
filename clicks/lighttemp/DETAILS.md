
---
# Light Temp click

Light Temp Click is a dual-channel LED driver, designed to be used in tunable Smart Connected Lighting (SCL) applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lighttemp_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/light-temp-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the LightTemp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LightTemp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lighttemp_cfg_setup ( lighttemp_cfg_t *cfg ); 
 
- Initialization function.
> LIGHTTEMP_RETVAL lighttemp_init ( lighttemp_t *ctx, lighttemp_cfg_t *cfg );

#### Example key functions :

- Get INT pin state
> uint8_t lighttemp_get_interrupt_state ( lighttemp_t *ctx );
 
- Get voltage
> uint16_t lighttemp_get_pg_voltage ( lighttemp_t *ctx );

- Start PW2 module.
> void lighttemp_cs_set_state( lighttemp_t *ctx, uint8_t state );

## Examples Description

> This application controls light intensity of LEDs.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and pwm init for all LED's

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lighttemp_cfg_t cfg;
    uint16_t frequency = 20000;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lighttemp_cfg_setup( &cfg );
    LIGHTTEMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lighttemp_init( &lighttemp, &cfg );

    lighttemp_pwm_start( &lighttemp );
    lighttemp_cs_set_state( &lighttemp, 0 );
}
  
```

### Application Task

> On first LED is a pwm module, which increases/decreases light intensity, 
> and on second LED turn ON/OFF light. 

```c

void application_task ( void )
{
    uint16_t pg_volt;
    uint8_t i;  
    
    pg_volt = lighttemp_get_pg_voltage( &lighttemp );
    log_printf( &logger, ">>> PG Voltage: %ld mV \r\n", pg_volt );

    log_printf( &logger, ">>> LED 1 Increase \r\n" );
    
    for ( i = 0; i < 72; i++ )
    {
        duty_cycle += 50;
        lighttemp_set_duty_cycle( &lighttemp, duty_cycle );
        Delay_ms( 100 );
    }
    
    Delay_ms( 1000 );
    
    log_printf( &logger, ">>> LED 1 Decrease \r\n" );
    
    
    for ( i = 0; i < 72; i++ )
    {
        duty_cycle -= 50;
        lighttemp_set_duty_cycle( &lighttemp, duty_cycle );
        Delay_ms( 100 ); 
    }
    
    Delay_ms( 1000 );
     
    log_printf( &logger, ">>> LED 2 -> ON \r\n" );
    lighttemp_cs_set_state( &lighttemp, 1 );
    Delay_ms( 1000 );
    log_printf( &logger, ">>> LED 2 -> OFF \r\n" );
    lighttemp_cs_set_state( &lighttemp, 0 );
    Delay_ms( 1000 );  
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LightTemp

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
