\mainpage Main Page


---
# UV click

> Design devices that warn you of excesive ultraviolet radiation levels with UV click. This click boards carries the ML8511 IC that is sensitive to UV-A (365-315 nm) and UV-B (315-280 nm) rays.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uv_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/uv-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Uv Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Uv Click driver.

#### Standard key functions :

- `uv_cfg_setup` Config Object Initialization function.
```c
void uv_cfg_setup ( uv_cfg_t *cfg ); 
```

- `uv_init` Initialization function.
```c
err_t uv_init ( uv_t *ctx, uv_cfg_t *cfg );
```

#### Example key functions :

- `uv_read_adc_voltage` ADC Voltage Reading function.
```c
err_t uv_read_adc_voltage ( uv_t *ctx, float *data_out );
```

- `uv_calc_index` UV Index Calculation function.
```c
void uv_calc_index ( uv_t *ctx, float data_in, uint8_t *data_out );
```

## Examples Description

> This is a example which demonstrates the use of UV Click board.

**The demo application is composed of two sections :**

### Application Init 

> Configuration of the click and log objects.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    uv_cfg_t cfg;

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

    // Click initialization.
    uv_cfg_setup( &cfg );
    UV_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == uv_init( &uv, &cfg ) )
    {
        log_info( &logger, "---- Application Init Error ----" );
        log_info( &logger, "---- Please, run program again ----" );
        for ( ; ; );
    }
    uv_set_callback_handler( &uv, application_callback );
    uv_device_enable( &uv );
    Delay_ms ( 1000 );
    uv_voltage = 0;
    uv_index = 0;
    log_info( &logger, "---- Application Init Done ----\r\n" );
}
  
```

### Application Task

> Reads the result of AD conversion once per second and calculates the UV index based on that. Results are being sent to the USB UART where you can track their changes.

```c

void application_task ( void )
{
    if ( SPI_MASTER_ERROR != uv_read_adc_voltage( &uv, &uv_voltage ) )
    {
        uv_calc_index( &uv, uv_voltage, &uv_index );

        log_printf( &logger, " UV Index [0-15] : %u\r\n", ( uint16_t ) uv_index );
        log_printf( &logger, " UV ADC Voltage [V] : %.2f\r\n", uv_voltage );
        log_printf( &logger, "------------------------------\r\n" );
    }

    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Uv

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
