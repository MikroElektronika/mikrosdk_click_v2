
---
# Fingerprint 2 click

Fingerprint 2 Click is a new fingerprint scanner Click board simplified for everyone's use and it's very easy to implement! This add-on board consists of a high-speed Nuvoton processor which carries high-performance fingerprint algorithm developed for on-board A-172-MRQ fingerprint sensor from company ByNew Technology Inc. This board can be used as a standalone device when connected over USB to PC or it can be controlled by the MCU/processor over serial UART interface. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fingerprint2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fingerprint-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Fingerprint2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fingerprint2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void fingerprint2_cfg_setup ( fingerprint2_cfg_t *cfg ); 
 
- Initialization function.
> FINGERPRINT2_RETVAL fingerprint2_init ( fingerprint2_t *ctx, fingerprint2_cfg_t *cfg );


#### Example key functions :

- This function registrates fingerprint on index.
> void fingerprint2_reg_one_fp ( fingerprint2_t *ctx, uint8_t fp_index );
 
- This function deletes fingerprint on index.
> void fingerprint2_delete_one_fp ( fingerprint2_t *ctx, uint8_t fp_index );

- This function restarts device.
> void fingerprint2_reset ( fingerprint2_t *ctx );


## Examples Description

> This example demonstrates the use of Fingerprint 2 click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, enables the click board, and then executes a command for registering a fingerprint.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint2_cfg_t cfg;

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

    fingerprint2_cfg_setup( &cfg );
    FINGERPRINT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    fingerprint2_init( &fingerprint2, &cfg );
    
    fingerprint2_reset ( &fingerprint2 );
    Delay_ms( 1000 );
    
    fp_reg_one( 0 );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Compares a fingerprint on input to the registered fingerprint and displays the results on the USB UART every 5 seconds.

```c

void application_task ( void )
{    
    fp_compare( );
    Delay_ms( 5000 );
} 

```

## Note
> In the registration state each fingerprint needs to be enrolled 3 times.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fingerprint2

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
