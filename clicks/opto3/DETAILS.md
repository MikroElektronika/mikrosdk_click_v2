
---
# Opto 3 Click

> Opto 3 Click is a relay Click board™, equipped with two pairs of optically isolated solid-state relays (SSR).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/opto3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/opto-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Opto3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Opto3 Click driver.

#### Standard key functions :

- `opto3_cfg_setup` Config Object Initialization function.
```c
void opto3_cfg_setup ( opto3_cfg_t *cfg ); 
```

- `opto3_init` Initialization function.
```c
err_t opto3_init ( opto3_t *ctx, opto3_cfg_t *cfg );
```

#### Example key functions :

- `opto3_get_in1` This function gets input 1 pin state.
```c
uint8_t opto3_get_in1 ( opto3_t *ctx );
```

- `opto3_get_in2` This function gets input 2 pin state.
```c
uint8_t opto3_get_in2 ( opto3_t *ctx );
```

- `opto3_set_out1` This function sets output 1 pin state.
```c
void opto3_set_out1 ( opto3_t *ctx, uint8_t state );
```

## Examples Description

> Opto 3 Click to be used in applications that require reinforced galvanic 
> isolation for both their input and output stages.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO interface.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    opto3_cfg_t cfg;

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
    opto3_cfg_setup( &cfg );
    OPTO3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    opto3_init( &opto3, &cfg );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the input pins state and sets their respective output pins to the same logic state.
> The output pins state will be displayed on the USB UART where you can track their changes.

```c
void application_task ( void )
{
    static uint8_t out1_state = 0;
    static uint8_t out2_state = 0;
    uint8_t in1_state = 0;
    uint8_t in2_state = 0;

    in1_state = opto3_get_in1( &opto3 );
    in2_state = opto3_get_in2( &opto3 );
    
    if ( in1_state != out1_state )
    {
        out1_state = in1_state;
        opto3_set_out1( &opto3, out1_state );
        log_printf( &logger, " OUT1 state: %u\r\n", ( uint16_t ) out1_state );
    }
    
    if ( in2_state != out2_state )
    {
        out2_state = in2_state;
        opto3_set_out2( &opto3, out2_state );
        log_printf( &logger, " OUT2 state: %u\r\n", ( uint16_t ) out2_state );
    }
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Opto3

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
