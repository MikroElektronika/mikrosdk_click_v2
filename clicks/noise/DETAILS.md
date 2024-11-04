
---
# Noise Click

Noise Click is a mikroBUS add-on board with noise detecting circuitry. It enables you to set a noise detection threshold for alarm systems, environmental monitoring or data logging.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/noise_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/noise-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the noise Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for noise Click driver.

#### Standard key functions :

- `noise_cfg_setup` Config Object Initialization function.
```c
void noise_cfg_setup ( noise_cfg_t *cfg ); 
```

- `noise_init` Initialization function.
```c
err_t noise_init ( noise_t *ctx, noise_cfg_t *cfg );
```

- `noise_default_cfg` Click Default Configuration function.
```c
void noise_default_cfg ( noise_t *ctx );
```

#### Example key functions :

- `noise_set_cmd_reg` This function sets command register.
```c
err_t noise_set_cmd_reg ( noise_t *ctx, uint8_t configuration, uint16_t threshold );
```

- `noise_set_state` This function switches Click on or off.
```c
void noise_set_state ( noise_t *ctx, uint8_t state );
```

- `noise_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t noise_read_an_pin_voltage ( noise_t *ctx, float *data_out );
```

## Examples Description

> This example performs an ambient noise monitoring using the Noise Click board.

**The demo application is composed of two sections :**

### Application Init 

> Device initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    noise_cfg_t cfg;

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
    noise_cfg_setup( &cfg );
    NOISE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    noise_init( &noise, &cfg );

    noise_default_cfg( &noise );
}
  
```

### Application Task

> Reads the voltage from AN pin which presents the noise level and displays it
on the USB UART every 5ms. If the noise is above predefined threshold
(25 percents of max noise, i.e. about 0.4V) an alarm message is being shown. 

```c

void application_task ( void )
{
    float voltage = 0;
    if ( NOISE_OK == noise_read_an_pin_voltage ( &noise, &voltage ) )
    {
        log_printf( &logger, "%.3f\r\n", voltage );
    }
    if ( noise_check_int_pin( &noise ) )
    {
        log_printf( &logger, " Sound overlimit detected!\r\n" );
    }
    Delay_ms ( 5 );
}

```

## Note

> We recommend using the SerialPlot tool for data visualizing.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Noise

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
