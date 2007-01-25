/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/xgi/xgi_misc.h,v */

/****************************************************************************
 * Copyright (C) 2003-2006 by XGI Technology, Taiwan.						*
 *																			*
 * All Rights Reserved.														*
 *																			*
 * Permission is hereby granted, free of charge, to any person obtaining	*
 * a copy of this software and associated documentation files (the			*
 * "Software"), to deal in the Software without restriction, including		*
 * without limitation on the rights to use, copy, modify, merge,			*
 * publish, distribute, sublicense, and/or sell copies of the Software,		*
 * and to permit persons to whom the Software is furnished to do so,		*
 * subject to the following conditions:										*
 *																			*
 * The above copyright notice and this permission notice (including the		*
 * next paragraph) shall be included in all copies or substantial			*
 * portions of the Software.												*
 *																			*
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,			*
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF		*
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND					*
 * NON-INFRINGEMENT.  IN NO EVENT SHALL XGI AND/OR							*
 * ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,		*
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,		*
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER			*
 * DEALINGS IN THE SOFTWARE.												*
 ***************************************************************************/

#ifndef _XGI_MISC_H_
#define _XGI_MISC_H_

/* xgi_misc.c */
extern void XGIGetLcdSize(ScrnInfoPtr pScrn, CARD16 *lcdWidth, CARD16 *lcdHeight);
extern float XGICalculateMemoryClock(ScrnInfoPtr pScrn);
extern void XGIDumpRegisterValue(ScrnInfoPtr pScrn);

/* Jong 07/12/2006 */
extern void XGIDumpMemory(CARD8 *addr, unsigned long size);

extern Bool XGIPcieMemAllocate(ScrnInfoPtr pScrn,
                               unsigned long size,
                               unsigned long *pBufBusAddr,
                               unsigned long *pBufHWAddr,
                               unsigned long *pBufVirtAddr);
extern Bool XGIPcieMemFree(ScrnInfoPtr pScrn,
                           unsigned long size,
                           unsigned long bufBusAddr,
                           unsigned long bufHWAddr,
                           void          *pBufVirtAddr);
extern Bool  XGIShareAreaInfo(ScrnInfoPtr pScrn,
                             unsigned long busAddr,
                             unsigned long size);

#endif
