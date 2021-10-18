\mainpage Main Page
 
 

---
# Buck-Boost  click

Buck-Boost click™ features LTC3129-1, a buck-boost DC/DC conversion integrated circuit. The click supports a wide input voltage range and can output eight discrete regulated output voltage levels, selectable by the digital output voltage selection pins, ranging from 2.5V to 15V. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buckboost_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-boost-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the BuckBoost Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BuckBoost Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buckboost_cfg_setup ( buckboost_cfg_t *cfg ); 
 
- Initialization function.
> BUCKBOOST_RETVAL buckboost_init ( buckboost_t *ctx, buckboost_cfg_t *cfg );

- Click Default Configuration function.
> void buckboost_default_cfg ( buckboost_t *ctx );


#### Example key functions :

- This function set fixed frequency PWM operation mode of LTC3129-1 on Buck Boost Click by set PWM pin ( logic 1 ).
> void buckboost_set_mode_fixed_freq ( buckboost_t *ctx );
 
- This function enables automatic burst mode operation of LTC3129-1 on Buck Boost Click by clear PWM pin ( logic 0 ).
> void buckboost_enables_auto_burst_mode ( buckboost_t *ctx );

- This function set the output voltage of 2500 mV function.
> void buckboost_set_2500mv ( buckboost_t *ctx );

## Examples Description

> The demo application change output voltage from 2500 mV to 15000 mV every 5 seconds.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device and set default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    buckboost_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    buckboost_cfg_setup( &cfg );
    BUCKBOOST_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buckboost_init( &buckboost, &cfg );

    buckboost_default_cfg( &buckboost );
    log_printf(&logger, "--------------------------------\r\n");
    log_printf(&logger, "        Buck Boost Click        \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    Delay_ms( 100 );
}
  
```

### Application Task

> This is a example which demonstrates the use of Buck Boost Click board.
> Change output voltage from 2500 mV to 15000 mV every 5 seconds.
> All data logs write on usb uart for aproximetly every 5 sec.

```c

void application_task ( void )
{
    log_printf(&logger, " Set Output Voltage of  2500 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_2500mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  3300 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_3300mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  4100 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_4100mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  5000 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_5000mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  6900 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_6900mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  8200 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_8200mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  12000 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_12000mv( &buckboost );
    Delay_ms( 5000 );

    log_printf(&logger, " Set Output Voltage of  15000 mV \r\n");
    log_printf(&logger, "--------------------------------\r\n");
    buckboost_set_15000mv( &buckboost );
    Delay_ms( 5000 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BuckBoost

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
