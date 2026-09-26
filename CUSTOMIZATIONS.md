# Keymap customizations

Oryx exports standard QMK mod-tap keys. `tools-customize/customize.sh` rewrites an
exported `keymap.c` so that some of those keys use custom handling instead. The
unmodified export is kept next to it as `keymap.c.orig`.

```bash
./tools-customize/customize.sh ./zsa_voyager_mau-<snapshot>_source/keymap.c
```

## What the script does

1. `defines.patch` adds the tuning `#define`s near the top of the file (see
   [Settings](#settings)).
2. `custom-keycodes.patch` adds `BSPC_SHIFT`, `SCLN_RSFT` and `I_RSFT` to
   `enum custom_keycodes`.
3. Replaces the Oryx mod-taps in the layers:

   | Oryx keycode            | Replaced with |
   |-------------------------|---------------|
   | `MT(MOD_LSFT, KC_BSPC)` | `BSPC_SHIFT`  |
   | `MT(MOD_RSFT, KC_SCLN)` | `SCLN_RSFT`   |
   | `MT(MOD_RSFT, KC_I)`    | `I_RSFT`      |

4. Deletes everything from `process_record_user` to the end of the file and
   appends `process-record.tail`, which has the new `process_record_user`,
   `process_bspc_shift` and `matrix_scan_user`.

## Why

A QMK mod-tap decides between tap and hold based on `TAPPING_TERM`. Tap a little
slowly and you get Shift instead of the key. Roll into the next key too fast and
you get the letter instead of the shifted letter.

The custom keys don't use a timer. They become Shift the moment another key is
pressed while they are held. Otherwise they send their tap key on release, no
matter how long they were held.

## Keys

### `BSPC_SHIFT` (Backspace / Left Shift)

- **Tap:** Backspace.
- **Hold, then press another key:** Left Shift is registered just before that key
  is processed, and released when `BSPC_SHIFT` is released.
- **Hold and release alone:** Backspace, even after a long hold.
- **Double-tap and hold:** auto-repeats Backspace. The second press must come
  within `TAP_MAX_INTERVAL` of the first. Repeat starts `REPEAT_DELAY` after the
  second press and fires every `REPEAT_INTERVAL`. Controlled by
  `BSPC_SHIFT_REPEAT_ON_DOUBLE_TAP_HOLD`.
- **Hold to repeat** (no double tap): available but off by default
  (`BSPC_SHIFT_REPEAT_ON_HOLD`). Turning it on means a long hold repeats Backspace
  instead of waiting to become Shift.

`process_bspc_shift` runs before the main `switch` for every key event, so any
key can trigger its Shift, custom keys included.

### `SCLN_RSFT` (`;` / Right Shift)

- **Tap:** `;`.
- **Hold, then press another key:** Right Shift, same as above.
- **Shift already held when pressed:** sends `;` immediately (so `:`) and skips
  the tap/hold logic.
- **Rolling from `BSPC_SHIFT`:** hold `BSPC_SHIFT`, press `;`, release
  `BSPC_SHIFT` first. You still get `:`, because `virtual_shift` records that
  Shift was active when `;` went down.
- **Hold to repeat:** available but off (`SCLN_RSFT_REPEAT_ON_HOLD`).

The tap key is set by `SCLN_RSFT_TAP_CODE`.

### `I_RSFT` (`i` / Right Shift)

Same behaviour as `SCLN_RSFT`, with `I_RSFT_TAP_CODE` as the tap key. It only
takes effect if the Oryx layout has `MT(MOD_RSFT, KC_I)` on some layer. It shares
the `scln_rsft_*` state variables with `SCLN_RSFT`, so the two can't be on the
same layout at once.

## Other handlers in `process-record.tail`

- **`DUAL_FUNC_0`** (`LT(14, KC_7)`): tap sends `=`, hold sends Esc. This came
  from an earlier Oryx export that had Escape on a dual-function key. It's
  harmless when the layout doesn't use it. Oryx numbers these keys per export,
  so if a new export uses dual-function keys, check that its `#define` matches
  what the tail expects.
- **`RGB_SLD`, `HSV_0_255_255`, `HSV_74_255_255`, `HSV_169_255_255`**: copied from
  the Oryx export unchanged.

## What is lost from the Oryx export

Because the script replaces everything from `process_record_user` down, any Oryx
code in that part of the file is dropped. Currently that means ZSA's `QK_MODS`
handler, which makes modifier + mouse-button keycodes (for example Shift+click)
behave consistently across operating systems. The layouts only use a plain
`KC_MS_BTN1`, so nothing depends on it today. If a future export adds new
handlers there, they have to be copied into `process-record.tail` by hand.

## Settings

Defined in `tools-customize/defines.patch`:

| Define                                 | Default   | Meaning                                         |
|----------------------------------------|-----------|-------------------------------------------------|
| `REPEAT_DELAY`                         | `500`     | ms of holding before auto-repeat starts         |
| `REPEAT_INTERVAL`                      | `40`      | ms between repeats                              |
| `TAP_MAX_INTERVAL`                     | `250`     | max ms between presses to count as a double tap |
| `BSPC_SHIFT_REPEAT_ON_HOLD`            | `0`       | repeat Backspace on a single hold               |
| `BSPC_SHIFT_REPEAT_ON_DOUBLE_TAP_HOLD` | `1`       | repeat Backspace on double-tap-and-hold         |
| `SCLN_RSFT_REPEAT_ON_HOLD`             | `0`       | repeat `;` on hold                              |
| `SCLN_RSFT_TAP_CODE`                   | `KC_SCLN` | tap key of `SCLN_RSFT`                          |
| `I_RSFT_REPEAT_ON_HOLD`                | `0`       | repeat `i` on hold                              |
| `I_RSFT_TAP_CODE`                      | `KC_I`    | tap key of `I_RSFT`                             |
| `DUAL_FUNC_0`                          | `LT(14, KC_7)` | keycode handled as tap `=` / hold Esc      |

## Known quirks

- On press, `BSPC_SHIFT` resets its repeat timer only when
  `SCLN_RSFT_REPEAT_ON_HOLD` is set, not its own flag. With the defaults, the
  first repeat on double-tap-and-hold therefore fires as soon as `REPEAT_DELAY`
  has passed, without waiting one more `REPEAT_INTERVAL`. You can't feel the
  difference, but a single-hold repeat would behave the same way if it were
  turned on.
- `virtual_shift` is a counter shared by all the custom keys. It is only
  consulted by `SCLN_RSFT` / `I_RSFT` to handle the roll case above.
