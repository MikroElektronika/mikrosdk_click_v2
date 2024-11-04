\mainpage Main Page
 
 

---
# BI HALL Click

Bi Hall Click is a simple solution for adding a bipolar Hall switch to your design. It carries the Melexis US2882 bipolar Hall-effect switch and a 74LVC1T45 single bit, dual supply transceiver.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/bihall_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/bi-hall-click)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the BiHall Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for BiHall Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void bihall_cfg_setup ( bihall_cfg_t *cfg ); 
 
- Initialization function.
> BIHALL_RETVAL bihall_init ( bihall_t *ctx, bihall_cfg_t *cfg );

- Click Default Configuration function.
> void bihall_default_cfg ( bihall_t *ctx );


#### Example key functions :

- Detecting south & north pole magnetic fields status function.
> uint8_t bihall_det_mag_field ( bihall_t *ctx );

## Examples Description

> 
> Detect the south & north pole magnetic fields.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    bihall_cfg_t cfg;

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
    log_printf(&logger, "---- Application Init ----\r\n");

    //  Click initialization.

    bihall_cfg_setup( &cfg );
    BIHALL_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    bihall_init( &bihall, &cfg );
    
    log_printf(&logger, " Detecting magnetic fields\r\n");
    log_printf(&logger, "--------------------------\r\n");
    
    bihall_state = BIHALL_MAG_POLE_NORTH;
    bihall_state_old = BIHALL_MAG_POLE_NORTH;
}
  
```

### Application Task

>
> This is a example which demonstrates the use of BI HALL Click board.
> Detect the south & north pole magnetic fields near the BI HALL Click.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs on usb uart when magnetic field is detected.
> 

```c

void application_task ( void )
{
    bihall_state = bihall_det_mag_field( &bihall );

    if ( ( bihall_state == BIHALL_MAG_POLE_SOUTH ) && ( bihall_state_old == BIHALL_MAG_POLE_NORTH ) )
    {
        bihall_state_old = BIHALL_MAG_POLE_SOUTH;
        log_printf(&logger, "         ~ SOUTH ~\r\n");
        log_printf(&logger, "--------------------------\r\n");
    }

    if ( ( bihall_state == BIHALL_MAG_POLE_NORTH ) && ( bihall_state_old == BIHALL_MAG_POLE_SOUTH ) )
    {
        log_printf(&logger, "         ~ NORTH ~\r\n");
        log_printf(&logger, "--------------------------\r\n");
        bihall_state_old = BIHALL_MAG_POLE_NORTH;
    }
} 

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.BiHall

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
