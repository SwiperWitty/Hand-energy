/**
  **************************************************************************
  * @file     main.c
  * @version  v2.0.7
  * @date     2022-08-16
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f415_board.h"
#include "at32f415_clock.h"


/** @addtogroup AT32F415_periph_examples
  * @{
  */

/** @addtogroup 415_PWC_power_voltage_monitor PWC_power_voltage_monitor
  * @{
  */


/**
  * @brief  power voltage monitor exint configuration.
  * @param  none
  * @retval none
  */
void pvm_exint_config(void)
{
  exint_init_type exint_init_struct;

  /* config the exint line of the power voltage monitor */
  exint_init_struct.line_select = EXINT_LINE_16;
  exint_init_struct.line_enable = TRUE;
  exint_init_struct.line_mode = EXINT_LINE_INTERRUPUT;
  exint_init_struct.line_polarity = EXINT_TRIGGER_BOTH_EDGE;
  exint_init(&exint_init_struct);
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  __IO uint32_t index = 0;

  /* congfig the system clock */
  system_clock_config();

  /* init at start board */
  at32_board_init();

  /* config priority group */
  nvic_priority_group_config(NVIC_PRIORITY_GROUP_4);

  /* turn on the led light */
  at32_led_on(LED2);
  at32_led_on(LED3);
  at32_led_on(LED4);

  /* enable pwc clock */
  crm_periph_clock_enable(CRM_PWC_PERIPH_CLOCK, TRUE);

  /* set the threshold voltage to 2.9v */
  pwc_pvm_level_select(PWC_PVM_VOLTAGE_2V9);

  /* enable power voltage monitor */
  pwc_power_voltage_monitor_enable(TRUE);

  /* config the exint line of the power voltage monitor */
  pvm_exint_config();

  /* when power voltage monitor enable,exint line16 flag will be set */
  while(exint_flag_get(EXINT_LINE_16) == RESET);

  /* clear the unexpected exint line flag */
  exint_flag_clear(EXINT_LINE_16);

  /* clear the unexpected nvic pending flag */
  NVIC_ClearPendingIRQ(PVM_IRQn);

  /* enable power voltage monitor interrupt */
  nvic_irq_enable(PVM_IRQn, 0, 0);

  while(1)
  {
  }
}

/**
  * @}
  */

/**
  * @}
  */
