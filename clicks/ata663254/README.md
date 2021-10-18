\mainpage Main Page
 
---
# ATA663254 click

ATA663254 click is a fully integrated LIN transceiver device with an integrated 5V LDO voltage regulator.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ata663254_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ata663254-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : feb 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Ata663254 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ata663254 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ata663254_cfg_setup ( ata663254_cfg_t *cfg ); 
 
- Initialization function.
> ATA663254_RETVAL ata663254_init ( ata663254_t *ctx, ata663254_cfg_t *cfg );

- Chip enable function.
> void ata663254_enable ( ata663254_t *ctx, uint8_t state );

#### Example key functions :

- Undervoltage detect function.
> uint8_t ata663254_get_rst_state ( ata663254_t *ctx );

- Generic multi write function.
> void ata663254_generic_write ( ata663254_t *ctx, char *data_buf,  uint16_t len );

- Generic multi read function.
> int32_t ata663254_generic_read ( ata663254_t *ctx, char *data_buf,  uint16_t len );

## Examples Description

> This application demonstates the use of ATA663254 Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the click driver and enables the click board.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663254_cfg_t cfg;

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

    ata663254_cfg_setup( &cfg );
    ATA663254_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663254_init( &ata663254, &cfg );
    
    ata663254_enable( &ata663254, 1 );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Depending on the selected mode, it reads all the received data or sends the desired message each 2 seconds.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER

    // RECEIVER - UART polling
    
    int32_t len = ata663254_generic_read( &ata663254, rec_buf, 50 );
    if ( len > 6 )
    {
        log_printf( &logger, "Received data: " );
        for ( int32_t cnt = 0; cnt < len; cnt++  )
        {
            log_printf( &logger, "%c", rec_buf[ cnt ] );
        }
        memset( rec_buf, 0 , 50 );
    }
    Delay_ms( 100 );
#endif
#ifdef DEMO_APP_TRANSMITTER

    // TRANSMITER - TX each 2 sec
       
    ata663254_generic_write( &ata663254, demo_message, 9 );
    log_info( &logger, "--- Data sent ---" );

    Delay_ms( 2000 );
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ata663254

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
