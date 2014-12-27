//
// arch/x86_64/rsp/vabs.s
//
// CEN64: Cycle-Accurate Nintendo 64 Simulator.
// Copyright (C) 2014, Tyler J. Stachecki.
//
// This file is subject to the terms and conditions defined in
// 'LICENSE', which is part of this source code package.
//

#
# xmm0 = vs
# xmm1 = vt
# xmm5 = acc_lo
#

.global RSP_VABS
.type	RSP_VABS, @function

RSP_VABS:

.ifdef __AVX__
  vpsraw $0xf, %xmm0, %xmm3
  vpxor %xmm3, %xmm1, %xmm2
  vpsubsw %xmm3, %xmm2, %xmm2
  vpsignw %xmm0, %xmm1, %xmm5
  vpblendvb %xmm3, %xmm2, %xmm5, %xmm0
  retq
.else
  movdqa %xmm0, %xmm3
  pcmpeqw %xmm2, %xmm0
  psraw $0xF, %xmm3
  pandn %xmm1, %xmm0
  pxor %xmm3, %xmm0
  movdqa %xmm0, %xmm5
  psubsw %xmm3, %xmm0
  psubw %xmm3, %xmm5
  retq
.endif

.size RSP_VABS,.-RSP_VABS

