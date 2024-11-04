 

---
# MAGNETO 4 Click

Magneto 4 Click is a high-resolution magnetic encoder Click board™ which allows contactless motion sensing down to 0.5µm.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/magneto-4-click)

---


#### Click library 

- **Author**        : Luka Filipovic
- **Date**          : Nov 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the Magneto4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneto4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneto4_cfg_setup ( magneto4_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETO4_RETVAL magneto4_init ( magneto4_t *ctx, magneto4_cfg_t *cfg );

- Click Default Configuration function.
> void magneto4_default_cfg ( magneto4_t *ctx );


#### Example key functions :

- Get Magnetic measurement status
> uint8_t magneto4_get_magnetic_status ( magneto4_t *ctx, mag_status_t *mag_status );
 
- Encoder position
> void magneto4_get_encoder_position ( magneto4_t *ctx );

- Encoder direction
> uint8_t magneto4_get_encoder_direction ( magneto4_t *ctx, mag_status_t *mag_status );

## Examples Description

> Reads and logs magnetic field strength values
> if magnetic field strength values bigger than 3000, 
> start magnetic linear position mode,   
> when moving the sensor from left to right the position for 1 step is reduced.

**The demo application is composed of two sections :**

### Application Init 

> Initializes Driver init and sets start encoder position on the zero.
> Reads and logs magnetic field strength values.
> For starting an encoder, it is necessary that the magnetic field strength 
> is greater than 3000.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto4_cfg_t cfg;

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

    magneto4_cfg_setup( &cfg );
    MAGNETO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto4_init( &magneto4, &cfg );
    
    magneto4_default_cfg ( &magneto4 );
    
    log_printf( &logger, " --- Please, bring the magnet close ---\r\n" );

    while ( magnetic_field < MAGNETO4_MAX_MAGNETIC_FIELD_VALUE )
    {
        magnetic_field = magneto4_get_magnetic_field( &magneto4 );
        log_printf( &logger, " Magnetic field strength : %d\r\n", magnetic_field );
        Delay_ms ( 1000 );
    }
    
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
    log_printf( &logger, " --- Magnetic Linear Position ---\r\n" );
}
  
```

### Application Task

> When moving the sensor from left to right, one step is added 
> and when moving from right to left, the position for 1 step is reduced.

```c

void application_task ( void )
{
    //  Task implementation.
    
    magneto4_get_encoder_position( &magneto4 );
    
    enc_position = magneto4.encoder_position;

    if ( old_position != enc_position )
    {
        log_printf( &logger, " Encoder position : %d\r\n", enc_position );
        log_printf( &logger, " ------------------------\r\n" );
    }
    
    old_position = enc_position;
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto4

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
