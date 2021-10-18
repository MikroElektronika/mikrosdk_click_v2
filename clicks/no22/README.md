\mainpage Main Page
 
 

---
# NO2 2 click

NO2 2 Click is a gas sensor Click board™, equipped with the MiCS-2714, a compact metal oxide (MOS) sensor. This sensor reacts to the presence of nitrogen dioxide (NO2) and hydrogen (H2).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/no22_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/no2-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the NO22 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NO22 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void no22_cfg_setup ( no22_cfg_t *cfg ); 
 
- Initialization function.
> NO22_RETVAL no22_init ( no22_t *ctx, no22_cfg_t *cfg );

- Click Default Configuration function.
> void no22_default_cfg ( no22_t *ctx );


#### Example key functions :

- Function for reading ADC data
> uint16_t no22_read_data ( no22_t *ctx );
 
- Function for reading ppb data
> float no22_get_ppb ( no22_t *ctx );

- Function for setting pht pin
> uint8_t no22_set_pht_state ( no22_t *ctx, uint8_t state );


## Examples Description

> 
> Measure the level of NO2
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Driver init
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    no22_cfg_t cfg;
    uint8_t error_data;

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

    
    no22_cfg_setup( &cfg );
    NO22_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    no22_init( &no22, &cfg );

    error_data = no22_set_pht_state( &no22, NO22_PIN_STATE_LOW );

    if ( error_data == NO22_DEVICE_ERROR )
    {
        log_printf( &logger, "Device error \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "***** App init ***** \r\n" );
}
  
```

### Application Task

>
> Measures in span of 1 seconc ppb of NO2
> 

```c

void application_task ( )
{
    uint16_t temp_data_read;
    float data_ppb;
    
    temp_data_read = no22_read_data( &no22 );
    log_printf( &logger, "ADC: %d \n\r", temp_data_read );
    
    data_ppb = no22_get_ppb( &no22 );
    log_printf( &logger, "PPB: %f \r\n", data_ppb );
    
    log_printf( &logger, "___________________________\r\n" );
    
    Delay_ms( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NO22

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
