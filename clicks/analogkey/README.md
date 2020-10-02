\mainpage Main Page
 
 

---
# Analog Key click

Analog Key Click is an analog keyboard on a Click board�. It contains six 
tactile pushbuttons, used to select one of six different voltage levels.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/analogkey_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/analog-key-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the AnalogKey Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AnalogKey Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void analogkey_cfg_setup ( analogkey_cfg_t *cfg ); 
 
- Initialization function.
> ANALOGKEY_RETVAL analogkey_init ( analogkey_t *ctx, analogkey_cfg_t *cfg );

#### Example key functions :

- This function returns which button is pressed.
> uint8_t analogkey_get_key ( analogkey_t* ctx, uint16_t adc_value );
 
- This function sets the resolution.
> void analogkey_set_resolution ( analogkey_t* ctx, uint8_t resolution );

## Examples Description

> This example logs which button is pressed.


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    analogkey_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    analogkey_cfg_setup( &cfg );
    ANALOGKEY_MAP_MIKROBUS( cfg, MIKROBUS_1 );

    analogkey_set_resolution( &analogkey, ANALOGKEY_ADC_RESOLUTION_12bit );
    
    analogkey_init( &analogkey, &cfg );
    Delay_ms( 100 );

    log_printf(&logger, " Press the button :D\r\n ");

}
  
```

### Application Task

> Reads ADC value and detects which button is pressed based on that value.

```c

void application_task ( void )
{
    uint16_t adc_value;
    uint8_t is_key;
    uint8_t cnt;
    uint16_t sum_value = 0;
    
    for ( cnt = 0; cnt < 5; cnt++ )
    {
        adc_value = analogkey_generic_read( &analogkey );
        sum_value += adc_value;
        Delay_ms( 10 );
    }
    adc_value = sum_value / 5;
    is_key = analogkey_get_key( &analogkey ,adc_value );

    if ( is_key != ANALOGKEY_NO_TOUCH )
    {
        log_printf( &logger, "Pressed the button: %d\r\n", is_key );
    }
    Delay_ms( 300 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogKey

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
