
---
# Analog MUX click

Analog MUX Click is a Click board™ that switches one of the sixteen inputs to one output. It employs the CD74HC4067, a High-Speed CMOS Logic 16-Channel Analog Multiplexer/Demultiplexer, produced by Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/analogmux_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/analog-mux-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the AnalogMUX Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AnalogMUX Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void analogmux_cfg_setup ( analogmux_cfg_t *cfg ); 
 
- Initialization function.
> ANALOGMUX_RETVAL analogmux_init ( analogmux_t *ctx, analogmux_cfg_t *cfg );

#### Example key functions :

- Generic read voltage function.
> float analogmux_get_voltage ( float adc_val, uint16_t vref, uint16_t rez );
 
- This function sets the active channel on the MUX.
> void analogmux_set_channel ( analogmux_t *ctx, uint8_t cfg );

## Examples Description

> This example showcases how to initialize, configure and use the Analog MUX click module. 
> The click switches one of the 16 inputs to output so the adc value of that input 
> can be read on the COM (AN) pin. The RST, PWM, CS and INT are used as control output pins. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    analogmux_cfg_t cfg;

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
    Delay_100ms( );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    analogmux_cfg_setup( &cfg );
    ANALOGMUX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    analogmux_init( &analogmux, &cfg );

    analogmux_set_channel( &analogmux, ANALOGMUX_CHANNEL_0 );
    log_printf( &logger, " Channel 0 enabled\r\n" );
    log_printf( &logger, " -------------------\r\n" );
}
  
```

### Application Task

> This function reads ADC value and voltage from channel 0 (AN0) and shows the results 
> on the USB UART every 2 seconds.

```c

void application_task ( void )
{
    uint16_t tmp;
    float val;

    tmp = analogmux_generic_read( &analogmux );
    
    log_printf( &logger, " ADC value : %u\r\n", tmp );

    val = analogmux_generic_read_voltage( &analogmux );

    log_printf( &logger, " Voltage: %.3f mV\r\n", val );
    log_printf( &logger, " -------------------\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AnalogMUX

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
