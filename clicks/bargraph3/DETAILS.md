
---
# BARGRAPH 3 click

< BarGraph 3 click is equipped with a five-segment LED bar graph display, notable for its strong and uniform illumination of the segments. Each segment consists of three internal LEDs with a common cathode, while the anodes of all LEDs are connected in a single point. >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bargraph3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/bargraph-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the BarGraph3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BarGraph3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void bargraph3_cfg_setup ( bargraph3_cfg_t *cfg ); 
 
- Initialization function.
> BARGRAPH3_RETVAL bargraph3_init ( bargraph3_t *ctx, bargraph3_cfg_t *cfg );



#### Example key functions :

- This function control the displey.
> void bargraph3_display ( bargraph3_t *ctx, uint8_t ctrl, uint8_t dir, uint8_t counter);
 
- This function set PWM.
> void bargraph3_set_pwm ( bargraph3_t *ctx, uint8_t state );

- Functions for enable the chip.
> void bargraph3_enable ( bargraph3_t *ctx, uint8_t state );

## Examples Description

> Used to create various types of VU meters, status indicators, different types of counters and similar devices.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init, enable device and set PWM.

```c

void application_init ( void )
{
 log_cfg_t log_cfg;
    bargraph3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    bargraph3_cfg_setup( &cfg );
    BARGRAPH3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bargraph3_init( &bargraph3, &cfg );
}
  
```

### Application Task

> Counter passes through the loop and logs the value of the counter on the bargraph display.

```c

void application_task ( void )
{
    uint8_t bargraph_cnt;
    
    for (bargraph_cnt = 0; bargraph_cnt <= 5; bargraph_cnt++)
    {
        bargraph3_display(  &bargraph3, BARGRAPH3_INCREASE_LED,  BARGRAPH3_DIRECTION_BOTTOM_TO_TOP, bargraph_cnt);
        Delay_ms( 1000 );
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BarGraph3

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
