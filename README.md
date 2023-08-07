# Notes to self (Newton):

QMK setup instructions: https://docs.qmk.fm/#/newbs_getting_started

 * keyboard name: keychron/q1_pro/ansi_knob (from `qmk list-keyboards`)
 * config: ~/personal/qmk/keyboards/keychron/q1/ansi_encoder/keymaps/newtonallen3

References:

 * `qmk` CLI docs: https://github.com/qmk/qmk_firmware/blob/master/docs/cli_commands.md#qmk-flash
 * Help: Keychron discord (search "bluetooth_playground")
 * Factory firmware: https://github.com/Keychron/qmk_firmware/blob/bluetooth_playground/keyboards/keychron/q1_pro/firmware/keychron_q1_pro_ansi_knob_via.bin

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

## Editing

```
vim ~/personal/qmk_keychron/keyboards/keychron/q1_pro/ansi_knob/keymaps/newtonallen3/keymap.c
```

## Compiling and flashing

Tip: to enter the bootloader, unplug keyboard, then hold escape while plugging it back in. ... not quite working yet....

(This is the [Bootmagic Lite](https://github.com/qmk/qmk_firmware/blob/master/docs/feature_bootmagic.md) feature at work! No need for the complicated steps on Keychron's website: https://www.keychron.com/blogs/archived/how-to-reset-your-keychron-q1-to-factory-settings.)

```
source ~/.virtualenvs/qmk/bin/activate
qmk compile -kb keychron/q1_pro/ansi_knob -km newtonallen3
qmk flash
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
