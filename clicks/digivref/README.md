\mainpage Main Page
 
 

---
# DigiVref Click

DigiVref Click is a very precise voltage reference Click board™, which allows one of four different voltage values to be selected over the SPI interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digivref_click.png" height=300px>
</p>


[Click Product page](https://www.mikroe.com/digivref-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the DigiVref Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DigiVref Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void digivref_cfg_setup ( digivref_cfg_t *cfg ); 
 
- Initialization function.
> DIGIVREF_RETVAL digivref_init ( digivref_t *ctx, digivref_cfg_t *cfg );

- Click Default Configuration function.
> void digivref_default_cfg ( digivref_t *ctx );


#### Example key functions :

- This function sets reference output voltage.
> void digivref_set_output_voltage ( digivref_t *ctx, uint8_t v_ref );

## Examples Description

> This app changes the reference output voltage. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    digivref_cfg_t cfg;

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

    digivref_cfg_setup( &cfg );
    DIGIVREF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    digivref_init( &digivref, &cfg );
}
  
```

### Application Task

> Changes the reference output voltage every 3 seconds.

```c

void application_task ( void )
{
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_4096mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage(  &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_1024mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_2048mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    digivref_set_output_voltage( &digivref, DIGIVREF_REF_VOLTAGE_3072mV );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiVref

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
