
---
# Voltmeter click

Voltmeter click is a mikroBUS™ add-on board for measuring voltage in an external electric circuit.
The board is designed to measure Direct Current only, and has a measurement range from 0 to 24V (it’s possible to measure both positive and negative charges).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/voltmeter_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/voltmeter-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Voltmeter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Voltmeter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void voltmeter_cfg_setup ( voltmeter_cfg_t *cfg ); 
 
- Initialization function.
> VOLTMETER_RETVAL voltmeter_init ( voltmeter_t *ctx, voltmeter_cfg_t *cfg );



#### Example key functions :

- Generic write the byte of the data function.
> void voltmeter_write_data ( voltmeter_t *ctx, uint16_t write_data );
 
- Generic read the byte of the data function.
> uint8_t voltmeter_read_byte ( voltmeter_t *ctx );

- Generic reading 16-bit data function.
> uint16_t voltmeter_read_data ( voltmeter_t *ctx );

## Examples Description

> This application give a voltage in milivolts

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables - I2C,
  start calibration reading and also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    voltmeter_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    voltmeter_cfg_setup( &cfg );
    VOLTMETER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    voltmeter_init( &voltmeter, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, " Initialization  Driver \r\n" );
    log_printf( &logger, "------------------------\r\n" );

    voltmeter_calibration( &voltmeter );
    Delay_ms( 100 );
    log_printf( &logger, " Calibration  completed \r\n" );
    log_printf( &logger, "------------------------\r\n" );
    log_printf( &logger, " Measurement  available \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
  
```

### Application Task

> This is an example which demonstrates the use of Voltmeter Click board.
  These examples read ADC value from the register of MCP3201 chip on the
  Voltmeter click board and calculate the voltage value [ mV ].
  Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void )
{
    adc_value = voltmeter_read_data( &voltmeter );
    log_printf( &logger, " ADC Value: %d\r\n", adc_value );

    voltage = voltmeter_get_voltage( &voltmeter, VOLTMETER_VCC_5V_COEFF_0 );
    log_printf( &logger, " Voltage  : %f mV\r\n", voltage );
    log_printf( &logger, "------------------------\r\n");
    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Voltmeter

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
