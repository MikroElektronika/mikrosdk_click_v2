
# LED driver 6 click

LED driver 6 Click is a high brightness LED or LED strip driver, designed to be used in tunable Smart Connected Lighting (SCL) applications. It is based on the AL1781, a single-channel PWM dimmable linear LED driver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/leddriver6_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/led-driver-6-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Leddriver6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Leddriver6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void leddriver6_cfg_setup ( leddriver6_cfg_t *cfg ); 
 
- Initialization function.
> LEDDRIVER6_RETVAL leddriver6_init ( leddriver6_t *ctx, leddriver6_cfg_t *cfg );


#### Example key functions :

- Generic sets PWM duty cycle.
> void leddriver6_set_duty_cycle ( leddriver6_t *ctx, pwm_data_t duty_cycle );
 
- Stop PWM module.
> void leddriver6_pwm_stop ( leddriver6_t *ctx );

- Start PWM module.
> void leddriver6_pwm_start ( leddriver6_t *ctx );

## Examples Description
 
> This application designed to be used in tunable Smart Connected Lighting applications. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and pwm init for LED. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    leddriver6_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    leddriver6_cfg_setup( &cfg );
    LEDDRIVER6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    leddriver6_init( &leddriver6, &cfg );

    leddriver6_pwm_start( &leddriver6 );
}
  
```

### Application Task

> Waits for valid user input and executes functions based on set of valid commands. 

```c

void application_task ( void )
{
  uint8_t cnt;

  if ( duty_cycle > leddriver6.pwm_period )
  {
      duty_cycle = 100;
  }
  
  leddriver6_set_duty_cycle ( &leddriver6, duty_cycle );
  duty_cycle += 50;
  Delay_100ms( );
  
  increase( );
  Delay_10ms( );
  decrease( );
  Delay_10ms( );
  current_pg_voltage( );

  for( cnt = 0; cnt < 5; cnt++ )
  {
      increase( );
      Delay_10ms( );
  }
  for( cnt = 0; cnt < 3; cnt++ )
  {
      decrease( );
      Delay_10ms( );
  }
  current_pg_voltage( );

  Delay_1s( );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Leddriver6

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
