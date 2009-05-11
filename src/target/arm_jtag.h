/***************************************************************************
 *   Copyright (C) 2005 by Dominic Rath                                    *
 *   Dominic.Rath@gmx.de                                                   *
 *                                                                         *
 *   Copyright (C) 2007,2008 �yvind Harboe                                 *
 *   oyvind.harboe@zylin.com                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef ARM_JTAG
#define ARM_JTAG

#include "jtag.h"

typedef struct arm_jtag_s
{
	jtag_tap_t *tap;

	u32 scann_size;
	u32 scann_instr;
	u32 cur_scan_chain;

	u32 intest_instr;
} arm_jtag_t;

extern int arm_jtag_set_instr(arm_jtag_t *jtag_info, u32 new_instr, void *verify_capture);
extern int arm_jtag_scann(arm_jtag_t *jtag_info, u32 new_scan_chain);
extern int arm_jtag_setup_connection(arm_jtag_t *jtag_info);

/* JTAG buffers to host, be and le buffers, flipping variants */
int arm_jtag_buf_to_u32_flip(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_le32_flip(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_le16_flip(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_be32_flip(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_be16_flip(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_8_flip(u8 *in_buf, void *priv, struct scan_field_s *field);

/* JTAG buffers to host, be and le buffers */
int arm_jtag_buf_to_u32(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_le32(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_le16(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_be32(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_be16(u8 *in_buf, void *priv, struct scan_field_s *field);
int arm_jtag_buf_to_8(u8 *in_buf, void *priv, struct scan_field_s *field);


/* use this as a static so we can inline it in -O3 and refer to it via a pointer  */
static __inline__ void arm7flip32(u8 *in)
{
	*((u32 *)in)=flip_u32(le_to_h_u32(in), 32);
}

static __inline__ void arm_le_to_h_u32(u8 *in)
{
	*((u32 *)in)=le_to_h_u32(in);
}


#endif /* ARM_JTAG */

