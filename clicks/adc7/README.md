\mainpage Main Page
 
 

---
# ADC 7 Click

ADC 7 Click is an advanced 32-bit analog to digital converter (ADC) which uses 
the LTC2500-32, a 32-bit oversampling SAR ADC with a configurable digital 
filter. The filter provides several presets (selectable via the hardware pin),
as well as programming of the filtering parameters, via the industry-standard 
SPI interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc7_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ADC7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void adc7_cfg_setup ( adc7_cfg_t *cfg ); 
 
- Initialization function.
> ADC7_RETVAL adc7_init ( adc7_t *ctx, adc7_cfg_t *cfg );

- Click Default Configuration function.
> void adc7_default_cfg ( adc7_t *ctx );


#### Example key functions :

- Function performs the device configuration by sending configuration data .
> uint8_t adc7_set_config ( adc7_t* ctx, uint8_t gain_config, uint8_t down_samp_factor, uint8_t filter_type );
 
- Function generates clock signal on MCK pin and on that way starts conversion.
> void adc7_start_conv_cycle ( adc7_t* ctx );

- Function reads voltage value from AD converter and calculates this value to mV.
> uint8_t adc7_read_results ( adc7_t* ctx, float* voltage );

## Examples Description

> This example performs the reads of the converted voltage value.
> Results will be logged on uart terminal. Repeats operation every 200ms.


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and performs configuration for conversion cycles.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc7_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.

    adc7_cfg_setup( &cfg );
    ADC7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc7_init( &adc7, &cfg );
    
    adc7_default_cfg( &adc7 );
}
  
```

### Application Task

> Performs the determined number of conversion cycles which are necessary for averaging.
> When all conversion cycles are done, it reads the converted voltage value.
> Results will be logged on UART terminal every second.

```c

void application_task ( void )
{
    adc7_start_conv_cycle( &adc7 );
    adc7_read_results( &adc7, &voltage_data );
    log_printf( &logger, "Voltage: %.2f mV\r\n", voltage_data );

    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC7

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
