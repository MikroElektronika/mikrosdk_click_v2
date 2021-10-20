 
---
# Ambient 5 click

Ambient 5 click can sense the intensity of the ambient light, providing 
measurement data in a digital format, over the I2C interface. It utilizes 
the VEML6030, a miniature ambient light sensor (ALS) which occupies 
only 2x2 mm of space.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient5_cfg_setup ( ambient5_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT5_RETVAL ambient5_init ( ambient5_t *ctx, ambient5_cfg_t *cfg );

- Click Default Configuration function.
> void ambient5_default_cfg ( ambient5_t *ctx );


#### Example key functions :

- This function writes the register value to the desired register.
> void ambient5_set_register ( ambient5_t *ctx, uint8_t reg_addr, uint16_t reg_value );
 
- This function reads data from the desired register.
> uint16_t ambient5_get_register ( ambient5_t *ctx, uint8_t reg );

- This function calculates resolution of output data in "high resolution" and "white channel" registers.
> float ambient5_get_resolution ( ambient5_t* ctx );

**The demo application is composed of two sections :**

### Application Init 

> Initializes i2c driver, powers the device and calculates refresh time

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient5_cfg_t ambient_cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ambient5_cfg_setup( &ambient_cfg );
    AMBIENT5_MAP_MIKROBUS( ambient_cfg, MIKROBUS_1 );
    ambient5_init( &ambient5, &ambient_cfg );
    ambient5_default_cfg( &ambient5 );

	log_printf( &logger, "App init done\r\n" );
}
  
```

### Application Task

> Logs high resolution ambient light data after a period of time.

```c

void application_task ( void )
{
    r_time = ambient5_get_refresh_time( &ambient5 );
    
    for (i = 0; i < r_time; i++)
	{
		Delay_ms(1);
	}

	high_res_light_level = ambient5_get_high_resolution_light_level( &ambient5 );

	log_printf( &logger, " Ambient Light Level : %.2f lx\r\n", high_res_light_level );
	    
    Delay_ms( 500 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient5

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
