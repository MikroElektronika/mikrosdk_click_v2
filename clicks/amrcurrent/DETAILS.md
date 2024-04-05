 
---
# AMR Current click

The AMR current Click is product is ±20A fully integrated bi-directional analog output current sensors that deliver both high accuracy and high bandwidth.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/amrcurrent_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/amr-current-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the AMRCurent Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for AMRCurent Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void amrcurent_cfg_setup ( amrcurent_cfg_t *cfg ); 
 
- Initialization function.
> AMRCURENT_RETVAL amrcurent_init ( amrcurent_t *ctx, amrcurent_cfg_t *cfg );

- Click Default Configuration function.
> void amrcurent_default_cfg ( amrcurent_t *ctx );


#### Example key functions :

- This function writes data to the desired register.
> void amrcurent_generic_write ( amrcurent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
 
- This function reads data from the desired register.
> void amrcurent_generic_read ( amrcurent_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );

- This function read value.
> uint16_t amrcurrent_read_value (  amrcurent_t *ctx );

## Examples Description
 
> This application integrated bi-directional analog output current sensors. 

**The demo application is composed of two sections :**

### Application Init 

> Initializations driver init. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    amrcurent_cfg_t cfg;

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

    amrcurent_cfg_setup( &cfg );
    AMRCURENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    amrcurent_init( &amrcurent, &cfg );
}

  
```

### Application Task

> Reading ADC data and converted current mA data from device and logs it to device. 

```c

void application_task ( void )
{
    //  Task implementation.

    read_adc_val = amrcurrent_read_value ( &amrcurent );
    log_printf( &logger, " - ADC value: \r\n ", read_adc_val );
    
    Delay_ms ( 100 );

    read_curr_val = amrcurrent_get_current (  &amrcurent );
    log_printf( &logger, " - Current value: \r\n ", read_curr_val );
    
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.AMRCurent

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
