
---

# BUCK 7 click

Buck 7 Click is a high-efficiency buck (step-down) DC-DC converter, which can provide digitally adjusted step-down voltage on its output while delivering up to 3.5A of current.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-7-click)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the BUCK7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BUCK7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void buck7_cfg_setup ( buck7_cfg_t *cfg ); 
 
- Initialization function.
> BUCK7_RETVAL buck7_init ( buck7_t *ctx, buck7_cfg_t *cfg );

- Click Default Configuration function.
> void buck7_default_cfg ( buck7_t *ctx );


#### Example key functions :

- Function for settings output voltage.
> void buck7_set_output_voltage ( buck7_t *ctx, uint16_t voltage );
 
- Function for enable chip
> void buck7_enable ( buck7_t *ctx );

- Function for settings chip mode
> void buck7_set_mode ( buck7_t *ctx, uint8_t mode );

## Examples Description

> This demo application controls the voltage at the output using the BUCK 7 click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init, reset chip, enable chip and set mode

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    buck7_cfg_t cfg;

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

    buck7_cfg_setup( &cfg );
    BUCK7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck7_init( &buck7, &cfg );

    buck7_enable( &buck7 );
    buck7_set_mode( &buck7, BUCK7_MODE_PWM );
}
```

### Application Task

> Sets output voltage to 5V, 10V, 15V, 20V, 25V every 3 seconds.
> It is necessary to set the input voltage on 2.7V + maximum output voltage.

```c
void application_task ( )
{
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_5V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_10V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_15V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_20V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_25V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_20V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, BUCK7_OUT_VOLTAGE_15V );
    Delay_ms( 3000 );
    buck7_set_output_voltage( &buck7, 0x0BB8 ); /* 10 V */
    Delay_ms( 3000 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BUCK7

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
