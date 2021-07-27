\mainpage Main Page
 
---
# VREG 2 click

VREG 2 click is a voltage regulator click, with outstanding performances. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/vreg2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/vreg-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : PWM type


# Software Support

We provide a library for the Vreg2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Vreg2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void vreg2_cfg_setup ( vreg2_cfg_t *cfg ); 
 
- Initialization function.
> VREG2_RETVAL vreg2_init ( vreg2_t *ctx, vreg2_cfg_t *cfg );

- Click Default Configuration function.
> void vreg2_default_cfg ( vreg2_t *ctx );


#### Example key functions :

- This function starts PWM module.
> void vreg2_pwm_start ( vreg2_t *ctx );
 
- This function stops PWM module.
> void vreg2_pwm_stop ( vreg2_t *ctx );

- This function sets the PWM duty cycle.
> void vreg2_set_duty_cycle ( vreg2_t *ctx, pwm_data_t duty_cycle );

## Examples Description

> This application enables voltage regulation.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the GPIO driver and configures the PWM 
> peripheral for controlling VREG2 voltage output.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    vreg2_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.rx_pin = (0x27) ; log_cfg.tx_pin = (0x26) ; log_cfg.baud = 9600; log_cfg.level = LOG_LEVEL_DEBUG; ;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    vreg2_cfg_setup( &cfg );
    cfg.pwm = (0x3C) ; cfg.an = (0x03) ;
    vreg2_init( &vreg2, &cfg );

    vreg2_set_duty_cycle( &vreg2, duty_cycle );
    vreg2_pwm_start( &vreg2 );
}
  
```

### Application Task

> Based on the data received from the uart the voltage output will be increased or decreased.

```c

void application_task ( void )
{
    //  Task implementation.

    switch ( ctrl_flag )
    {
        case 0:
        {
            duty_cycle = (uint32_t)vreg2.pwm_period  * 20 / 100;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );
            ctrl_pre_flag = ctrl_flag;
            ctrl_flag = 1;
            break;
        }

        case 1:
        {
            duty_cycle = (uint32_t)vreg2.pwm_period * 50 / 100;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );

            if ( ctrl_pre_flag == 0 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 2;
            }
            else if ( ctrl_pre_flag == 2 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 0;
            }
            break;
        }
        case 2:
        {
            duty_cycle = (uint32_t)vreg2.pwm_period  * 70 / 100;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );

            if ( ctrl_pre_flag == 1 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 3;
            }
            else if ( ctrl_pre_flag == 3 )
            {
                ctrl_pre_flag = ctrl_flag;
                ctrl_flag = 1;
            }
            break;
        }
        case 3:
        {
            duty_cycle = (uint32_t)vreg2.pwm_period * 95 / 100;
            log_printf( &logger, "Volatage set to : %d %%\r\n", duty_cycle );
            ctrl_pre_flag = ctrl_flag;
            ctrl_flag = 2;
            break;

        }
        default:
        {
            log_printf( &logger, "Something broke\r\n");
        }
    }

    vreg2_set_duty_cycle( &vreg2, duty_cycle );
    Delay_ms( 1500 );
    Delay_100ms();
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Vreg2

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
