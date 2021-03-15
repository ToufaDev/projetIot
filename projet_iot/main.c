/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Example application for demonstrating the RIOT network stack
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <lpsxxx.h>
#include <lpsxxx_params.h>
#include <lpsxxx_internal.h>

#include "shell.h"
#include "msg.h"
#include "xtimer.h"

#define MAIN_QUEUE_SIZE     (8)

int main(void)
{

  lpsxxx_t sensor;
  //tell sensor to sample with this rate  

  char data[32];
  int i, temp_abs;
  int16_t temp;
  int error = lpsxxx_init(&sensor, &lpsxxx_params[0]);

  puts("EOUHDUOFHUIDHFIUHSDUFHUIDHFIUH\n");
  if (error != LPSXXX_OK) {
    puts("error on lpsxxx_init\n");
    return -1;
  }
  puts("starting experiment....\n");
  for (i = 0; i < 10; i++)
    {
      xtimer_sleep(1);
      error = lpsxxx_read_temp(&sensor, &temp);
      if (error == LPSXXX_OK)
	{
	  temp_abs = temp / 100;
	  temp -= temp_abs * 100;
	  snprintf(data, 32, "temp : %2i.%02iC", temp_abs, temp);
	  data[31] = '\0';
	  puts(data);
	  puts("\n");
	}
      else {
	//puts("error when prompting sensor\n");
      }
    }

  puts("experiment over\n");  
  lpsxxx_disable(&sensor);
  return 0;
}
