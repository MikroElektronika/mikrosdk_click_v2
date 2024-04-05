\mainpage Main Page
 
 

---
# Hall Current 5 click

Hall Current 5 Click is a very accurate electric current measurement Click board™ based on the ACS733 IC. This IC is a galvanically isolated current sensor, which utilizes the Hall-effect principle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the HallCurrent5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void hallcurrent5_cfg_setup ( hallcurrent5_cfg_t *cfg ); 
 
- Initialization function.
> HALLCURRENT5_RETVAL hallcurrent5_init ( hallcurrent5_t *ctx, hallcurrent5_cfg_t *cfg );

- Click Default Configuration function.
> void hallcurrent5_default_cfg ( hallcurrent5_t *ctx );


#### Example key functions :

- This function sets ADC resolution.
> void hallcurrent5_set_adc_resolution ( hallcurrent5_t *ctx, float adc_res );
 
- This function gets ADC voltage.
> float hallcurrent5_get_adc_voltage ( hallcurrent5_t *ctx, uint16_t adc_value );


- This function gets ADC current value.
> float hallcurrent5_get_current ( hallcurrent5_t *ctx, uint16_t adc_value );

## Examples Description

> The demo application reads ADC value and current value.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device and ADC Init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent5_cfg_t cfg;

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

    hallcurrent5_cfg_setup( &cfg );
    HALLCURRENT5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent5_init( &hallcurrent5, &cfg );

    // CLICK INIT
    hallcurrent5_set_adc_resolution( &hallcurrent5, HALLCURRENT5_ADC_RESOLUTION_12bit );
    hallcurrent5_set_init_voltage( &hallcurrent5, 316 );
    Delay_100ms();
}
  
```

### Application Task

> Reads current value in mA and this data logs to USBUART every 500ms. 

```c

void application_task ( void )
{
    hallcurrent5_data_t tmp;
    int16_t adc_value;
    uint32_t sum_adc = 0;
    uint8_t cnt;
    float current;
  
    //  Task implementation.
    
    tmp = hallcurrent5_generic_read( &hallcurrent5 );
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    Delay_ms ( 1000 );

    sum_adc = 0;
    for(cnt = 0; cnt < 20; cnt++)
    {
        sum_adc += hallcurrent5_generic_read( &hallcurrent5 );
    }
    adc_value = ( sum_adc / 20 );

    current = hallcurrent5_get_current( &hallcurrent5, adc_value/1.8 );

    if ( current < 0 ) 
    {
        current = 0;
    }

    log_printf( &logger, " ADC value: %d \r\n", adc_value);
    log_printf( &logger, " Current : \r\n", adc_value);

    Delay_ms ( 500 );
}

```

## Note

> Before the start of the program you have to set the starting voltage on AN pin.
> First, measure the voltage in mV on AN pin, when electronic load isn't >  connected to the Click board, 
>  and pass that value as an input parameter of the voltage initialization function. 
 
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent5

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
