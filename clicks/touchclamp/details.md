

---
# TouchClamp click

TouchClamp click is a mikroBUS™ add-on board with NXP’s MPR121 proximity capacitive touch sensor controller. It has seven plated holes for clamps which can be used to connect any – literally any – conductive object in order to use it as an input button to send an interrupt to the target board MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchclamp_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/touchclamp-click>)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the TouchClamp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TouchClamp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void touchclamp_cfg_setup ( touchclamp_cfg_t *cfg ); 
 
- Initialization function.
> TOUCHCLAMP_RETVAL touchclamp_init ( touchclamp_t *ctx, touchclamp_cfg_t *cfg );

- Click Default Configuration function.
> void touchclamp_default_cfg ( touchclamp_t *ctx );


#### Example key functions :

- Get touch data function.
> uint16_t touchclamp_get_touch_data ( touchclamp_t *ctx );

## Examples Description

> 
> This demo-app shows the touch position using TouchClamp click.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> Setting the click in the default configuration.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchclamp_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, " Application Init \r\n" );

    //  Click initialization.

    touchclamp_cfg_setup( &cfg );
    TOUCHCLAMP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchclamp_init( &touchclamp, &cfg );
    Delay_ms( 100 );
    
    touchclamp_soft_reset( &touchclamp );
    Delay_ms( 100 );
    
    touchclamp_default_cfg( &touchclamp );
    Delay_ms( 100 );
    
    touch_data_old = TOUCHCLAMP_NO_TOUCH;
    
    log_printf( &logger, "-------------------\r\n" );
    log_printf( &logger, " Touch Clamp Click \r\n" );
    log_printf( &logger, "-------------------\r\n" );
}
  
```

### Application Task

>
> Detect and dispay touch position when the click is triggered.
> 

```c

void application_task ( void )
{
    touch_data = touchclamp_get_touch_data( &touchclamp );
    
    if ( touch_data_old != touch_data )
    {
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_H )
            log_printf( &logger, "  - - - - - - - H\r\n" );
            
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_G )
            log_printf( &logger, "  - - - - - - G -\r\n" );
            
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_F )
            log_printf( &logger, "  - - - - - F - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_E )                       
            log_printf( &logger, "  - - - - E - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_D )                       
            log_printf( &logger, "  - - - D - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_C )                       
            log_printf( &logger, "  - - C - - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_B )                       
            log_printf( &logger, "  - B - - - - - -\r\n" );
                                                       
        if ( touch_data == TOUCHCLAMP_TOUCH_POSITION_A )                       
            log_printf( &logger, "  A - - - - - - -\r\n" );
      
        touch_data_old = touch_data;
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchClamp

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
