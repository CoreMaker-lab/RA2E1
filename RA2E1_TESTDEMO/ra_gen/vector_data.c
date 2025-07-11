/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [1] = ctsu_write_isr, /* CTSU WRITE (Write request interrupt) */
            [2] = ctsu_read_isr, /* CTSU READ (Measurement data transfer request interrupt) */
            [3] = ctsu_end_isr, /* CTSU END (Measurement end interrupt) */
            [4] = sci_uart_rxi_isr, /* SCI9 RXI (Receive data full) */
            [5] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [6] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [7] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [9] = rtc_alarm_periodic_isr, /* RTC ALARM (Alarm interrupt) */
            [10] = rtc_alarm_periodic_isr, /* RTC PERIOD (Periodic interrupt) */
            [11] = rtc_carry_isr, /* RTC CARRY (Carry interrupt) */
        };
        #if BSP_FEATURE_ICU_HAS_IELSR
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [1] = BSP_PRV_VECT_ENUM(EVENT_CTSU_WRITE,GROUP1), /* CTSU WRITE (Write request interrupt) */
            [2] = BSP_PRV_VECT_ENUM(EVENT_CTSU_READ,GROUP2), /* CTSU READ (Measurement data transfer request interrupt) */
            [3] = BSP_PRV_VECT_ENUM(EVENT_CTSU_END,GROUP3), /* CTSU END (Measurement end interrupt) */
            [4] = BSP_PRV_VECT_ENUM(EVENT_SCI9_RXI,GROUP4), /* SCI9 RXI (Receive data full) */
            [5] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TXI,GROUP5), /* SCI9 TXI (Transmit data empty) */
            [6] = BSP_PRV_VECT_ENUM(EVENT_SCI9_TEI,GROUP6), /* SCI9 TEI (Transmit end) */
            [7] = BSP_PRV_VECT_ENUM(EVENT_SCI9_ERI,GROUP7), /* SCI9 ERI (Receive error) */
            [9] = BSP_PRV_VECT_ENUM(EVENT_RTC_ALARM,GROUP1), /* RTC ALARM (Alarm interrupt) */
            [10] = BSP_PRV_VECT_ENUM(EVENT_RTC_PERIOD,GROUP2), /* RTC PERIOD (Periodic interrupt) */
            [11] = BSP_PRV_VECT_ENUM(EVENT_RTC_CARRY,GROUP3), /* RTC CARRY (Carry interrupt) */
        };
        #endif
        #endif
