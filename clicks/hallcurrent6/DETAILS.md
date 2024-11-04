
---
# Hall Current 6 Click

> Hall Current 6 Click is a very accurate current measurement Click board™, based on the ACS723 IC. This IC is a galvanically isolated current sensor, which utilizes the Hall-effect principle.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/hallcurrent6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/hall-current-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the HallCurrent6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for HallCurrent6 Click driver.

#### Standard key functions :

- `hallcurrent6_cfg_setup` Config Object Initialization function.
```c
void hallcurrent6_cfg_setup ( hallcurrent6_cfg_t *cfg ); 
```

- `hallcurrent6_init` Initialization function.
```c
HALLCURRENT6_RETVAL hallcurrent6_init ( hallcurrent6_t *ctx, hallcurrent6_cfg_t *cfg );
```

#### Example key functions :

- `hallcurrent6_read_data` Reads ADC current data
```c
uint16_t hallcurrent6_read_data ( hallcurrent6_t *ctx );
```

- `hallcurrent6_get_current` Reads current data
```c
float hallcurrent6_get_current ( hallcurrent6_t *ctx );
```

- `hallcurrent6_generic_read` Generic read function.
```c
void hallcurrent6_generic_read ( hallcurrent6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

## Example Description

> 
> This application reads current data.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initializations driver init
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent6_cfg_t cfg;

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
    log_info( &logger, "---- App Init ----" );

    //  Click initialization.

    hallcurrent6_cfg_setup( &cfg );
    HALLCURRENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent6_init( &hallcurrent6, &cfg );

    log_info( &logger, "---- App Init Done ----" );
}
  
```

### Application Task

>
> Reads Current data in mA and logs this data to USBUART every 1 sec.
> 

```c

void application_task ( void )
{
    float current;

    current = hallcurrent6_get_current( &hallcurrent6 );
    log_printf( &logger, " Current value: %.2f mA \r\n" , current);
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent6

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
