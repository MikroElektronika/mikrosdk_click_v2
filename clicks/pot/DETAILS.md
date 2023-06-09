
# POT click

> Click board with the accurate selectable reference voltage output.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pot-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : nov 2019.
- **Type**          : ADC type


# Software Support

We provide a library for the Pot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pot Click driver.

#### Standard key functions :

- `pot_cfg_setup` Config Object Initialization function.
```c
void pot_cfg_setup ( pot_cfg_t *cfg ); 
```

- `pot_init` Initialization function.
```c
err_t pot_init ( pot_t *ctx, pot_cfg_t *cfg );
```

#### Example key functions :
 
- `pot_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t pot_read_an_pin_value ( pot_t *ctx, uint16_t *data_out );
```

- `pot_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t pot_read_an_pin_voltage ( pot_t *ctx, float *data_out );
```

## Examples Description

> Click board with the accurate selectable reference voltage output.

**The demo application is composed of two sections :**

### Application Init 

> Performs logger and Click initialization.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pot_cfg_t pot_cfg;  /**< Click config object. */

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
    pot_cfg_setup( &pot_cfg );
    POT_MAP_MIKROBUS( pot_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == pot_init( &pot, &pot_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Reads and displays on the USB UART the voltage level measured from AN pin.

```c

void application_task ( void )
{
    float voltage = 0;
    if ( POT_OK == pot_read_an_pin_voltage ( &pot, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage : %.3f[V]\r\n\n", voltage );
        Delay_ms( 1000 );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pot

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
