# Notes to self (Newton):

QMK setup instructions: https://docs.qmk.fm/#/newbs_getting_started

 * keyboard name: keychron/q1_pro/ansi_knob (from `qmk list-keyboards`)
 * Q1 config: ~/personal/qmk/keyboards/keychron/q1/ansi_encoder/keymaps/newtonallen3
 * Iris config: ~/personal/qmk/keyboards/keebio/iris/keymaps/newtonallen3

References:

 * `qmk` CLI docs: https://github.com/qmk/qmk_firmware/blob/master/docs/cli_commands.md#qmk-flash
 * Help: Keychron discord (search "bluetooth_playground")
 * Factory firmware: https://github.com/Keychron/qmk_firmware/blob/bluetooth_playground/keyboards/keychron/q1_pro/firmware/keychron_q1_pro_ansi_knob_via.bin
 * RGB effects: https://docs.qmk.fm/#/feature_rgb_matrix?id=common-configuration
 * Key codes: https://docs.qmk.fm/#/keycodes

## Features added:

 * LED indicates current layer (solid color for each layer except base)
 * "Caps Word" feature triggered by pressing both Shifts

## One-time setup

```
python3 -m venv ~/.virtualenvs/qmk
source ~/.virtualenvs/qmk/bin/activate
python3 -m pip install --user qmk
qmk setup -H ~/personal/qmk newtonallen3/qmk_firmware

qmk compile -kb keychron/q1_pro/ansi_knob -km default
qmk config user.keyboard=keychron/q1_pro/ansi_knob
qmk config user.keymap=newtonallen3
qmk new-keymap
```

For picotool:

 - https://github.com/raspberrypi/picotool
 - https://jamesachambers.com/getting-started-guide-raspberry-pi-pico/

```
cd ~/personal
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init

cd ~/personal
git clone https://github.com/raspberrypi/picotool.git
sudo cp udev/99-picotool.rules /etc/udev/rules.d/
cd picotool
mkdir build
cd build
cmake -DPICO_SDK_PATH=../../pico-sdk ..
make
```

## Editing

Files of interest are under `keyboards/keychron/q1_pro/ansi_knob`, e.g.

```
vim ~/personal/qmk/keyboards/keychron/q1_pro/ansi_knob/keymaps/newtonallen3/keymap.c
```

## Compiling and flashing

Tip: to enter the bootloader, switch keyboard to off, then hold escape while plugging it back in.

(This is the [Bootmagic Lite](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_bootmagic.md) feature at work! No need for the complicated steps on Keychron's website: https://www.keychron.com/blogs/archived/how-to-reset-your-keychron-q1-to-factory-settings.)

For the Iris keyboard, to enter the bootloader, press the reset button on the bottom for 1 second.

```
source ~/.virtualenvs/qmk/bin/activate
qmk compile -kb keychron/q1_pro/ansi_knob -km newtonallen3
qmk flash

qmk compile -kb keebio/iris/rev8 -km newtonallen3 && \
~/personal/picotool/build/picotool load -x ~/personal/qmk/keebio_iris_rev8_newtonallen3.uf2
```

## Troubleshooting - can't mount RP2040 as a writable disk, so qmk flash fails

Workaround: Use picotool for flashing:

```
picotool load -x ~/personal/qmk/keebio_iris_rev8_newtonallen3.uf2
```

Instructions for building picotool: https://jamesachambers.com/getting-started-guide-raspberry-pi-pico/

Discarded alternative: use dd instead of mounting the device as a pseudo writable filesystem.
https://www.reddit.com/r/raspberrypipico/comments/l4rhvi/psa_you_can_also_use_dd_for_uploading_new_images

Downside: this doesn't provide feedback in case of problems (e.g. not in bootsel mode), and never
seemed to work for me.

```
FIRMWARE=~/personal/qmk/keebio_iris_rev8_newtonallen3.uf2
sudo dd if="$FIRMWARE" of=/dev/sda1 bs="$(stat --printf="%s" "$FIRMWARE")"
# Better alternative to sda1? /dev/disk/by-id/usb-RPI_RP2_E0C9125B0D9B-0:0-part1
```

## Troubleshooting flashing (fixed)

Problem: doesn't recognize device.

`lsusb` confirms that device is attached. `dfs-util --list` even showed the keyboard and allowed me to "upload" the firmware from the keyboard to my computer.

```
(qmk) 04:09:59 newt-glaptop2 ~/personal/qmk qmk doctor
Ψ QMK Doctor is checking your environment.
Ψ CLI version: 1.1.2
Ψ QMK home: /home/newt/personal/qmk
Ψ Detected Linux (Debian GNU/Linux rodete).
⚠ Missing or outdated udev rules for 'atmel-dfu' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'kiibohd' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'stm32-dfu' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'apm32-dfu' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'gd32v-dfu' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'bootloadhid' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'usbasploader' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'usbtinyisp' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'md-boot' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'caterina' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
⚠ Missing or outdated udev rules for 'hid-bootloader' boards. Run 'sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/'.
```

Ran:

```
sudo cp /home/newt/personal/qmk/util/udev/50-qmk.rules /etc/udev/rules.d/
sudo chmod +r /etc/udev/rules.d/50-qmk.rules
sudo udevadm control --reload-rules && sudo udevadm trigger
```

Hypothesis: I'm building firmware for the wrong keyboard... the Q1 instead of the Q1 Pro.

Fix: Grab correct firmware from separate Github branch: "bluetooth_playground": https://www.reddit.com/r/Keychron/comments/13l321j/q1_pro_flashing_with_qmk/

Success!

## Troubleshooting - can't use Via with custom flash

Need to use Via v3 keyboard definition:
https://github.com/the-via/keyboards/blob/4f64a385c87b3738c955ec03339d56da26bd721c/v3/keychron/q1_pro/ansi_rgb_knob.json
(not yet merged into Via's main branch). Upload this in the design tab in usevia.app.

Now getting these errors:

```
07:00:07.394
The device must be opened first.
Device: Keychron Keychron Q1 Pro
Vid: 0x3434
Pid: 0x0610

07:00:07.413
Received invalid protocol version from device
Device: Keychron Keychron Q1 Pro
Vid: 0x3434
Pid: 0x0610
```

## TODO

 - Fix accidental mod taps with "a" key. Maybe increase hold time for this key?
 - Fix Alt+Tab layer (need the layer to have alt held; separate this out from tab switching/moving layer)
 - Disable LED effects by default (save power)? https://docs.qmk.fm/#/feature_rgb_matrix?id=indicators-without-rgb-matrix-effect
 - Layer for customizing LED effects
 - Try "bilateral combinations" if/when they're available to help avoid home row mod accidental holds: https://github.com/manna-harbour/qmk_firmware/blob/bilateral-combinations/docs/tap_hold.md#bilateral-combinations
    * The following bigrams are especially commonly triggered: at (Windows+T), kn (Ctrl+N)
    * Could also try adjusting TAPPING_TERM: https://docs.qmk.fm/#/tap_hold?id=dynamic-tapping-term
    * Or could try Combo Mods: https://jasoncarloscox.com/blog/combo-mods/
    * Or try Achordion: https://getreuer.info/posts/keyboards/achordion/index.html
