
---
# Motion 2 click

Motion 2 Click is a Click board™ based on EKMC1607112, PIR motion sensor from Panasonic Corporation that's used as human motion detector. Also featured on Motion 2 Click bord is TLP241A photorelay from Toshiba that is used to provide a reinforced galvanic isolation for the external signals used to drive some external high power electronic equipment when motion is detected. It's allowing up to 40V between the SSR contacts in OFF state, and currents up to 2A while in ON state, thanks to a very low ON-state resistance.
Motion 2 Click board™ is supported by a mikroSDK compliant library, which includes functions that simplify software development. This Click board™ comes as a fully tested product, ready to be used on a system equipped with the mikroBUS™ socket.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/motion2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/motion-2-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Motion2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Motion2 Click driver.

#### Standard key functions :

- `motion2_cfg_setup` Config Object Initialization function.
```c
void motion2_cfg_setup ( motion2_cfg_t *cfg );
```

- `motion2_init` Initialization function.
```c
motion2_return_value_t motion2_init ( motion2_t *ctx, motion2_cfg_t *cfg );
```

#### Example key functions :

- `motion2_enable` Enable motion sensor function.
```c
void motion2_enable ( motion2_t *ctx, uint8_t state );
```

- `motion2_detect_state` Get detection state function.
```c
uint8_t motion2_detect_state ( motion2_t *ctx );
```

## Example Description

> This example demonstrates the use of Motion 2 click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the motion sensor.

```c

void application_init ( void ) {
   
    log_cfg_t log_cfg;  /**< Logger config object. */
    motion2_cfg_t motion2_cfg;  /**< Click config object. */

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

    // Click initialization.

    motion2_cfg_setup( &motion2_cfg );
    MOTION2_MAP_MIKROBUS( motion2_cfg, MIKROBUS_1 );
    if ( motion2_init( &motion2, &motion2_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    motion2_enable( &motion2, MOTION2_MODULE_ENABLE );
    Delay_ms( 100 );
    log_printf( &logger, "The sensor is ready.\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

```

### Application Task

> It checks if the sensor has detected movement and therefore displays the desired message on the USB UART.

```c

void application_task ( void ) {  
    uint8_t int_status;

    int_status = motion2_detect_state( &motion2 );

    if ( int_status == MOTION2_DETECT_OBJECT ) {
        log_printf( &logger, "Motion detected!\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        while ( int_status == MOTION2_DETECT_OBJECT ) {
            int_status = motion2_detect_state( &motion2 );
        }
        log_printf( &logger, "The sensor is ready.\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms( 100 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
