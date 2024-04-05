\mainpage Main Page
 
---
# Force 2 click

Force 2 Click is a mikroBUS™ add-on board with circuitry for implementing Honeywell’s FSS1500NGT Series force sensors into your projects (with a single zone force sensing resistor included with the click).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/force2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/force-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the Force2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Force2 Click driver.

#### Standard key functions :

- `force2_cfg_setup` Config Object Initialization function.
```c
void force2_cfg_setup ( force2_cfg_t *cfg ); 
```

- `force2_init` Initialization function.
```c
err_t force2_init ( force2_t *ctx, force2_cfg_t *cfg );
```

#### Example key functions :

- `force2_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t force2_read_an_pin_value ( force2_t *ctx, uint16_t *data_out );
```

- `force2_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t force2_read_an_pin_voltage ( force2_t *ctx, float *data_out );
```

## Examples Description

> This example demonstrates the use of Force 2 click board by reading and displaying the voltage from AN pin and the calculated force (N) value.

**The demo application is composed of two sections :**

### Application Init 

> Initalizes the driver and logger and makes an initial log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    force2_cfg_t cfg;

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
    force2_cfg_setup( &cfg );
    FORCE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force2_init( &force2, &cfg );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force 2 click   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 500 );
}
  
```

### Application Task

> Reads and displays the voltage from AN pin, then calculates and displays the force in N.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( FORCE2_OK == force2_read_an_pin_voltage ( &force2, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage: %.3f V\r\n", voltage );
        log_printf( &logger, " Force: %.1f N\r\n", 
                    FORCE2_FORCE_MAX - voltage * FORCE2_FORCE_MAX / FORCE2_VREF );
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}  

```

## Note

> Adjust the gain and range onboard potentiometers in order to get zero N when there's no force applied to the sensor.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Force2

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
