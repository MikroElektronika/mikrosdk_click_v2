
 

---
# IR distance Click

IR distance Click carries Sharp’s GP2Y0A60SZ0F distance measuring sensor, which comprises of an integrated PSD (position sensitive detector), an infrared LED and a signal processing circuit. The measuring range is between 10 and 150 cm. The Click is designed to run on either 3.3V or 5V power supply. It communicates with the target MCU over RST and AN pin on the mikroBUS™ line.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irdistance_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ir-distance-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the IrDistance Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for IrDistance Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void irdistance_cfg_setup ( irdistance_cfg_t *cfg ); 
 
- Initialization function.
> IRDISTANCE_RETVAL irdistance_init ( irdistance_t *ctx, irdistance_cfg_t *cfg );

- Click Default Configuration function.
> void irdistance_default_cfg ( irdistance_t *ctx );


#### Example key functions :

- Function enable distance measuring sensor by set RST pin on Stretch Click board.
> void irdistance_enable ( irdistance_t *ctx );
 
- This function reads ADC data using analog_in_read function
> irdistance_data_t irdistance_read_adc ( irdistance_t *ctx );

- Function calculate the voltage output of distance measuring sensor on IR Distance Click board.
> float irdistance_get_voltage_out ( uint32_t adc_value, uint16_t resolution_value, float vcc_value );

## Examples Description

> The Click board outputs an analog voltage corresponding to the distance of the object 
> (through the mikroBUS AN pin). An Enable (EN) pin is also utilized.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO, enable IR sensor, initialization ADC, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    irdistance_cfg_t cfg;

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

    irdistance_cfg_setup( &cfg );
    IRDISTANCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irdistance_init( &irdistance, &cfg );
    irdistance_default_cfg ( &irdistance );
}
  
```

### Application Task

> This is an example which demonstrates the use of IR Distance Click board.
> IR Distance Click reads and displays ADC value.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on USB uart change for every 1 sec.
 

```c

void application_task ( void )
{
    adc_val = irdistance_read_adc( &irdistance );
    log_printf( &logger, " ADC value : %u\r\n", adc_val );
    log_printf( &logger, "---------------------\r\n" );
   
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.IrDistance

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
