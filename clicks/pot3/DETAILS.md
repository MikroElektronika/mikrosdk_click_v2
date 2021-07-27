
---
# Pot 3 click

POT 3 Click is a Click board� with the accurate selectable reference voltage 
output. By employing a high-quality 11mm, metal shaft potentiometer,
this Click board can provide very accurate voltage output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pot3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pot-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Pot3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pot3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pot3_cfg_setup ( pot3_cfg_t *cfg ); 
 
- Initialization function.
> POT3_RETVAL pot3_init ( pot3_t *ctx, pot3_cfg_t *cfg );



#### Example key functions :

- This function reads the result of AD conversion.
> uint16_t pot3_read_adc ( pot3_t* ctx );
 
- This function reads the averaged result of AD conversions.
> uint16_t pot3_read_avg_adc ( pot3_t* ctx, uint16_t n_samples );

-  This function returns VOUT value calculated to millivolts.
> uint16_t pot3_get_vout ( pot3_t* ctx, uint8_t vref_sel, uint16_t n_samples );

## Examples Description

> This example gets voltage, calculates it to millivolts and then logs it to the terminal. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and sets required pins.


```c

void application_init ( void )
{
	log_cfg_t log_cfg;
    pot3_cfg_t pot3_cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    pot3_cfg_setup( &pot3_cfg );
    POT3_MAP_MIKROBUS( pot3_cfg, MIKROBUS_1 );
    pot3_init( &pot3, &pot3_cfg );
}
  
```

### Application Task

>
> Reads VOUT value calculated to millivolts with 2000 conversions
>  included in one measurement cycle.
> 

```c

void application_task ( void )
{
	voltage_mv = pot3_get_vout( &pot3, POT3_VREF_2V, 2000);
	log_printf( &logger, " VOUT : %d mV\r\n", voltage_mv );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pot3

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
