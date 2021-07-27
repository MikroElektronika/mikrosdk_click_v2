\mainpage Main Page
 
---
# H Bridge 3 click

H-Bridge 3 Click is designed for the control of small DC motors and inductive loads, it features TLE9201SG a general purpose 6A H-Bridge perfectly suited for industrial and automotive applications. This IC meets the harsh automotive environmental conditions and it is qualified in accordance with the AEC-Q100 standard, also has set of features such as the short circuit and over-temperature protection, under-voltage protection, detailed SPI diagnosis or simple error flag and fully 3.3/5.5V compatible logic inputs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hbridge3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/h-bridge-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the HBridge3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HBridge3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hbridge3_cfg_setup ( hbridge3_cfg_t *cfg ); 
 
- Initialization function.
> HBRIDGE3_RETVAL hbridge3_init ( hbridge3_t *ctx, hbridge3_cfg_t *cfg );

- Click Default Configuration function.
> void hbridge3_default_cfg ( hbridge3_t *ctx );


#### Example key functions :

- This function sets the PWM duty cycle.
> void hbridge3_set_duty_cycle ( hbridge3_t *ctx, pwm_data_t duty_cycle );
 
- This function sends SPI command and receives response to command sent
> uint8_t hbridge3_spi ( hbridge3_t *ctx, uint8_t spi_command );

- Generic SPI transfer, for sending and receiving packages.
> void hbridge3_generic_transfer ( hbridge3_t *ctx, spi_master_transfer_data_t *block );

## Examples Description

> H-bridge in general, allows the current to flow in one or another direction.
> This click is used for drive a H-Bridge motor by changing output states. 
> The outputs can be pulse width modulated at frequencies up to 20kHz by means of PWM/DIR control. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI and LOG modules, AN, RST, CS and PWM pins

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hbridge3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    hbridge3_cfg_setup( &cfg );
    HBRIDGE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hbridge3_init( &hbridge3, &cfg );

    Delay_ms( 500 );
    
    hbridge3_pwm_start( &hbridge3 );
}
  
```

### Application Task

>  Initializes SPI driver and PWM module, sets minimum PWM duty cycle and starts PWM

```c

void application_task ( void )
{
    log_printf( &logger, "------------------------------\r\n" );
    case_direction1( );
    Delay_ms( 20 );
    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
    
    for ( duty_cycle = 1; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
    
    log_printf( &logger, "------------------------------\r\n" );
    case_direction2( );
    Delay_ms( 20 );
    for ( duty_cycle = 0.1; duty_cycle < 1; duty_cycle += 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
    
    for ( duty_cycle = 1; duty_cycle > 0.09; duty_cycle -= 0.1 )
    {
        hbridge3_set_duty_cycle( &hbridge3, duty_cycle );
        log_printf( &logger, "> duty cycle : %.2f\r\n", duty_cycle );
        Delay_ms( 300 );
    }
}
  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HBridge3

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
