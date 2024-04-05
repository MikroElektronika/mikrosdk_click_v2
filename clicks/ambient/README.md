\mainpage Main Page
  

---
# Ambient click

> Ambient click carries the Melexis MLX75305 IC. It’s a CMOS integrated optical sensor that consists of a photodiode, a transimpendance amplifier, and an output transistor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Ambient Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient Click driver.

#### Standard key functions :

- `ambient_cfg_setup` Config Object Initialization function.
```c
void ambient_cfg_setup ( ambient_cfg_t *cfg ); 
```

- `ambient_init` Initialization function.
```c
err_t ambient_init ( ambient_t *ctx, ambient_cfg_t *cfg );
```

#### Example key functions :

- `ambient_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t ambient_read_an_pin_voltage ( ambient_t *ctx, float *data_out );
```

- `ambient_get_light_intensity` Calculates the light intensity from analog voltage measurement of the Melexis MLX75305 IC on Ambient click board.
```c
uint16_t ambient_get_light_intensity ( ambient_t *ctx );
```

## Example Description

> This application turns light intensity into voltage.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    ambient_cfg_setup( &cfg );
    AMBIENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient_init( &ambient, &cfg );

    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> This is an example which demonstrates the use of Ambient click board.
Ambient click reads ADC voltage once per second and converts it to light intensity [ uW/cm2 ].
Results are being sent to the USB UART where you can track their changes.

```c

void application_task ( void )
{
    uint16_t light_intensity = ambient_get_light_intensity( &ambient );
    log_printf( &logger, " Light Intensity: %u uW/cm2\r\n\n", light_intensity );
    Delay_ms ( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient

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
