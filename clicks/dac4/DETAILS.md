
---
# DAC 4 click

DAC 4 Click carries Microchip’s MCP4728 IC, a Quad Digital-to-Analog Converter with nonvolatile (EEPROM) Memory. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-4-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Dac4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac4_cfg_setup ( dac4_cfg_t *cfg ); 
 
- Initialization function.
> DAC4_RETVAL dac4_init ( dac4_t *ctx, dac4_cfg_t *cfg );

- Click Default Configuration function.
> void dac4_default_cfg ( dac4_t *ctx );


#### Example key functions :

- Setting channel voltage reference values
> uint8_t dac4_voltage_reference_set ( dac4_t *ctx, uint8_t v_ref_channel_a, uint8_t v_ref_channel_b, uint8_t v_ref_channel_c, uint8_t v_ref_channel_d );
 
- Writing channel gain values
> uint8_t dac4_gain_set ( dac4_t *ctx, uint8_t gain_channel_a, uint8_t gain_channel_b, uint8_t gain_channel_c, uint8_t gain_channel_d );

- Reading channel data and forming reports
> uint8_t dac4_data_report ( dac4_t *ctx, dac_channel_setting_t * channel_buffer );

## Examples Description

> This application enables usage of digital to analog converter.

**The demo application is composed of two sections :**

### Application Init 

> Initializes I2C driver, executes general call reset and wake up commands and initializes variables to zero

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    dac4_cfg_t cfg;

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

    dac4_cfg_setup( &cfg );
    DAC4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac4_init( &dac4, &cfg );
    log_info( &logger, "---- Application ----" );

    Delay_ms( 500 );
    dac4_general_call_reset( &dac4 );
    Delay_ms( 500 );
    dac4_general_call_wake_up( &dac4 );
    Delay_ms( 500 );

    dac4_default_cfg( &dac4 );
    
    log_printf( &logger, "~-- App init done \r\n \r\n" );
}
  
```

### Application Task

> Waits for user input and based on it logs reports or sets output value for specified channel

```c

void application_task ( void )
{
    dac4_channel_report( );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac4

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
