

---
# Mic click

Mic click carries the SPQ0410HR5H-B surface mount silicon microphone with maximum RF protection. The click is designed to run on a 3.3V power supply. It communicates with the target microcontroller over the AN pin on the mikroBUS™ line.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/mic-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Mic Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void mic_cfg_setup ( mic_cfg_t *cfg ); 
 
- Initialization function.
> MIC_RETVAL mic_init ( mic_t *ctx, mic_cfg_t *cfg );

- Click Default Configuration function.
> void mic_default_cfg ( mic_t *ctx );


#### Example key functions :

- This function read ADC data.
> mic_data_t mic_generic_read ( mic_t *ctx );

## Examples Description

> This example showcases the initialization and configuration of the click and logger modules and later on reads and displays data recorded by the mic.

**The demo application is composed of two sections :**

### Application Init 

> Initializes LOG communication, ADC and configures AN pin as input on MIKROBUS1.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic_cfg_t cfg;

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

    mic_cfg_setup( &cfg );
    MIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic_init( &mic, &cfg );
}
  
```

### Application Task

> Reads 12 bit ADC data from AN pin and displays it using the logger module. 

```c

void application_task ( void )
{
    mic_data_t tmp;
    
    //  Task implementation.
    
    tmp = mic_generic_read ( &mic );
    
    log_printf( &logger, "** ADC value : [DEC]- %d, [HEX]- 0x%x \r\n", tmp, tmp );

    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic

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
