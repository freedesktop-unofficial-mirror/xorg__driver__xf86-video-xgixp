/*
 * Copyright (C) 2003-2006 by XGI Technology, Taiwan.
 * (c) Copyright IBM Corporation 2008
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "xf86.h"
#include "xf86PciInfo.h"
#include <xf86i2c.h>
#include <xf86Crtc.h>

#include "xgi.h"
#include "xgi_regs.h"

struct xg47_crtc_private {
    I2CBusPtr    pI2C;
};


static int xg47_output_mode_valid(xf86OutputPtr output, DisplayModePtr mode);

static Bool xg47_output_mode_fixup(xf86OutputPtr output, DisplayModePtr mode,
    DisplayModePtr adjusted_mode);

static void xg47_output_prepare(xf86OutputPtr output);

static void xg47_output_commit(xf86OutputPtr output);

static void xg47_output_mode_set(xf86OutputPtr output, DisplayModePtr mode,
    DisplayModePtr adjusted_mode);

static void xg47_vga_dpms(xf86OutputPtr output, int mode);
static void xg47_dvi_dpms(xf86OutputPtr output, int mode);

static xf86OutputStatus xg47_output_detect(xf86OutputPtr output);

static void xg47_output_save(xf86OutputPtr output);

static void xg47_output_restore(xf86OutputPtr output);

static void xg47_output_destroy(xf86OutputPtr output);

static DisplayModePtr xg47_output_get_modes(xf86OutputPtr output);

static xf86OutputPtr xg47_OutputDac1Init(ScrnInfoPtr scrn, Bool primary);

static xf86OutputPtr xg47_OutputDac2Init(ScrnInfoPtr scrn);

static const xf86OutputFuncsRec xg47_vga_funcs = {
    .dpms = xg47_vga_dpms,
    .save = xg47_output_save,
    .restore = xg47_output_restore,
    .mode_valid = xg47_output_mode_valid,
    .mode_fixup = xg47_output_mode_fixup,
    .prepare = xg47_output_prepare,
    .mode_set = xg47_output_mode_set,
    .commit = xg47_output_commit,
    .detect = xg47_output_detect,
    .get_modes = xg47_output_get_modes,
    .destroy = xg47_output_destroy
};


static const xf86OutputFuncsRec xg47_dvi_funcs = {
    .dpms = xg47_dvi_dpms,
    .save = xg47_output_save,
    .restore = xg47_output_restore,
    .mode_valid = xg47_output_mode_valid,
    .mode_fixup = xg47_output_mode_fixup,
    .prepare = xg47_output_prepare,
    .mode_set = xg47_output_mode_set,
    .commit = xg47_output_commit,
    .detect = xg47_output_detect,
    .get_modes = xg47_output_get_modes,
    .destroy = xg47_output_destroy
};


void
xg47_vga_dpms(xf86OutputPtr output, int mode)
{
    ScrnInfoPtr pScrn = output->scrn;
    XGIPtr  pXGI = XGIPTR(pScrn);


    if (pXGI->isFBDev) {
        fbdevHWDPMSSet(pScrn, mode, 0);
    } else if (pXGI->pVbe) {
        /* I don't know if the bug is in XGI's BIOS or in VBEDPMSSet, but
         * cx must be set to 0 here, or the mode will not be set.
         */
        pXGI->pInt10->cx = 0x0000;
        VBEDPMSSet(pXGI->pVbe, mode);
    } else {
        const uint8_t power_status = (IN3CFB(0x23) & ~0x03) 
            | (mode);
        const uint8_t pm_ctrl = (IN3C5B(0x24) & ~0x01)
            | ((mode == DPMSModeOn) ? 0x01 : 0x00);


        OUT3CFB(0x23, power_status);
        OUT3C5B(0x24, pm_ctrl);
    }
}


void
xg47_dvi_dpms(xf86OutputPtr output, int mode)
{
    ScrnInfoPtr pScrn = output->scrn;
    XGIPtr  pXGI = XGIPTR(pScrn);


    const uint8_t power_status = (IN3CFB(0x26) & ~0x30) 
	| (mode << 4);
        const uint8_t pm_ctrl = (IN3CFB(0x3d) & ~0x01)
            | ((mode == DPMSModeOn) ? 0x01 : 0x00);


    OUT3CFB(0x26, power_status);
    OUT3CFB(0x3d, pm_ctrl);
}


xf86OutputStatus
xg47_output_detect(xf86OutputPtr output)
{
    struct xg47_crtc_private *xg47_output = 
	(struct xg47_crtc_private *) output->driver_private;

    return (xf86I2CProbeAddress(xg47_output->pI2C, 0xA0)) 
        ? XF86OutputStatusConnected : XF86OutputStatusUnknown;
}


int
xg47_output_mode_valid(xf86OutputPtr output, DisplayModePtr mode)
{
    return MODE_OK;
}


Bool
xg47_output_mode_fixup(xf86OutputPtr output, DisplayModePtr mode,
                       DisplayModePtr adjusted_mode)
{
    return TRUE;
}


void
xg47_output_prepare(xf86OutputPtr output)
{
    output->funcs->dpms(output, DPMSModeOff);
}


void
xg47_output_commit(xf86OutputPtr output)
{
    output->funcs->dpms(output, DPMSModeOn);
}


void
xg47_output_mode_set(xf86OutputPtr output, DisplayModePtr mode,
                     DisplayModePtr adjusted_mode)
{
}


void
xg47_output_save(xf86OutputPtr output)
{
}


void
xg47_output_restore(xf86OutputPtr output)
{
}


void
xg47_output_destroy(xf86OutputPtr output)
{
    /* No private data yet, so this function doesn't need to do anything.
     */
}


static DisplayModePtr
xg47_output_get_modes(xf86OutputPtr output)
{
    XGIPtr  pXGI = XGIPTR(output->scrn);
    struct xg47_crtc_private *xg47_output = 
	(struct xg47_crtc_private *) output->driver_private;
    xf86MonPtr mon;

    mon = xf86OutputGetEDID(output, xg47_output->pI2C);
    xf86OutputSetEDID(output, mon);

    return xf86OutputGetEDIDModes(output);
}


/**
 */
xf86OutputPtr
xg47_OutputDac1Init(ScrnInfoPtr scrn, Bool primary)
{
    XGIPtr pXGI = XGIPTR(scrn);
    xf86OutputPtr output;
    struct xg47_crtc_private *xg47_output;
    const char *const name = (primary) ? "VGA" : "VGA1";


    output = xf86OutputCreate(scrn, &xg47_vga_funcs, name);
    if (!output) {
        return NULL;
    }

    xg47_output = xnfcalloc(sizeof(*xg47_output), 1);
    xg47_output->pI2C = pXGI->pI2C;

    output->driver_private = xg47_output;
    return output;
}


/**
 */
xf86OutputPtr
xg47_OutputDac2Init(ScrnInfoPtr scrn)
{
    XGIPtr pXGI = XGIPTR(scrn);
    xf86OutputPtr output;
    struct xg47_crtc_private *xg47_output;


    output = xf86OutputCreate(scrn, &xg47_dvi_funcs, "DVI");
    if (!output) {
        return NULL;
    }

    xg47_output = xnfcalloc(sizeof(*xg47_output), 1);
    xg47_output->pI2C = pXGI->pI2C_dvi;

    output->driver_private = xg47_output;
    return output;
}


void
xg47_PreInitOutputs(ScrnInfoPtr scrn)
{
    xf86OutputPtr output;

    output = xg47_OutputDac1Init(scrn, TRUE);
    if (output != NULL) {
        output->possible_crtcs = 0x01;
    }

    output = xg47_OutputDac2Init(scrn);
    if (output != NULL) {
        output->possible_crtcs = 0x01;
    }
}
