
---
# Motion 4 Click

Motion 4 Click is a long distance PaPIR's motion sensor with plastic lense and controllable output. This Click board features EKMC1603111, a PIR motion sensor from Panasonic Corporation which can be used as human motion detector and is able to detect movement up to 12m with 170uA current consumption. Also featured on Motion 4 Click bord is TLP241A photorelay from Toshiba that is used to provide a reinforced galvanic isolation for the external signals used to drive some external high power electronic equipment when motion is detected. It's allowing up to 40V between the SSR contacts in OFF state, and currents up to 2A while in ON state, thanks to a very low ON-state resistance. Motion 4 Click board™ is supported by a mikroSDK compliant library, which includes functions that simplify software development. This Click board™ comes as a fully tested product, ready to be used on a system equipped with the mikroBUS™ socket.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/motion4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/motion-4-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Motion4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Motion4 Click driver.

#### Standard key functions :

- `motion4_cfg_setup` Config Object Initialization function.
```c
void motion4_cfg_setup ( motion4_cfg_t *cfg );
```

- `motion4_init` Initialization function.
```c
MOTION4_RETVAL motion4_init ( motion4_t *ctx, motion4_cfg_t *cfg );
```

#### Example key functions :

- `motion4_enable` This function enables/disables motion sensor by setting EN pin state.
```c
void motion4_enable ( motion4_t *ctx, uint8_t state );
```

- `motion4_detect_state` This function returns INT pin state.
```c
uint8_t motion4_detect_state ( motion4_t *ctx );
```

## Example Description

> This example demonstrates the use of Motion 4 Click boards.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the motion sensor.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    motion4_cfg_t motion4_cfg;  /**< Click config object. */

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

    motion4_cfg_setup( &motion4_cfg );
    MOTION4_MAP_MIKROBUS( motion4_cfg, MIKROBUS_1 );
    if ( motion4_init( &motion4, &motion4_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
       
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    motion4_enable( &motion4, MOTION4_MODULE_ENABLE );
    Delay_ms ( 100 );
    log_printf( &logger, "The sensor is ready.\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
}

```

### Application Task

> It checks if the sensor has detected movement and therefore displays the desired message on the USB UART.

```c

void application_task ( void ) {
    uint8_t int_status;

    int_status = motion4_detect_state( &motion4 );

    if ( int_status == MOTION4_DETECT_OBJECT ) {
        
        log_printf( &logger, "Motion detected!\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        while ( int_status == MOTION4_DETECT_OBJECT ) {
           
            int_status = motion4_detect_state( &motion4 );
        }
        log_printf( &logger, "The sensor is ready.\r\n" );
        log_printf( &logger, "-----------------------\r\n" );
        Delay_ms ( 100 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Motion4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
