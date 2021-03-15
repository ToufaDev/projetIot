/*
 * Copyright (C) 2014 Freie Universität Berlin
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
 * @brief       Hello World application
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Ludwig Knüpfer <ludwig.knuepfer@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include <phydat.h>
#include <saul.h>

int main(void)
{
  phydat_t res;
  int nb;
  saul_init_devs();
  nb = saul_read_t(SAUL_SENSE_TEMP, &res);
  printf("err : %d", err);
  puts("Hello World!");
  
  printf("You are running RIOT on a(n) %s board.\n", RIOT_BOARD);
  printf("This board features a(n) %s MCU.\n", RIOT_MCU);
  printf("Temp %hn, %d, %d\n", res.val, res.unit, res.scale);
  return 0;
}
