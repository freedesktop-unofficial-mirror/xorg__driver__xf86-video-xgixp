/***************************************************************************
 * Copyright (C) 2003-2006 by XGI Technology, Taiwan.			   *
 *									   *
 * All Rights Reserved.							   *
 *									   *
 * Permission is hereby granted, free of charge, to any person obtaining   *
 * a copy of this software and associated documentation files (the	   *
 * "Software"), to deal in the Software without restriction, including	   *
 * without limitation on the rights to use, copy, modify, merge,	   *
 * publish, distribute, sublicense, and/or sell copies of the Software,	   *
 * and to permit persons to whom the Software is furnished to do so,	   *
 * subject to the following conditions:					   *
 *									   *
 * The above copyright notice and this permission notice (including the	   *
 * next paragraph) shall be included in all copies or substantial	   *
 * portions of the Software.						   *
 *									   *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,	   *
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF	   *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND		   *
 * NON-INFRINGEMENT.  IN NO EVENT SHALL XGI AND/OR			   *
 * ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,	   *
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,	   *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER	   *
 * DEALINGS IN THE SOFTWARE.						   *
 ***************************************************************************/

#ifndef _XGI_SHADOW_H_
#define _XGI_SHADOW_H_

/* xgi_shadow.c */
extern void XGIRefreshArea(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
extern void XGIShadowUpdate (ScreenPtr pScreen, shadowBufPtr pBuf);
extern void XGIPointerMoved(int index, int x, int y);
extern void XGIRefreshArea8(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
extern void XGIRefreshArea16(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
extern void XGIRefreshArea24(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
extern void XGIRefreshArea32(ScrnInfoPtr pScrn, int num, BoxPtr pbox);

#endif
