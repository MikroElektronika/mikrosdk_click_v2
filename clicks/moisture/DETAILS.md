
 

---
# Moisture click

Moisture click is a Click board™ that can be used to easily detect a moisture level of the skin, by simply touching the sensitive surface of the PCB.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/moisture_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/moisture-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Moisture Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Moisture Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void moisture_cfg_setup ( moisture_cfg_t *cfg ); 
 
- Initialization function.
> MOISTURE_RETVAL moisture_init ( moisture_t *ctx, moisture_cfg_t *cfg );

- Click Default Configuration function.
> void moisture_default_cfg ( moisture_t *ctx );


#### Example key functions :

- Measurement data function
> uint8_t moisture_get_data ( moisture_t *ctx );
 
- Configure device function
> void  moisture_cfg( moisture_t *ctx, uint16_t gain, uint16_t offset, uint16_t clk_div );

- Soft reset function
> void moisture_soft_reset ( moisture_t *ctx );

## Examples Description

> The demo application displays relative moisture measurement using Moisture click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver and sets moisture gain, offset data and clock divider
> and performs calibration of the device. We advise you not to touch,
> or expose sensor to moisture during the calibration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    moisture_cfg_t cfg;

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

    moisture_cfg_setup( &cfg );
    MOISTURE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    moisture_init( &moisture, &cfg );
    Delay_ms( 100 );

    data_res = moisture_read_word( &moisture, MOISTURE_REG_DEVICE_ID );

    if ( ( data_res != MOISTURE_FDC2112_ID ) && ( data_res != MOISTURE_FDC2212_ID ) )
    {
        log_printf( &logger, "---- Comunication ERROR!!! ---- \r\n" );
        for ( ; ; );
    }
    else
    {
        log_printf( &logger, "---- Comunication OK!!! ---- \r\n" );
    }

    moisture_soft_reset( &moisture );
    moisture_default_cfg( &moisture );

    log_printf( &logger, " --- Calibration start --- \r\n" );
    moisture_cal( &moisture );
    Delay_ms( 1000 );

    log_printf( &logger, " --- Calibration finishing --- \r\n" );
}
```

### Application Task

> The device measure moisture and displays data in percentage every 500ms.

```c
void application_task ( void )
{
    moisture_data = moisture_get_data( &moisture  );
    log_printf( &logger, " Moisture data : %d \r\n", moisture_data );
    Delay_ms( 500 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Moisture

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
