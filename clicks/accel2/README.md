\mainpage Main Page
 
---
# Accel 2 click

Accel 2 click carries ST’s LIS3DSH IC, a low-power factory-calibrated three-axis accelerometer which embeds a FIFO buffer and two programmable state machines.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-2-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel2_cfg_setup ( accel2_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL2_RETVAL accel2_init ( accel2_t *ctx, accel2_cfg_t *cfg );

- Generic write function.
> void accel2_generic_write ( accel2_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );


#### Example key functions :

- Check Accel 2 ID.
> uint8_t accel2_check_id ( accel2_t *ctx );
 
- Function read X axis.
> uint16_t accel2_read_xaxis ( accel2_t *ctx );

- Function read Y axis.
> uint16_t accel2_read_yaxis ( accel2_t *ctx );

## Examples Description

> This application is three-axis accelerometer which embeds.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device. Check sensor ID and initialize Accel 2 click.

```c

void application_init ( void )
{
   log_cfg_t log_cfg;
   accel2_cfg_t cfg;

   log_cfg.level = LOG_LEVEL_DEBUG;
   LOG_MAP_USB_UART( log_cfg );
   log_init( &logger, &log_cfg );
   log_info( &logger, "---- Application Init ----" );

   accel2_cfg_setup( &cfg );
   ACCEL2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
   accel2_init( &accel2, &cfg );
}
  
```

### Application Task

> This is a example which demonstrates the use of Accel 2 click board.
   Measured coordinates (X,Y,Z) are being sent to the UART where you can track their changes.

```c

void application_task ( void )
{
   int16_t value_x;
   int16_t value_y;
   int16_t value_z;
   uint8_t txt_x[ 15 ];
   uint8_t txt_y[ 15 ];
   uint8_t txt_z[ 15 ];

   value_x = accel2_read_xaxis( &accel2 );
   value_y = accel2_read_yaxis( &accel2 );
   value_z = accel2_read_zaxis( &accel2 );

   log_printf( &logger, "Axis X: %d\r\n", txt_x );

   log_printf( &logger, "Axis Y: %d\r\n", txt_y );

   log_printf( &logger, "Axis Z: %d\r\n", txt_z );
   
   log_printf( &logger, "-------------------------------" );

   Delay_ms( 5000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel2

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
