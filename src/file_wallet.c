/*

    File: file_wallet.c

    Copyright (C) 2013 Christophe GRENIER <grenier@cgsecurity.org>
  
    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
  
    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */

#if !defined(SINGLE_FORMAT) || defined(SINGLE_FORMAT_wallet)
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#include <stdio.h>
#include "types.h"
#include "filegen.h"

/*@ requires \valid(file_stat); */
static void register_header_check_wallet(file_stat_t *file_stat);

const file_hint_t file_hint_wallet = {
  .extension = "wallet",
  .description = "Armory bitcoin wallet",
  .max_filesize = 10 * 1024 * 1024,
  .recover = 1,
  .enable_by_default = 1,
  .register_header_check = &register_header_check_wallet
};

/*@
  @ requires buffer_size > 0;
  @ requires \valid_read(buffer+(0..buffer_size-1));
  @ requires valid_file_recovery(file_recovery);
  @ requires \valid(file_recovery_new);
  @ requires file_recovery_new->blocksize > 0;
  @ requires separation: \separated(&file_hint_wallet, buffer+(..), file_recovery, file_recovery_new);
  @ assigns  *file_recovery_new;
  @ ensures  \result!=0 ==> valid_file_recovery(file_recovery_new);
  @*/
static int header_check_wallet(const unsigned char *buffer, const unsigned int buffer_size, const unsigned int safe_header_only, const file_recovery_t *file_recovery, file_recovery_t *file_recovery_new)
{
  reset_file_recovery(file_recovery_new);
  file_recovery_new->extension = file_hint_wallet.extension;
  return 1;
}

static void register_header_check_wallet(file_stat_t *file_stat)
{
  static const unsigned char wallet_header[8] = {
    0xba, 'W', 'A', 'L', 'L', 'E', 'T', 0x00
  };
  register_header_check(0, wallet_header, sizeof(wallet_header), &header_check_wallet, file_stat);
}
#endif
