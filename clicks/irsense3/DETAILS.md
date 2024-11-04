
 

---
# IR Sense 3 Click

IR Sense 3 Click is the infrared sensor Click board, designed to be used for the short range IR sensing applications. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irsense3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-sense-3-click)

---


#### Click library 

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the IrSense3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrSense3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irsense3_cfg_setup ( irsense3_cfg_t *cfg ); 
 
- Initialization function.
> IRSENSE3_RETVAL irsense3_init ( irsense3_t *ctx, irsense3_cfg_t *cfg );

- Click Default Configuration function.
> void irsense3_default_cfg ( irsense3_t *ctx );


#### Example key functions :

- Human approach detection
> uint8_t irsense3_human_approach_detect ( irsense3_t *ctx );
 
- Output current of IR sensor
> float irsense3_get_ir_sensor_data ( irsense3_t *ctx );

- Get Interrupt state
> uint8_t irsense3_get_interrupt_state ( irsense3_t *ctx );

## Examples Description

> Demo application shows detection of human and reading of 
> other parameters such as IR current ..

**The demo application is composed of two sections :**

### Application Init 

> Configuring clicks and log objects.
> Software reset and settings the Click in the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense3_cfg_t cfg;

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

    irsense3_cfg_setup( &cfg );
    IRSENSE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense3_init( &irsense3, &cfg );

    // Software reset

    log_info( &logger, "---- Software reset ----" );
    irsense3_software_reset( &irsense3 );
    Delay_1sec( );

    // Configuration

    log_info( &logger, "---- Default config ----" );
    irsense3_default_cfg( &irsense3 );
}
```

### Application Task

> Reads temperature data, outputs current of IR Sensor and checks for human approach. 

```c
void application_task ( void )
{
    float temperature;
    float ir_current_data;
    uint8_t f_detect;

    // Detection Object

    f_detect = irsense3_human_approach_detect( &irsense3 );
    if ( f_detect != 0 )
    {
       log_printf( &logger, ">> Human Approach detected !!!\r\n" );
       Delay_1sec( );
    }

    // Output current of IR sensor

    ir_current_data = irsense3_get_ir_sensor_data( &irsense3 );
    log_printf( &logger, ">> IR current data: %.2f pA.\r\n", ir_current_data );

    // Temperature

    temperature = irsense3_get_temperature_data( &irsense3 );
    log_printf( &logger, ">> Temperature: %.2f C.\r\n", temperature );

    log_printf( &logger, "----------------------------\r\n" );
    Delay_1sec( );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrSense3

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
