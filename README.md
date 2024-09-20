# Read me!

**This is just a playground repo to build a custom firmware for the GD32F303ZET6 MCU equipping the Parkside PMRA B2.
Do not use it :) !!**

---


## Background

To work with this repository, I installed the Keil Studio extension to VSCode.

At the time (July 2024), the GD32F30x_DFP CMSIS pack that is made available on ARM CMSIS database is not up to date. The only way to use the newest version (2.2.3 when writing those lines), is to download it from https://www.gd32mcu.com and install it.

To install it, you can, for instance, run: `cpackget add ~/Downloads/GD32F30x_AddOn_V2.2.3/GigaDevice.GD32F30x_DFP.2.2.3.pack`

There seemed to be a typo in the `gd32f30x_misc.c` file (l.105), `NVIC->IP` should be `NVIC->IPR`. I manually made the modification.

After all this, you can restart VSCode (that was the only way I found to get the CMSIS components listed in the CMSIS Panel)

To flash, you need to create a device in the "Device manager". Write `GigaDevice::GD32F30x_DFP@2.2.3` when you are prompted for the name of the pack.

## First try

Blink a LED!
It works using the debugger for now. Will introduce a delay function later.

## Some notes about code examples...

Some code example specific to the GD32F30x chip can be found on the official website's Downloads section (look for Firmware Library), so old versions are available at https://github.com/CommunityGD32Cores/gigadevice-firmware-and-docs/tree/main/GD32F30x also.

