
---
# DC Motor 9 click

DC Motor 9 Click is a brushed DC motor driver with the current limiting and current sensing. It is based on the DRV8871, an integrated H-Bridge driver IC, optimized for motor driving applications. It can be operated by two logic signals, allowing to drive the connected motor in two different ways: it can use fixed logic levels for the direction control, or it can be controlled by a PWM signal, offering an additional speed control option. The DRV8871 also contains a set of protection features, offering a very high level of reliability. Besides driving capabilities, DC Motor 9 click can also sense current consumption at its output.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-9-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the DcMotor9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DcMotor9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dcmotor9_cfg_setup ( dcmotor9_cfg_t *cfg ); 
 
- Initialization function.
> DCMOTOR9_RETVAL dcmotor9_init ( dcmotor9_t *ctx, dcmotor9_cfg_t *cfg );


#### Example key functions :

- This function read ADC data.
> dcmotor9_data_t dcmotor9_generic_read ( dcmotor9_t *ctx );
 
- This function starts PWM module.
> void dcmotor9_pwm_start ( dcmotor9_t *ctx );

- This function sets the PWM duty cycle.
> void dcmotor9_set_duty_cycle ( dcmotor9_t *ctx, float duty_cycle );

## Examples Description

> DC Motor 9 Click is a brushed DC motor driver with the current limiting and current sensing. It can
> be operated by two logic signals, allowing to drive the connected motor in two different ways: 
> it can use fixed logic levels for the direction control, or it can be controlled by a PWM signal, 
> offering an additional speed control option. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes LOG, PWM pin as output, RST pin as input and CS pin as output
> and nitializes GPIO driver and ADC and PWM functionalities.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dcmotor9_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    dcmotor9_cfg_setup( &cfg );
    DCMOTOR9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dcmotor9_init( &dcmotor9, &cfg );

    dcmotor9_pwm_start( &dcmotor9 );

    duty_cycle = 1;
    dcmotor9_set_duty_cycle ( &dcmotor9, duty_cycle );
}
  
```

### Application Task

> Reads ADC value and print it via UART terminal.

```c

void application_task ( void )
{
    adc_value = dcmotor9_generic_read( &dcmotor9 );
    log_printf( &logger, "%d \r\n", adc_value );
    Delay_ms( 750 );
}
  

```

## Note

> Optional : call - dcmotor9_get_volt_amper( adc_ref ) - function to get value of voltage and current on shunt
> float adc_ref - is ADC value read from AN pin while no load is connected to device

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DcMotor9

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
