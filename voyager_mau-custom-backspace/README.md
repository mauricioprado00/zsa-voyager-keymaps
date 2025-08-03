This is a QMK configuration for the ZSA Voyager.
Unfortunatelly Oryx doesn't allow much customization when it comes to multi function keys, and they cannot be individually tunned.

This does something quite similar to what the `Hold On Other Key Press` does, but for a couple of keys.
The layout is similar to the one given by default.

# How to compile

Download the qmk fork of ZSA: 

```bash
git clone https://github.com/zsa/qmk_firmware ~/qmk_firmware
```

Download the    keymap:

```bash
pushd ~/qmk_firmware/keyboards/zsa/voyager/
git clone https://github.com/mauricioprado00/zsa-voyager-keymaps.git
```

Compile all zsa voyager keymaps:

```bash
cd ~/qmk_firmware
./util/docker_build.sh zsa/voyager
```

after that the binary should be there. use [keymapp](https://oryx.nyc3.cdn.digitaloceanspaces.com/keymapp/keymapp-latest.tar.gz) to flash the firmware to the keyboard


