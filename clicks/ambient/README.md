\mainpage Main Page
 
 

---
# Ambient click

< Ambient click carries the Melexis MLX75305 IC. It’s a CMOS integrated optical sensor that consists of a photodiode, a transimpendance amplifier, and an output transistor. >

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ambient-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Ambient Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient_cfg_setup ( ambient_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT_RETVAL ambient_init ( ambient_t *ctx, ambient_cfg_t *cfg );


#### Example key functions :

- Generic read function.
> ambient_data_t ambient_generic_read ( ambient_t *ctx );
 
- Calculate light intensity function.
> uint16_t ambient_calculate_light_intensity ( ambient_t *ctx, uint16_t adc_data, uint16_t vcc_val, uint16_t adc_res );

## Examples Description

> This application turns light intensity into voltage.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO,initializationADC, also write log.

```c

void application_init ( void )
{
 log_cfg_t log_cfg;
    ambient_cfg_t cfg;

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

    ambient_cfg_setup( &cfg );
    AMBIENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient_init( &ambient, &cfg );

    log_printf( &logger, "      Initialization ADC      " );
    Delay_ms( 100 );
}
  
```

### Application Task

> This is an example which demonstrates the use of Ambient click board.
  Ambient click reads ADC value and converts to light intensity [ uW/cm2 ].
  Results are being sent to the Usart Terminal where you can track their changes.
  All data logs on USB uart change for every 1 sec.

```c

void application_task ( void )
{
ambient_data_t tmp;
    
    //  Task implementation.
    
    tmp = ambient_generic_read ( &ambient );
    light = ambient_calculate_light_intensity( &ambient, value_adc, AMBIENT_VCC_3_3, AMBIENT_RES_12_BIT );

    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );
    log_printf( &logger, "Light Intensity: %d uW/cm2 \r\n",light );

    Delay_ms( 1000 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient

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
