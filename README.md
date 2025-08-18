## Customize ZSA with special defined keys
run this:

```bash
./tools-customize/customize.sh ./zsa_voyager_mau-no-equal-move-right-shift-ad_source/keymap.c
```

and it will map the specially defined keys:
    ["MT(MOD_LSFT, KC_BSPC)"]="BSPC_SHIFT"
    ["MT(MOD_RSFT, KC_SCLN)"]="SCLN_RSFT"

which behaves like shift immediatelly after a following key is pressed, without need to wait for the release of the first key to produce the shifted key.



