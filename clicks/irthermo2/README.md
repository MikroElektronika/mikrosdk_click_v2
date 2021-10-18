\mainpage Main Page
 
---
# IrThermo 2 click

IrThermo 2 click is a non-contact temperature measurement solution. The click board carries the TMP007 infrared thermopile sensor with an integrated math engine.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irthermo2_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/irthermo-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : maj 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the IrThermo2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrThermo2 Click driver.

#### Standard key functions :

- `irthermo2_cfg_setup` Config Object Initialization function.
```c
void irthermo2_cfg_setup ( irthermo2_cfg_t *cfg ); 
```

- `irthermo2_init` Initialization function.
```c
err_t irthermo2_init ( irthermo2_t *ctx, irthermo2_cfg_t *cfg );
```
- `irthermo2_default_cfg` Click Default Configuration function.
``` c
void irthermo2_default_cfg ( irthermo2_t *ctx );
```

#### Example key functions :

- `irthermo2_get_raw_temperature` Function read 16-bit data from raw temperature register and calculate temperature in degrees Celsius.
```c
float irthermo2_get_raw_temperature ( irthermo2_t *ctx );
```

- `irthermo2_get_object_temperature_c` Function read 16-bit data from object temperature register and calculate temperature in degrees Celsius.
```c
float irthermo2_get_object_temperature_c ( irthermo2_t *ctx );
```

- `irthermo2_get_object_temperature_f` Function read 16-bit data from object temperature register and calculate temperature in degrees Fahrenheit.
```c
float irthermo2_get_object_temperature_f ( irthermo2_t *ctx );
```

## Examples Description

> IrThermo 2 is a non-contact temperature measurement click. The sensor absorbs the infrared 
> radiation emitted by the target object (withing the sensor’s field of view) and 
> the integrated math engine calculates its temperature by comparing it with the temperature 
> of the silicon die. The measurement range of the sensor is between –40°C to 125°C.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, set default configuration and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    irthermo2_cfg_t cfg;

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

    irthermo2_cfg_setup( &cfg );
    IRTHERMO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irthermo2_init( &irthermo2, &cfg );

    irthermo2_default_cfg( &irthermo2 );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is a example which demonstrates the use of IrThermo 2 Click board.
> Measures the object temperature value from sensor and calculate temperature in degrees Celsius [ C ].
> Results are being sent to the USART Terminal where you can track their changes.
> All data logs on usb uart for aproximetly every 5 sec when the data value changes.

```c

void application_task ( void )
{
    temperature = irthermo2_get_object_temperature_c( &irthermo2 );

    log_printf( &logger, " Temperature : %.2f C\r\n", temperature );
    log_printf( &logger, "---------------------------\r\n" );

    Delay_ms( 5000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrThermo2

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
