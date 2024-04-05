\mainpage Main Page
 
 

---
# Step Up click

Step Up Click is a fixed frequency DC-DC step-up (boost) regulator, which can be obtained from any low voltage input - such as NiCd, NiMH or one cell Li-Po/Li-Ion batteries.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/stepup_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/step-up-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the StepUp Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for StepUp Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void stepup_cfg_setup ( stepup_cfg_t *cfg ); 
 
- Initialization function.
> STEPUP_RETVAL stepup_init ( stepup_t *ctx, stepup_cfg_t *cfg );

- Click Default Configuration function.
> void stepup_default_cfg ( stepup_t *ctx );


#### Example key functions :

- This function calculates ouput value in percent
> float stepup_get_percent ( uint16_t out_value );
 
- This function sets the EN pin state
> void stepup_en_set ( stepup_t *ctx, uint8_t pin_state );

- This function sets output value
> uint8_t stepup_set_out ( stepup_t *ctx, uint16_t out_value );

## Examples Description

> This application enables usage of DC-DC step-up (boost) regulator.>

**The demo application is composed of two sections :**

### Application Init 

> Initializes SPI driver, sets config word, initializes and configures the device

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    stepup_cfg_t cfg;
    
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
    log_info( &logger, "Application Init" );

    //  Click initialization.

    stepup_cfg_setup( &cfg );
    STEPUP_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    stepup_init( &stepup, &cfg );
    
    stepup_default_cfg( &stepup );

    Delay_ms ( 100 );
    log_info( &logger, "Application Task" );
}
  
```

### Application Task

> Sets 3 different boost precentage value to device, value changes every 10 seconds.


```c

void application_task ( void )
{
    log_info( &logger, "Setting DAC boost to 10%%" );
    stepup_set_percentage( &stepup, 10 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_info( &logger, "Setting DAC boost to 60%%" );
    stepup_set_percentage( &stepup, 60 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, "Setting DAC boost to 30%%" );
    stepup_set_percentage( &stepup, 30 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

## Note

> Additional Functions :
> 
> stepup_logPercent() - calls 'stepup_getPercent()' function to get output
> value in expressed as percentage and logs that value. 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.StepUp

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
