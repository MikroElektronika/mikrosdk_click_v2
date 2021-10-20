\mainpage Main Page
 
---
# DAC 3 click

DAC3 click carries Microchip’s MCP4726 IC, a 12-bit digital-to-analog converter, along with voltage output screw terminals. The digital value is converted to the appropriate voltage level in the range between GND and REFERENCE (VCC or 4.096V), which is proportional to the received 12-bit number.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/dac3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the DAC3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for DAC3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac3_cfg_setup ( dac3_cfg_t *cfg ); 
 
- Initialization function.
> DAC3_RETVAL dac3_init ( dac3_t *ctx, dac3_cfg_t *cfg );

- Click Default Configuration function.
> void dac3_default_cfg ( dac3_t *ctx );


#### Example key functions :

- This function configures the click module.
> void dac3_write_all_mem ( dac3_t *ctx, uint16_t value );
 
- This function sends a command to the click module using SPI communication.
> void dac3_send_command ( dac3_t *ctx, uint8_t cmd );

- This function sets the output voltage on the click module terminal.
> void dac3_set_out_voltage ( dac3_t *ctx, uint16_t output );

## Examples Description

> This example showcases how to initialize, configure and use the DAC 3 click module. The click
  performs digital to analog conversion and the output voltage can be read on the output termi-
  nal using a multimeter. An oscilloscope is required to read the analog signal. 

**The demo application is composed of two sections :**

### Application Init 

> This function configures and initializes the click and logger modules. The write_all_mem(...)
  function configures DAC settings. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac3_cfg_t cfg;

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

    dac3_cfg_setup( &cfg );
    DAC3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac3_init( &dac3, &cfg );

    dac3.dac_cfg.vrl = 0;
    dac3.dac_cfg.power = 0;
    dac3.dac_cfg.gain = 0;

    dac3_write_all_mem( &dac3, 0 );
    Delay_100ms( );
}
  
```

### Application Task

> This function resets and wakes up the click module and then changes the output voltage on the
  output terminal a few times in a loop with a 5 second delay. It does so every 1 second. 

```c

void application_task ( void )
{
    uint8_t cnt;
    uint32_t output_value;

    output_value = 500;

    dac3_send_command( &dac3, DAC3_RESET );
    Delay_100ms( );

    dac3_send_command( &dac3, DAC3_WAKE_UP );
    Delay_100ms( );

    for ( cnt = 1; cnt < 9; cnt ++ )
    {
        dac3_set_out_voltage( &dac3, output_value * cnt );

        log_printf( &logger, " .current DAC value: %d\r\n", output_value * cnt );
        log_printf( &logger, " .output voltage: %d mV\r\n", ( ( output_value * cnt ) * 79 ) / 64 );
        log_printf( &logger, "-------------------------------\r\n" );

        Delay_ms( 5000 );
    }

    log_printf( &logger, "###############################\r\n" );
    Delay_1sec( );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.DAC3

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
