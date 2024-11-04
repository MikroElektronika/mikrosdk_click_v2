

---
# MIC33153 Click

MIC33153 Click is a DC-DC adjustable step-down (buck) converter that is designed to deliver a substantial amount of current to very demanding loads, with the voltage output up to 3.5V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic33153_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/mic33153-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Mic33153 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic33153 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic33153_cfg_setup ( mic33153_cfg_t *cfg ); 
 
- Initialization function.
> MIC33153_RETVAL mic33153_init ( mic33153_t *ctx, mic33153_cfg_t *cfg );

- Click Default Configuration function.
> void mic33153_default_cfg ( mic33153_t *ctx );


#### Example key functions :

- This function writes 12-bit value to DAC and that causes that output voltage be seted on determined value.
> void mic33153_write_dac ( mic33153_t *ctx, const uint16_t value_dac );
 
- This function enables or disables output voltage depending on the state value.
> void mic33153_enable_out ( mic33153_t *ctx, uint8_t state );

- This function hecks state of PG (INT) pin. If state is 1 that means that output voltage is above 92% of its steady
- state voltage. If state is 0 that means that output voltage is below 86% of its steady state voltage.
> uint8_t mic33153_check_power_good ( mic33153_t *ctx );

## Examples Description

> This app enables step-down (buck) converter.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Click driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic33153_cfg_t cfg;

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

    mic33153_cfg_setup( &cfg );
    MIC33153_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic33153_init( &mic33153, &cfg );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Activates the output voltage of the device, and then sets output voltage to various different values.
> All data is being logged on USB UART.  

```c

void application_task ( void )
{
    mic33153_enable_out( &mic33153, MIC33153_OUT_ENABLE );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_1000MV );
    log_printf( &logger, "Output voltage set to 1000mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_1500MV );
    log_printf( &logger, "Output voltage set to 1500mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_2000MV );
    log_printf( &logger, "Output voltage set to 2000mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_2500MV );
    log_printf( &logger, "Output voltage set to 2500mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_3000MV );
    log_printf( &logger, "Output voltage set to 3000mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    mic33153_write_dac ( &mic33153, MIC33153_VOLTAGE_3200MV );
    log_printf( &logger, "Output voltage set to 3200mV\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "-----------------------------------\r\n" );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic33153

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
