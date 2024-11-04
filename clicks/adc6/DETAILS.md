
---
# ADC 6 Click

ADC 6 Click is an advanced 24bit multichannel analog to digital converter (ADC),
with 8 fully differential or 15 single ended/pseudo differential sampling inputs,
and very flexible routing capabilities. The Click board� has two 2x10 pin headers,
used both to configure the device and connect the input channels.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/adc6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/adc-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the ADC6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for ADC6 Click driver.

#### Standard key functions :

- `adc6_cfg_setup` Config Object Initialization function.
```c
void adc6_cfg_setup ( adc6_cfg_t *cfg );
```

- `adc6_init` Initialization function.
```c
err_t adc6_init ( adc6_t *ctx, adc6_cfg_t *cfg );
```

- `adc6_default_cfg` Click Default Configuration function.
```c
void adc6_default_cfg ( adc6_t* ctx );
```

#### Example key functions :

- `adc6_get_adc_data` Get data function
```c
uint32_t adc6_get_adc_data ( adc6_t* ctx );
```

- `adc6_read_reg` Generic read function
```c
uint32_t adc6_read_reg ( adc6_t* ctx, uint8_t register_address );
```

- `adc6_write_reg` Generic write function
```c
void adc6_write_reg ( adc6_t* ctx, uint8_t register_address, uint32_t transfer_data );
```

## Examples Description

> This example collects data from the sensor, calculates the voltage to a digital value and then logs it.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and sets configuration which enables channel 0,
puts AIN0 on positive analog input and AIN1 on negative analog input,
enables internal reference voltage (approximately 2.65V (AVDD = 3.3V)),
and also enables bipolar operation mode and puts device on full power mode.
When the ADC is configured for unipolar operation, the output code is natural
(straight) binary with a zero differential input voltage 
resulting in a code of 0x00000000, a midscale voltage resulting in a code 
of 0x00800000, and a full-scale input voltage resulting in a code of 0x00FFFFFF.
When the ADC is configured for bipolar operation, the output code is offset
binary with a negative full-scale voltage resulting in a code of 0x00000000, 
a zero differential input voltage resulting in a code of 0x00800000, 
and a positive full-scale input voltage resulting in a code of 0x00FFFFFF.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    adc6_cfg_t cfg;

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

    adc6_cfg_setup( &cfg );
    ADC6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    adc6_init( &adc6, &cfg );
    adc6_default_cfg( &adc6 );

}
  
```

### Application Task

>  Gets 24-bit converted data in single read mode and logs data on USB UART. Repeats operation every 500 ms.


```c

void application_task ( void )
{
    uint32_t adc_value = 0;

    adc_value = adc6_get_adc_data( &adc6 );

    log_printf( &logger, "The ADC value is: 0x%.6LX\r\n", adc_value );

    Delay_ms ( 500 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.ADC6

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
