\mainpage Main Page
 
 

---
# Opto Encoder click

Opto Encoder click is a linear incremental optical sensor/encoder click, which can be used for the movement or rotation encoding.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/optoencoder_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/opto-encoder-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the OptoEncoder Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OptoEncoder Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void optoencoder_cfg_setup ( optoencoder_cfg_t *cfg ); 
 
- Initialization function.
> OPTOENCODER_RETVAL optoencoder_init ( optoencoder_t *ctx, optoencoder_cfg_t *cfg );

#### Example key functions :

- Function for reading O1 state
> uint8_t optoencoder_getO1 ( optoencoder_t *ctx );
 
- Initialization function
> void optoencoder_init_dev ( optoencoder_t *ctx );

- Function for reading the position of the encoder
> int16_t optoencoder_get_position ( optoencoder_t *ctx );

## Examples Description

> This application is used to encode motion or rotation.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and opto encoder.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    optoencoder_cfg_setup( &cfg );
    OPTOENCODER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder_init( &optoencoder, &cfg );

    optoencoder_init_dev( &optoencoder );
}
  
```

### Application Task

> Depending on the direction of the movement it increments/decrements the step counter.

```c

void application_task ( )
{
    int16_t new_step;
    new_step = optoencoder_get_position( &optoencoder );
    if ( old_step != new_step)
    {
        log_printf( &logger, "Step: %d \r\n", new_step );
        old_step = new_step;
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder

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
