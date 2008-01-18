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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "fbdevhw.h"

#include "xgi.h"
#include "xgi_regs.h"
#include "xgi_mode.h"
#include "xg47_mode.h"

#ifndef NATIVE_MODE_SETTING
void XGIModeSave(ScrnInfoPtr pScrn, XGIRegPtr pXGIReg)
{
    XGIPtr  pXGI = XGIPTR(pScrn);

    switch (pXGI->chipset)
    {
    case XG47:
        XG47ModeSave(pScrn, pXGIReg);
        break;
    default:
        break;
    }
}

void XGIModeRestore(ScrnInfoPtr pScrn, XGIRegPtr pXGIReg)
{
    XGIPtr  pXGI = XGIPTR(pScrn);

    switch (pXGI->chipset)
    {
    case XG47:
        XG47ModeRestore(pScrn, pXGIReg);
        break;
    default:
        break;
    }
}
#endif

void XGILoadPalette(ScrnInfoPtr pScrn, int numColors, int *indicies,
                    LOCO *colors, VisualPtr pVisual)
{
    XGIPtr   pXGI = XGIPTR(pScrn);

    if (pXGI->isFBDev)
    {
	    fbdevHWLoadPalette(pScrn, numColors, indicies, colors, pVisual);
	    return;
    }

    switch (pXGI->chipset)
    {
    case XG47:
        XG47LoadPalette(pScrn, numColors, indicies, colors, pVisual);
        break;
    default:
        break;
    }
}

void XGISetOverscan(ScrnInfoPtr pScrn, int overscan)
{
    XGIPtr pXGI = XGIPTR(pScrn);

    switch(pXGI->chipset)
    {
    case XG47:
        XG47SetOverscan(pScrn, overscan);
        break;
    default:
        break;
    }
}
