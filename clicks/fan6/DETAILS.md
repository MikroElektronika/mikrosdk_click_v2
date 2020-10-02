
---
# Fan 6  click

The Fan 6 click is a Click board™ which features EMC2103, an SMBus compliant fan controller with up to up to 3 external and 1 internal temperature channels. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/fan-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fan6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fan6_cfg_setup ( fan6_cfg_t *cfg ); 
 
- Initialization function.
> FAN6_RETVAL fan6_init ( fan6_t *ctx, fan6_cfg_t *cfg );

- Click Default Configuration function.
> void fan6_default_cfg ( fan6_t *ctx );


#### Example key functions :

- This function reads 256 bytes from EEPROM.
> void fan6_read_eeprom ( fan6_t *ctx, uint8_t *data_out );
 
- This function sets Fan on PWM mode and determines Fan speed (PWM duty).
> void fan6_set_pwm_mode ( fan6_t *ctx, const uint8_t pwm_duty );

- This function reads current tachometer value and calculates that value in rpm.
> uint32_t fan6_read_tachometer ( fan6_t *ctx );

## Examples Description

> This demo application reads tachometer value which is calculated as rpm value, and reads
> temperature of external diode in celsius value.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    fan6_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    fan6_cfg_setup( &cfg );
    FAN6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fan6_init( &fan6, &cfg );

    fan6_default_cfg( &fan6 );
    tachometer = 0;
}
  
```

### Application Task

> Reads tachometer value which is calculated as rpm value, and reads
> temperature of external diode in celsius value. All this results logs on USB UART.
> Repeats operation every 500 ms.>
 

```c

void application_task ( void )
{
    tachometer = fan6_read_tachometer( &fan6 );
    log_printf( &logger, "Tachometer value is: %d rpm \r\n", tachometer );

    temp_diode = fan6_get_temperature( &fan6, FAN6_EXTDIODE1_TEMP_READ_REG );
    log_printf( &logger, "Temperature of DIODE is: %f - Cels \r\n", temp_diode );

    Delay_ms( 500 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan6

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