
---
# Hall Current click

> Hall Current Click is a compact add-on board that contains a precise solution for AC/DC current sensing. This board features the TLI4970-D050T4, a 16-bit digital SPI output (13-bit current value) coreless magnetic current sensor designed for the current range of ±25A from Infineon Technology. A differential measurement principle allows effective stray field suppression with a highly linear output signal without hysteresis. Due to the integrated primary conductor (current rail), there is no need for external calibration. The TLI4970-D050T4 is highly accurate over temperature range and lifetime with fast overcurrent detection with a configurable threshold.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/hall-current-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the HallCurrent Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent Click driver.

#### Standard key functions :

- `hallcurrent_cfg_setup` Config Object Initialization function.
```c
void hallcurrent_cfg_setup ( hallcurrent_cfg_t *cfg ); 
```

- `hallcurrent_init` Initialization function.
```c
err_t hallcurrent_init ( hallcurrent_t *ctx, hallcurrent_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent_read_data` Generic read 16-bit data function
```c
uint16_t hallcurrent_read_data ( hallcurrent_t *ctx );
```

- `hallcurrent_check_status` Check status of read data function.
```c
uint8_t hallcurrent_check_status ( hallcurrent_t *ctx );
```

- `hallcurrent_read_current` Read electric current function
```c
float hallcurrent_read_current ( hallcurrent_t *ctx );
```

## Examples Description

> The application is current sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - SPI and start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent_cfg_t cfg;

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
    hallcurrent_cfg_setup( &cfg );
    HALLCURRENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent_init( &hallcurrent, &cfg );
    
    HALLCURRENT_SET_DATA_SAMPLE_EDGE;
    
    log_printf( &logger,"------------------------\r\n" );
    log_printf( &logger,  "       Hall Current     \r\n" );
    log_printf( &logger, "------------------------\r\n" );
}
  
```

### Application Task

> This is an example which demonstrates the use of Hall Current Click board.

```c

void application_task ( void )
{
    log_printf( &logger, " Current : %.3f A \r\n", hallcurrent_read_current( &hallcurrent ) );
    log_printf( &logger, "------------------------\r\n" );
    Delay_ms ( 1000 );
} 

```
The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent

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
