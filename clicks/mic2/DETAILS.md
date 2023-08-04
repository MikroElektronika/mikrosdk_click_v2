
---
# MIC 2 click

> MIC 2 click is equipped with a small electret microphone, accompanied by a suitable pre-amplifying circuit. The small electret microphone is not capable of providing sufficient line-level output; therefore, the pre-amp has to be used

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mic-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : ADC type


# Software Support

We provide a library for the Mic2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Mic2 Click driver.

#### Standard key functions :

- `mic2_cfg_setup` Config Object Initialization function.
```c
void mic2_cfg_setup ( mic2_cfg_t *cfg ); 
```

- `mic2_init` Initialization function.
```c
err_t mic2_init ( mic2_t *ctx, mic2_cfg_t *cfg );
```

#### Example key functions :

- `mic2_set_potentiometer` This function set the value of digital potentiometer.
```c
void mic2_set_potentiometer ( mic2_t *ctx, uint8_t ptt_value );
```

- `mic2_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t mic2_read_an_pin_value ( mic2_t *ctx, uint16_t *data_out );
```

- `mic2_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t mic2_read_an_pin_voltage ( mic2_t *ctx, float *data_out );
```

## Example Description

> This range is suited for audio and/or speech applications.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and logger and sets the digital potentiometer.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic2_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    mic2_cfg_setup( &cfg );
    MIC2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic2_init( &mic2, &cfg );

    mic2_set_potentiometer( &mic2, 35 );
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads the AN pin voltage and displays the results on the USB UART every 100ms.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( MIC2_OK == mic2_read_an_pin_voltage ( &mic2, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms( 100 );
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Mic2

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
