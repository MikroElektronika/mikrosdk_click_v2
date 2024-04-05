

---
# DAC 2 click

DAC 2 click represents a 16-bit digital-to-analog converter.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dac2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dac-2-click)

---


#### Click library 

- **Author**        : Mihajlo Djordjevic
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Dac2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Dac2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void dac2_cfg_setup ( dac2_cfg_t *cfg ); 
 
- Initialization function.
> DAC2_RETVAL dac2_init ( dac2_t *ctx, dac2_cfg_t *cfg );

- Click Default Configuration function.
> void dac2_default_cfg ( dac2_t *ctx );


#### Example key functions :

- This function executes default configuration for LTC2601 click.
> void dac2_default_cfg ( dac2_t *ctx );
 
- This function required percentage value ( from 0% to 100% ) convert to digital input and transforms it to the output voltage from 0 to Vref [mV].
> void dac2_write_output_voltage_procentage ( dac2_t *ctx, uint8_t value_pct );

## Examples Description

> 
> This example code presents the usage of DAC 2 Click, and digital-to-analog converter.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Application Init performs Logger and Click initialization.
> 

```c

{
    log_cfg_t log_cfg;
    dac2_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    dac2_cfg_setup( &cfg );
    DAC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    dac2_init( &dac2, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ----- DAC 2  Click ----- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    dac2_default_cfg( &dac2 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

>
> This example of the DAC 2 communicates with MCU through the SPI communication, 
> send digital input ( form 0 to 100 with step 1 ) and transforms it 
> to the output voltage, ranging from 0 to Vref [mV].
> 

```c

void application_task ( void )
{
    uint16_t voltage_out;
    uint8_t value_pct;

    for ( value_pct = 0; value_pct <= 100; value_pct += 10 )
    {
        dac2_write_output_voltage_procentage( &dac2, value_pct );
        voltage_out = value_pct * 50;
        log_printf( &logger, "Voltage Output: %d mV\r\n", voltage_out );
        
        voltage_out = value_pct;
        log_printf( &logger, "Percentage Output: %d %%\r\n", voltage_out );
        
        log_printf( &logger, "--------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }

    log_printf( &logger, "###############################\r\n" );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Dac2

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
