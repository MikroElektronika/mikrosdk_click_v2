\mainpage Main Page
 
 

---
# Angle 3 click

Angle 3 click carries the AK7451, a magnetic rotational angle sensor.
The click is designed to run on a 5V power supply.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/angle3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/angle-3-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Angle3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Angle3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void angle3_cfg_setup ( angle3_cfg_t *cfg ); 
 
- Initialization function.
> ANGLE3_RETVAL angle3_init ( angle3_t *ctx, angle3_cfg_t *cfg );



#### Example key functions :

- Writes given data to given address.
> void angle3_write_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg, uint16_t write_data );
 
- Reads data from given address.
> uint16_t angle3_read_data ( angle3_t* ctx, uint8_t opcode, uint8_t reg );

- Function reads the latest angle output data.
> uint16_t angle3_read_angle_data( angle3_t* ctx );

## Examples Description

> This example reads data from the sensor, calculates and logs the result.

**The demo application is composed of two sections :**

### Application Init 

> Driver initialization, sets sensor to normal mode and starts writting to log.

```c

void application_init ( void )
{
	log_cfg_t log_cfg;
    angle3_cfg_t angle3_cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    angle3_cfg_setup( &angle3_cfg );
    ANGLE3_MAP_MIKROBUS( angle3_cfg, MIKROBUS_1 );
    angle3_init( &angle3, &angle3_cfg );
	angle3_default_cfg( &angle3 );

}
  
```

### Application Task

> Angle 3 Click communicates with registers via SPI, reads data from the angle
> sensor, calculates it to degrees and writes it to the terminal.


```c

void application_task ( void )
{
	angle_value_old = 0;

	if ( angle3_read_error( &angle3 ) )
	{
		angle_value = angle3_read_angle_data( &angle3 );

		if ( angle_value_old != angle_value )
		{
			angle_data_degrees = angle3_calculate_degrees( &angle3, angle_value );

			log_printf( &logger, "Angle : %d deg \r\n", angle_data_degrees );

			angle_value_old = angle_value;

			Delay_ms( 1000 );
		}
	}
	else
	{
		log_printf( &logger, "Magnetic Field Too Weak\r\n" );

		Delay_ms( 1000 );
	}
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle3

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
