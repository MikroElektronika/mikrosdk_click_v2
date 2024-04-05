\mainpage Main Page
 
# Balancer 3 click

> Balancer 3 Click is overvoltage protection device for 2-series cell lithium-ion battery packs that incorporates a high-accuracy precision overvoltage detection circuit and automatic cell imbalance correction. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/balancer3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/balancer-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Balancer3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Balancer3 Click driver.

#### Standard key functions :

- `balancer3_cfg_setup` Config Object Initialization function.
```c
void balancer3_cfg_setup ( balancer3_cfg_t *cfg ); 
```
 
- `balancer3_init` Initialization function.
```c
balancer3_init ( balancer3_t *ctx, balancer3_cfg_t *cfg );
```

#### Example key functions :

- `balancer3_enable_cell_balance` Cell Balance Enable function.
```c
void balancer3_enable_cell_balance ( balancer3_t *ctx, uint8_t state );
```

- `balancer3_check_overvoltage` Overvoltage Condition Check function.
```c
uint8_t balancer3_check_overvoltage ( balancer3_t *ctx );
```

## Examples Description

> This application is device for 2-series cell lithium-ion battery.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device coummunication and enables cell balancing.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer3_cfg_t cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    balancer3_cfg_setup( &cfg );
    BALANCER3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer3_init( &balancer3, &cfg );
         
    balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
    log_printf( &logger, "* Normal operation - Cell balance enabled *\r\n" );
    
    log_info( &logger, " Application Task " );
}
  
```

### Application Task

> Checks if overvoltage is occured and disables cell balancing. If overvoltage doesn't occur it enables cell balancing.

```c

void application_task ( void )
{
    static uint8_t old_ov_state = 0;
    uint8_t ov_state = balancer3_check_overvoltage( &balancer3 );
    if ( old_ov_state != ov_state )
    {
        old_ov_state = ov_state;
        if ( BALANCER3_OV_COND_NOT_DETECTED == ov_state )
        {
            log_printf( &logger, "* Normal operation - Cell balance enabled *\r\n" );
            balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_EN );
        }
        else
        {
            log_printf( &logger, "* Overvoltage condition - Cell balance disabled * \r\n" );
            balancer3_enable_cell_balance( &balancer3, BALANCER3_CELL_BALANCE_DIS );
        }
    }
    Delay_ms ( 1 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer3

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
