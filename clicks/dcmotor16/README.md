\mainpage Main Page

---
# DC Motor 16 click

> DC Motor 16 Click is a compact add-on board that contains a high-performance single phase reversible DC motor drive with speed control. This board features the ZXBM5210, a fully-featured DC motor drive solution with an average current capability of up to 700mA from Diodes Incorporated. The ZXBM5210 has several modes of operations selected by two GPIO pins, has a wide supply voltage range from 3V to 18V, and low power consumption.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/dcmotor16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/dc-motor-16-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the DCMotor16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DCMotor16 Click driver.

#### Standard key functions :

- `dcmotor16_cfg_setup` Config Object Initialization function.
```c
void dcmotor16_cfg_setup ( dcmotor16_cfg_t *cfg );
```

- `dcmotor16_init` Initialization function.
```c
err_t dcmotor16_init ( dcmotor16_t *ctx, dcmotor16_cfg_t *cfg );
```

#### Example key functions :

- `dcmotor16_set_direction` Set motor direction.
```c
void dcmotor16_set_direction( dcmotor16_t *ctx, uint8_t dir );
```

- `dcmotor16_ctrl_vref` Control motor VRef (speed).
```c
void dcmotor16_ctrl_vref( dcmotor16_t *ctx, uint16_t value );
```

- `dcmotor16_stop` Motor stop.
```c
void dcmotor16_stop( dcmotor16_t *ctx );
```

## Example Description

> This example shows the capabilities of the DC Motor 16 click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver init.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor16_cfg_t dcmotor16_cfg;  /**< Click config object. */

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

    dcmotor16_cfg_setup( &dcmotor16_cfg );
    DCMOTOR16_MAP_MIKROBUS( dcmotor16_cfg, MIKROBUS_1 );
    err_t init_flag  = dcmotor16_init( &dcmotor16, &dcmotor16_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Start motor example with change in motor direction and speed.

```c

void application_task ( void ) {
    uint16_t cnt;
    
    log_printf( &logger, ">> Motor start with direction [FORWARD] <<\r\n" );
    dcmotor16_set_direction( &dcmotor16, DCMOTOR16_DIR_FORWARD );
    for( cnt = 0; cnt <= 0x0100; cnt+= 25 ) {
        dcmotor16_ctrl_vref( &dcmotor16, cnt );
        Delay_ms( 250 );
    }
    Delay_ms( 2000 );
    
    log_printf( &logger, ">> Motor stop \r\n" );
    dcmotor16_stop( &dcmotor16 );
    Delay_ms( 1000 );
    
    log_printf( &logger, ">> Motor start with direction [BACKWARD] <<\r\n" );
    dcmotor16_set_direction( &dcmotor16, DCMOTOR16_DIR_BACKWARD );
    for( cnt = 0; cnt <= 0x0100; cnt+= 25 ) {
        dcmotor16_ctrl_vref( &dcmotor16, cnt );
        Delay_ms( 250 );
    }
    Delay_ms( 2000 );
    
    log_printf( &logger, ">> Motor stop \r\n" );
    dcmotor16_stop( &dcmotor16 );
    Delay_ms( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DCMotor16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
