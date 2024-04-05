

---
# Gyro click

Gyro click is an add-on board in mikroBUS form factor. It features L3GD20 three-axis digital gyroscope module capable of providing the measured angular rate, as well as ambient temperature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gyro_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gyro-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Gyro Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gyro Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gyro_cfg_setup ( gyro_cfg_t *cfg ); 
 
- Initialization function.
> GYRO_RETVAL gyro_init ( gyro_t *ctx, gyro_cfg_t *cfg );

- Click Default Configuration function.
> void gyro_default_cfg ( gyro_t *ctx );


#### Example key functions :

- Function get data from two L3GD20 register.
> int16_t gyro_get_axis( gyro_t *ctx, uint8_t adr_reg_low )
 
- Function read Gyro X-axis, Y-axis and Z-axis axis.
> void gyro_read_gyro( gyro_t *ctx, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z );

- Function read temperature data.
> uint8_t gyro_read_temperature ( gyro_t *ctx );

## Examples Description

> This example displays values of Gyro sensor (x, y, z axis)

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver, initialize L3GD20 register and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gyro_cfg_t cfg;

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

    gyro_cfg_setup( &cfg );
    GYRO_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gyro_init( &gyro, &cfg );
    gyro_default_cfg ( &gyro);
}
  
```

### Application Task

> This is a example which demonstrates the use of Gyro Click board.
> Measured Gyro coordinates ( X-axis, Y-axis, Z-axis ) and temperature in degrees C are being sent
> to the Usart Terminal where you can track their changes.
> All data logs on usb uart for every 2 sec. 

```c

void application_task ( void )
{
    //  Task implementation.

    gyro_read_gyro(  &gyro, &gyrox,  &gyroy, &gyroz );
    temperature = gyro_read_temperature( &gyro );

    log_printf( &logger, " Axis X : %d \r\n", gyrox );
    log_printf( &logger, " Axis Y : %d \r\n", gyroy );
    log_printf( &logger, " Axis Z : %d \r\n", gyroz );
    log_printf( &logger, " Temp.: %.2f C\r\n", temperature );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}


```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Gyro

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
