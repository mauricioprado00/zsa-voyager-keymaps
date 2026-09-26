# zsa_voyager_mau-20260926-add-workman-layer

QWERTY base layer plus a Workman layer, a mouse layer, and a layer picker to
switch between them.

## Layers

| Layer | Contents                                              | Reached by                 |
|-------|-------------------------------------------------------|----------------------------|
| 0     | QWERTY (base)                                         | picker + J                 |
| 1     | Workman (letters only, rest falls through to 0)       | picker + K                 |
| 2     | Mouse                                                 | picker + L, or hold Enter + `TO(2)` |
| 3     | Layer picker                                          | hold `MO(3)`, left of Q    |
| 4     | F-keys, symbols, numpad                               | hold Enter (`LT(4)`)       |
| 5     | Brackets, navigation                                  | hold Space (`LT(5)`)       |
| 6     | RGB, media, volume, LED_LEVEL, QK_BOOT                | hold Space + `MO(6)`       |

Workman sits below the symbol, nav and RGB layers on purpose. A higher layer
wins on every key it defines, so with Workman as layer 1, holding Enter or
Space shows symbols and arrows instead of Workman letters. The old attempts put
Workman above those layers and needed custom thumb code to work around it (see
the `workman` branch).

## Switching layers

Hold the key left of Q (`MO(3)`) and press, on the right home row:

| Key | Goes to     |
|-----|-------------|
| J   | QWERTY (0)  |
| K   | Workman (1) |
| L   | Mouse (2)   |

The `TO()` fires while the picker is held, so the new layer stays after you
let go. The picker key is transparent on Workman and Mouse, so it works from
every mode, and a stray press on its own does nothing. The mouse layer also
has `TO(0)` on the A position.

## Customizations

`tools-customize/customize.sh` (run by CI) replaces:

| Layer | Oryx keycode             | Replaced with | Key         |
|-------|--------------------------|---------------|-------------|
| 0     | `MT(MOD_LSFT, KC_BSPC)`  | `BSPC_SHIFT`  | Backspace / Left Shift |
| 0     | `MT(MOD_RSFT, KC_SCLN)`  | `SCLN_RSFT`   | `;` / Right Shift      |
| 1     | `MT(MOD_RSFT, KC_QUOTE)` | `QUOTE_RSFT`  | `'` / Right Shift      |

So QWERTY's `;` and Workman's `'` behave the same way: tap sends the key on
release, however long it was held, and it becomes Right Shift only when another
key is pressed while it's down. See [CUSTOMIZATIONS.md](../CUSTOMIZATIONS.md).

Workman's I is a plain `KC_I` (the `I_RSFT` replacement finds nothing here).

## Known problems

### Rolling off `;` or `'` turns it into Shift

The custom Right Shift keys have no tapping term. If the next key goes down
before `;` (QWERTY) or `'` (Workman) is released, that key is shifted and the
`;` / `'` is lost. For example `foo();` + Enter typed quickly can give
Shift+Enter, and `don't` rolled quickly can give `donT`. Stock `MT()` would
count a quick roll as a tap.

### Oryx's modded mouse/media key handling is dropped

`customize.sh` replaces `process_record_user()` wholesale with
`tools-customize/process-record.tail`, which lacks Oryx's
`QK_MODS ... QK_MODS_MAX` block. It only matters for modifier + mouse/consumer
keycodes, and this keymap has none.

## Fixed in this version

- Tap dances on A, D and H (dropped letters on hold, `dd`/`aa` + pause switched
  layers) are gone; the picker replaces them.
- Mouse is reachable from Workman, and Mouse can go straight back to Workman.
- Workman's I no longer becomes Shift when rolled.
- Layer 6 (QK_BOOT, RGB, media) is reachable again through `MO(6)`.
