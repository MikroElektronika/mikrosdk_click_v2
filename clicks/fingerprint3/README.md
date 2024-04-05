\mainpage Main Page
 
---
# Fingerprint 3 click

Fingerprint 3 Click is an adapter Click board™, used to interface a compatible Fingerprint Sensor with Two-Color LED Ring with the host MCU.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fingerprint3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fingerprint-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Sep 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Fingerprint3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Fingerprint3 Click driver.

#### Standard key functions :

- `fingerprint3_cfg_setup` Config Object Initialization function.
```c
void fingerprint3_cfg_setup ( fingerprint3_cfg_t *cfg ); 
```

- `fingerprint3_init` Initialization function.
```c
err_t fingerprint3_init ( fingerprint3_t *ctx, fingerprint3_cfg_t *cfg );
```

- `fingerprint3_set_config` Set config function.
```c
uint8_t fingerprint3_set_config ( fingerprint3_t *ctx, uint32_t addr, uint32_t pass );
```

#### Example key functions :

- `fingerprint3_take_image` Take image function.
```c
uint8_t fingerprint3_take_image ( fingerprint3_t *ctx );
```

- `fingerprint3_aura_control` Aura LED control function.
```c
uint8_t fingerprint3_aura_control ( fingerprint3_t *ctx, uint8_t control, uint8_t speed, uint8_t color, uint8_t times );
```

- `fingerprint3_finger_indicator` Finger indicator function.
```c
uint8_t fingerprint3_finger_indicator ( fingerprint3_t *ctx );
```

## Examples Description

> This example reads and processes data from Fingerprint 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver, configures the sensor, and enrolls fingerprints.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    fingerprint3_cfg_t cfg;

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
    Delay_ms ( 100 );

    //  Click initialization.
    fingerprint3_cfg_setup( &cfg );
    FINGERPRINT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    err_t init_flag = fingerprint3_init( &fingerprint3, &cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    error_check = fingerprint3_set_config ( &fingerprint3, FINGERPRINT3_DEFAULT_ADDRESS, 
                                                           FINGERPRINT3_DEFAULT_PASSWORD );
    display_error( "Set Config" );
    Delay_ms ( 500 );
    
    error_check = fingerprint3_soft_reset ( &fingerprint3 );
    display_error( "Soft Reset" );
    Delay_ms ( 500 );
    
    error_check = fingerprint3_check_sensor ( &fingerprint3 );
    display_error( "Check Sensor" );
    Delay_ms ( 500 );
    
    error_check = fingerprint3_empty_library ( &fingerprint3 );
    display_error( "Empty the Library" );
    Delay_ms ( 500 );
    
    uint8_t cnt = 0; 
    do 
    {
        log_printf( &logger, " >>>  Register fingerprint %u of %u  <<<\r\n", ( uint16_t ) cnt + 1, 
                                                                             ( uint16_t ) NUMBER_OF_FINGERPRINTS );
        log_printf( &logger, "--------------------------------- \r\n" );
        error_check = enroll_finger ( &fingerprint3, LOCATION_IN_LIBRARY + cnt, NUMBER_OF_IMAGES );
        display_error( "Enroll finger" );
        if ( FINGERPRINT3_OK != error_check )
        {
            log_printf( &logger, " Please enroll your fingerprint again.\r\n" );
            log_printf( &logger, "--------------------------------- \r\n" );
        }
        else
        {
            cnt++;
        }
        Delay_ms ( 1000 );
    }
    while ( FINGERPRINT3_OK != error_check || cnt != NUMBER_OF_FINGERPRINTS );
}
  
```

### Application Task

> Takes an image of the finger, then checks if there's a fingerprint in the library that matches the
> one it has just read. All data is being logged on the USB UART.

```c

void application_task ( void )
{
    search_finger( &fingerprint3 );
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Fingerprint3

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
