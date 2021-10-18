\mainpage Main Page
 
---
# Force click

Force click is a mikroBUS™ add-on board with circuitry for implementing Interlink Electronics’ Force Sensing Resistors into your projects (with a single zone force sensing resistor included with the click). The Force Sensing Resistor is a thin sensor made of two membranes that are separated by a spacer around the edges.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/force_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/force-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Force Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Force Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void force_cfg_setup ( force_cfg_t *cfg ); 
 
- Initialization function.
> FORCE_RETVAL force_init ( force_t *ctx, force_cfg_t *cfg );

- Click Default Configuration function.
> void force_default_cfg ( force_t *ctx );


#### Example key functions :

- This function reads ADC data.
> force_data_t force_generic_read ( force_t *ctx );
 
- This function calculates resistance data based on the ADC input.
> float force_get_resistance ( uint32_t adc_value );

- This function calculates the correction factor based on temperature and humidity data.
> force_get_correction_factor ( float temperature, float humidity );

## Examples Description

> This example showcases how to initialize and configure the logger and click modules and 
  read and display ADC voltage data read from the analog pin.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    force_cfg_t cfg;

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

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force  click    \r\n" );
    log_printf( &logger, "--------------------\r\n\r\n" );

    //  Click initialization.

    force_cfg_setup( &cfg );
    FORCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force_init( &force, &cfg );
}
  
```

### Application Task

> This function reads and displays ADC voltage data from the analog pin every second. 

```c

void application_task ( )
{
    force_data_t tmp;
    
    //  Task implementation.
    
    tmp = force_generic_read ( &force );
    log_printf( &logger, " * ADC value : %d \r\n", tmp );
    log_printf( &logger, "--------------------- \r\n" );
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Force

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
