/****************************************************************************
** Copyright (C) 2026 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

#include "invn/soniclib/chirp_bsp.h"
#include "invn/soniclib/ch_log.h"
#include "ultrasonic3.h"
#include "mcu.h"
#include "interrupts.h"

static ch_group_t *sensor_group_ptr = NULL;
static ultrasonic3_t *click_ptr = NULL;

// MCU CARD for STM32 STM32F407ZG
#ifdef STM32F4xx
void EXTI3_IRQHandler ( void ) 
{
    if ( EXTI->PR & EXTI_PR_PR3 ) 
    {
        EXTI->PR |= EXTI_PR_PR3;                    // Clear interrupt flag
        ch_interrupt ( sensor_group_ptr, 0 );
    }
}

void chbsp_ext_int_enable ( void )
{
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;           // Enable clock for SYSCFG

    SYSCFG->EXTICR[ 0 ] |= SYSCFG_EXTICR1_EXTI3_PD; // PD3 to EXTI3

    EXTI->RTSR &= ~EXTI_RTSR_TR3;                   // no rising
    EXTI->FTSR |= EXTI_FTSR_TR3;                    // falling trigger
    EXTI->IMR  |= EXTI_IMR_IM3;                     // Enable interrupt mask for EXTI3
    EXTI->PR   |= EXTI_PR_PR3;                      // Clear interrupt flag

    interrupt_enable( INTERRUPTS_EXTI3 );
}

void chbsp_ext_int_disable ( void )
{
    interrupt_disable( INTERRUPTS_EXTI3 );
}

// MCU CARD for Tiva TM4C129XNCZAD
#elif TM4C129
void GPIOB_IRQHandler ( void )
{
    if ( GPIO_PORTB_AHB_MIS_R & ( 1u << 4 ) )       // Interrupt active on PB4
    {
        GPIO_PORTB_AHB_ICR_R = ( 1u << 4 );         // W1C: clear PB4 flag
        ch_interrupt ( sensor_group_ptr, 0 );
    }
}

void chbsp_ext_int_enable ( void )
{
    GPIO_PORTB_AHB_IM_R   &= ~( 1u << 4 );          /* mask during config */
    GPIO_PORTB_AHB_IS_R   &= ~( 1u << 4 );          /* 0 = edge */
    GPIO_PORTB_AHB_IBE_R  &= ~( 1u << 4 );          /* 0 = single-edge */
    GPIO_PORTB_AHB_IEV_R  &= ~( 1u << 4 );          /* 0 = falling */

    GPIO_PORTB_AHB_ICR_R   =  ( 1u << 4 );          /* W1C */
    GPIO_PORTB_AHB_IM_R   |=  ( 1u << 4 );          /* unmask */
    
    interrupt_enable( INTERRUPTS_GPIOB );
}

void chbsp_ext_int_disable ( void )
{
    interrupt_disable( INTERRUPTS_GPIOB );
}

// MCU CARD for PIC32 PIC32MX795F512L
#elif PIC32MX795F512L
#include <sys/attribs.h>

void __ISR(_EXTERNAL_1_VECTOR, IPL4AUTO) INT1_ISR(void)
{
    IFS0CLR = _IFS0_INT1IF_MASK;                    // clear flag first (W1C)
    ch_interrupt ( sensor_group_ptr, 0 );
}

void chbsp_ext_int_enable ( void )
{
    // Multivector mode
    INTCONSET = _INTCON_MVEC_MASK;

    // INT1 falling edge: INT1EP = 0  (1=rising, 0=falling)
    INTCONCLR = _INTCON_INT1EP_MASK;                // make sure it's 0

    // Clear flag, set priority, enable
    IFS0CLR = _IFS0_INT1IF_MASK;
    IPC1CLR = _IPC1_INT1IP_MASK | _IPC1_INT1IS_MASK;
    IPC1SET = ( 4u << _IPC1_INT1IP_POSITION );      // priority 4
    interrupt_enable( INTERRUPTS_INT1 );
}

void chbsp_ext_int_disable ( void )
{
    interrupt_disable( INTERRUPTS_INT1 );
}
#else
    #error "External interrupt on INT pin is not configured for the selected setup."
#endif

void chbsp_init ( ch_group_t *grp_ptr, ultrasonic3_t *clk_ptr )
{
    // Make local copy of pointers
    sensor_group_ptr = grp_ptr;
    click_ptr = clk_ptr;
#ifdef STM32F4xx
    if ( click_ptr->int_pin_name != PD3 )
    {
        CH_LOG_APP ( "External interrupt on INT pin is not configured for the selected setup." );
        CH_LOG_APP ( "Check config and restart the system!" );
        for ( ; ; );
    }
#elif TM4C129
    if ( click_ptr->int_pin_name != PB4 )
    {
        CH_LOG_APP ( "External interrupt on INT pin is not configured for the selected setup." );
        CH_LOG_APP ( "Check config and restart the system!" );
        for ( ; ; );
    }
#elif PIC32MX795F512L
    if ( click_ptr->int_pin_name != PE8 )
    {
        CH_LOG_APP ( "External interrupt on INT pin is not configured for the selected setup." );
        CH_LOG_APP ( "Check config and restart the system!" );
        for ( ; ; );
    }
#endif
}

void chbsp_set_int1_dir_out ( ch_dev_t *dev_ptr )
{
    digital_out_init ( &click_ptr->int_pin_out, click_ptr->int_pin_name );
}

void chbsp_set_int1_dir_in ( ch_dev_t *dev_ptr )
{
    digital_in_init ( &click_ptr->int_pin_in, click_ptr->int_pin_name );
}

void chbsp_int1_clear ( ch_dev_t *dev_ptr )
{
    digital_out_low ( &click_ptr->int_pin_out );
}

void chbsp_int1_set ( ch_dev_t *dev_ptr )
{
    digital_out_high ( &click_ptr->int_pin_out );
}

void chbsp_int1_interrupt_enable ( ch_dev_t *dev_ptr )
{
    if ( ch_sensor_is_connected ( dev_ptr ) ) 
    {
        chbsp_set_int1_dir_in ( dev_ptr );
        chbsp_ext_int_enable ( );
    }
}

void chbsp_int1_interrupt_disable ( ch_dev_t *dev_ptr )
{
    if ( ch_sensor_is_connected ( dev_ptr ) )
    {
        chbsp_ext_int_disable ( );
    }
}

void chbsp_group_set_int1_dir_out ( ch_group_t *grp_ptr )
{
    chbsp_set_int1_dir_out ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_set_int1_dir_in ( ch_group_t *grp_ptr )
{
    chbsp_set_int1_dir_in ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int1_clear ( ch_group_t *grp_ptr )
{
    chbsp_int1_clear ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int1_set ( ch_group_t *grp_ptr )
{
    chbsp_int1_set ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int1_interrupt_enable ( ch_group_t *grp_ptr )
{
    chbsp_int1_interrupt_enable ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int1_interrupt_disable ( ch_group_t *grp_ptr )
{
    chbsp_int1_interrupt_disable ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_set_int2_dir_out ( ch_dev_t *dev_ptr )
{
    digital_out_init ( &click_ptr->int_pin_out, click_ptr->int_pin_name );
}

void chbsp_set_int2_dir_in ( ch_dev_t *dev_ptr )
{
    digital_in_init ( &click_ptr->int_pin_in, click_ptr->int_pin_name );
}

void chbsp_int2_clear ( ch_dev_t *dev_ptr )
{
    digital_out_low ( &click_ptr->int_pin_out );
}

void chbsp_int2_set ( ch_dev_t *dev_ptr )
{
    digital_out_high ( &click_ptr->int_pin_out );
}

void chbsp_int2_interrupt_enable ( ch_dev_t *dev_ptr )
{
    if ( ch_sensor_is_connected ( dev_ptr ) ) 
    {
        chbsp_set_int2_dir_in ( dev_ptr );
        chbsp_ext_int_enable ( );
    }
}

void chbsp_int2_interrupt_disable ( ch_dev_t *dev_ptr )
{
    if ( ch_sensor_is_connected ( dev_ptr ) )
    {
        chbsp_ext_int_disable ( );
    }
}

void chbsp_group_set_int2_dir_out ( ch_group_t *grp_ptr )
{
    chbsp_set_int2_dir_out ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_set_int2_dir_in ( ch_group_t *grp_ptr )
{
    chbsp_set_int2_dir_in ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int2_clear ( ch_group_t *grp_ptr )
{
    chbsp_int2_clear ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int2_set ( ch_group_t *grp_ptr )
{
    chbsp_int2_set ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int2_interrupt_enable ( ch_group_t *grp_ptr )
{
    chbsp_int2_interrupt_enable ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_group_int2_interrupt_disable ( ch_group_t *grp_ptr )
{
    chbsp_int2_interrupt_disable ( ch_get_dev_ptr ( grp_ptr, 0 ) );
}

void chbsp_spi_cs_on ( ch_dev_t *dev_ptr )
{
    spi_master_select_device ( click_ptr->chip_select );
}

void chbsp_spi_cs_off ( ch_dev_t *dev_ptr )
{
    spi_master_deselect_device ( click_ptr->chip_select );
}

int chbsp_spi_write ( ch_dev_t *dev_ptr, const uint8_t *data, uint16_t num_bytes )
{
    return spi_master_write ( &click_ptr->spi, data, num_bytes );
}

int chbsp_spi_read ( ch_dev_t *dev_ptr, uint8_t *data, uint16_t num_bytes )
{
    return spi_master_read ( &click_ptr->spi, data, num_bytes );
}

void chbsp_delay_us ( uint32_t us )
{
    Delay_us ( us );
}

void chbsp_delay_ms ( uint32_t ms )
{
    Delay_ms ( ms );
}

uint32_t chbsp_timestamp_ms ( void )
{
    return 0;
}
