\mainpage Main Page
 
 

---
# Magneto 2 click

Magneto 2 click is a mikroBUS add-on board with Melexis's MLX90316 monolithic
rotary position sensor. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Magneto2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneto2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneto2_cfg_setup ( magneto2_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETO2_RETVAL magneto2_init ( magneto2_t *ctx, magneto2_cfg_t *cfg );

#### Example key functions :

- This function reads 14-bit data value from target register,
  calculates and converts to float angle value from 0� to 360�.
> float magneto2_read_angle ( magneto2_t* ctx )
 
- This function takes 14-bit data value from target register.
> uint16_t magneto2_read_data ( magneto2_t* ctx );


## Examples Description
 
> This example collects data from the sensor, calculates position of absolute 
> rotary angle and then logs it.


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and start write log.


```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto2_cfg_t cfg;

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

    magneto2_cfg_setup( &cfg );
    MAGNETO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto2_init( &magneto2, &cfg );

    angle_value = 0;
    angle_value_old = -1.0;
}
  
```

### Application Task

> Magneto 2 Click communicates with register via SPI by read from register
> and calculates position of absolute rotary angle float value.
> Results are being sent to the Uart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.


```c

void application_task ( void )
{
    angle_value = magneto2_read_angle( &magneto2 );
    Delay_100ms();

    if ( angle_value_old != angle_value )
    {
        if ( angle_value != -1 )
        {
            if ( angle_value != 0 )
            {
                log_printf( &logger, "Angle %f\r\n", angle_value );
            }
            else
            {
                log_printf( &logger, "Magnetic field too weak\r\n" );
            }
        }
        else
        {
            log_printf(&logger, "Magnetic field too strong\r\n");
        }

        angle_value_old = angle_value;
        Delay_ms ( 1000 );
    }
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto2

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
