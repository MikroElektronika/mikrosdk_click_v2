\mainpage Main Page
 
---
# Heater  click

Heater Click is designed with intention of PCB heater concept testing and useful tool for heating complete casing where staying in specified temperature range is crucial. Exact PCB temperature can be set and controlled using TMP235 on board temperature sensor from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/heater_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/heater-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the heater Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for heater Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void heater_cfg_setup ( heater_cfg_t *cfg ); 
 
- Initialization function.
> HEATER_RETVAL heater_init ( heater_t *ctx, heater_cfg_t *cfg );

- Click Default Configuration function.
> void heater_default_cfg ( heater_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> uint16_t heater_read_data ( heater_t *ctx )

- Read data in mV
> float heater_read_mv ( heater_t *ctx )

- Read data in C
> float heater_read_temp ( heater_t *ctx )


## Examples Description

> 
>  The devices resolution depends on settings applied.
>  User should consult the datasheet and choose resolution value 
>  that corresponds to the settings applied.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initialization of PWM module and start heating up
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    heater_cfg_t cfg;
    heater_config_t cfg1;

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
    log_info( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    heater_cfg_setup( &cfg, &cfg1 );
    HEATER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    heater_init( &heater, &cfg, &cfg1 );
    
    frequency = 500;
    
    heater_set_duty_cycle( &heater, heater.pwm_period );
    status_dev = HEATER_HEATING;
    
    log_printf( &logger, " ***** APP INIT ***** \r\n" );
    Delay_ms ( 500 );

}
  
```

### Application Task

>
> Durning the task device is heating up to 50 degree C and then
> cooling down to 40 degree C
 

```c

void application_task ( void )
{
    temp_read = heater_read_temp( &heater );
    
    if ( ( temp_read > HOT_TEMP ) && ( status_dev == HEATER_WAITING ) )
    {
    status_dev = HEATER_COOLING;
    }
    else if ( ( temp_read < COOL_TEMP ) && ( status_dev == HEATER_WAITING ) )
    {
    status_dev = HEATER_HEATING;
    }

    if ( status_dev == HEATER_HEATING )
    {
    heater_pwm_start ( &heater );
    heater_set_led1_status( &heater, HEATER_LED_ON );
    heater_set_led2_status( &heater, HEATER_LED_OFF );
    status_dev = HEATER_WAITING;
    }
    else if ( status_dev == HEATER_COOLING )
    {
    heater_pwm_stop ( &heater );
    heater_set_led1_status( &heater,HEATER_LED_OFF );
    heater_set_led2_status( &heater,HEATER_LED_ON );
    status_dev = HEATER_WAITING;
    }

    log_printf( &logger,  " - Temperature: %.2f %s\r\n", temp_read, log_degree );
    
    log_printf( &logger, "***************\r\n" );

    Delay_ms ( 1000 );
}


```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Heater

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
