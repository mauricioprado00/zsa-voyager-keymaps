## Customize ZSA with special defined keys
run this:

```bash
./tools-customize/customize.sh ./zsa_voyager_mau-no-equal-move-right-shift-ad_source/keymap.c
```

and it will map the specially defined keys:
    ["MT(MOD_LSFT, KC_BSPC)"]="BSPC_SHIFT"
    ["MT(MOD_RSFT, KC_SCLN)"]="SCLN_RSFT"

which behaves like shift immediatelly after a following key is pressed, without need to wait for the release of the first key to produce the shifted key.



## Compile the firmware

Builds use ZSA's fork of QMK, [zsa/qmk_firmware](https://github.com/zsa/qmk_firmware),
on the `firmware25` branch, through its Docker wrapper `util/docker_build.sh`.
Nothing needs to be installed locally except Docker.

This repository lives inside the ZSA tree at `keyboards/zsa/voyager/keymaps`
(the fork's `.gitignore` ignores that path):

```bash
git clone -b firmware25 https://github.com/zsa/qmk_firmware ~/qmk_firmware
git clone git@github.com:mauricioprado00/zsa-voyager-keymaps.git \
  ~/qmk_firmware/keyboards/zsa/voyager/keymaps
```

Build a keymap by its folder name, from the root of the ZSA tree:

```bash
cd ~/qmk_firmware
./util/docker_build.sh zsa/voyager:zsa_voyager_mau-20251029-bring-back-space-on_source
```

The firmware is written to
`~/qmk_firmware/zsa_voyager_<keymap-folder>.bin`; flash it with Keymapp.
Append `:flash` to the target to build and flash in one step.

Notes:

- From `firmware25` on, Oryx support is a QMK community module
  (`modules/zsa/oryx`). Every keymap folder needs a `keymap.json` that loads it,
  or the build fails with `rgb_matrix_kb.inc: No such file or directory`:

  ```json
  {
      "modules": [
          "zsa/oryx",
          "zsa/defaults"
      ]
  }
  ```

  Oryx exports made for firmware25 already include this file.
- The build ends with `cp: cannot create regular file '/qmk_userspace/...'`.
  That is harmless: the wrapper also tries to copy into a QMK userspace folder
  that this setup doesn't use. The `.bin` in `~/qmk_firmware` is still written.
- Older branches (for example `firmware24`) don't build with the current
  `ghcr.io/qmk/qmk_cli` image, whose Python 3.14 is too new for them.
