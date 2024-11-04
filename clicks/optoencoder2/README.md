\mainpage Main Page
 

---
# Opto Encoder 2 Click

Opto Encoder 2 Click is a linear incremental optical sensor/encoder Click which can be used for the movement or rotation encoding.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/optoencoder2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/opto-encoder-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the OptoEncoder2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OptoEncoder2 Click driver.

#### Standard key functions :

- `optoencoder2_cfg_setup` Config Object Initialization function.
```c
void optoencoder2_cfg_setup ( optoencoder2_cfg_t *cfg ); 
```

- `optoencoder2_init` Initialization function.
```c
err_t optoencoder2_init ( optoencoder2_t *ctx, optoencoder2_cfg_t *cfg );
```

#### Example key functions :

- `optoencoder2_pwm_get` Getting PWM pin state
```c
uint8_t optoencoder2_pwm_get ( optoencoder2_t *ctx );
```

- `optoencoder2_int_get` Getting INT pin state
```c
uint8_t optoencoder2_int_get ( optoencoder2_t *ctx );
```

- `optoencoder2_get_position` Getting encoder position
```c
int32_t optoencoder2_get_position ( optoencoder2_t *ctx );
```

## Examples Description

> This application is used to encode motion or rotation.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver and resets encoder counter to 0 (zero).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    optoencoder2_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.
    optoencoder2_cfg_setup( &cfg );
    OPTOENCODER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    optoencoder2_init( &optoencoder2, &cfg );

    optoencoder2_zero_counter( &optoencoder2 );
}
  
```

### Application Task

> If motion is detected - encoder increments or decrements position on each rising edge on Channel A (INT pin) and logs encoder position.

```c

void application_task ( )
{
    int32_t encoder_position = 0;
    uint8_t stop_flag = 0;

    stop_flag = optoencoder2_isr( &optoencoder2, 100 );
    encoder_position = optoencoder2_get_position( &optoencoder2 );
    
    if ( stop_flag == 0 )
    {
        log_printf( &logger, "Position: %ld \r\n", encoder_position );
    }
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OptoEncoder2

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
