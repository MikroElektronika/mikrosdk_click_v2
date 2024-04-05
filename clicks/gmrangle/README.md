\mainpage Main Page
 
---
# GMR Angle click

The GMR Angle Click is a Click board™ that features the TLI5012B E1000, which is a pre-calibrated 360° angle sensor that detects the orientation of a magnetic field, made by Infineon. The GMR Angle click is ideal for angular position sensing in industrial and consumer applications such as electrical commutated motor (e.g. BLDC), fans or pumps.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gmrangle_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gmr-angle-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the GmrAngle Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for GmrAngle Click driver.

#### Standard key functions :

- `gmrangle_cfg_setup` Config Object Initialization function.
```c
void gmrangle_cfg_setup ( gmrangle_cfg_t *cfg ); 
```

- `gmrangle_init` Initialization function.
```c
err_t gmrangle_init ( gmrangle_t *ctx, gmrangle_cfg_t *cfg );
```

#### Example key functions :

- `gmrangle_read_data` Generic read 16-bit data function.
```c
uint16_t gmrangle_read_data ( gmrangle_t *ctx, uint8_t reg );
```

- `gmrangle_write_data` Generic write 16-bit data function.
```c
void gmrangle_write_data ( gmrangle_t *ctx, uint8_t reg, uint16_t tx_data );
```

- `gmrangle_calculate_angle` Calculate angle function.
```c
float gmrangle_calculate_angle ( gmrangle_t *ctx );
```

## Examples Description

> This is an example which demonstrates the use of GMR Angle Click board.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO pins, SPI and LOG modules.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gmrangle_cfg_t cfg;

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
    gmrangle_cfg_setup( &cfg );
    GMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gmrangle_init( &gmrangle, &cfg );
    
    GMRANGLE_SET_DATA_SAMPLE_EDGE; 
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   GMR Angle Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "        Start\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Display angle value in degrees.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 300 msec.

```c

void application_task ( void )
{
    angle = gmrangle_calculate_angle( &gmrangle );
    log_printf( &logger, " Angle is %.1f\r\n", angle );
    Delay_ms ( 300 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.GmrAngle

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
