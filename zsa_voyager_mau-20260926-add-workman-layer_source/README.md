# zsa_voyager_mau-20260926-add-workman-layer

QWERTY base layer plus a Workman layer and a mouse layer.

## Layers

| Layer | Contents                                   |
|-------|--------------------------------------------|
| 0     | QWERTY (base)                              |
| 1     | Workman (letters only, rest falls to 0)    |
| 2     | F-keys, symbols, numpad (hold Enter)       |
| 3     | Brackets, navigation (hold Space)          |
| 4     | RGB, media, QK_BOOT (MO(4) from layer 3)   |
| 5     | Mouse                                      |

Workman sits below the symbol/nav layers on purpose. A higher layer wins on
every key it defines, so with Workman as layer 1, holding Enter (L2) or Space
(L3) shows symbols and arrows instead of Workman letters. The old attempts put
Workman at layer 4, which covered layers 1-3 and needed custom thumb code to
work around it (see the `workman` branch).

## Switching layers

| From        | Key                      | Double-tap goes to |
|-------------|--------------------------|--------------------|
| QWERTY (0)  | A (`DANCE_0`)            | Mouse (5)          |
| QWERTY (0)  | D (`DANCE_1`)            | Workman (1)        |
| Workman (1) | H, D's position (`DANCE_2`) | QWERTY (0)      |
| Mouse (5)   | A position (`TO(0)`)     | QWERTY (0)         |

## Known problems

### Holding A, D or H types nothing

The three tap dances only define single tap and double tap. If the key is
still down when the tapping term (150 ms) expires, `dance_step()` returns
`SINGLE_HOLD`, which the `dance_N_finished()` switches don't handle. A slow
press drops the letter, and holding the key does not auto-repeat.

Fix in Oryx: set each tap dance's **hold** action to the same letter.

### `dd` / `aa` followed by a pause switches layers

A double tap only counts if no other key is pressed within the tapping term
after the second tap. Words typed straight through (`added`, `address`) are
fine: the next letter interrupts the dance and it outputs `dd`. But `add`,
`odd`, or vim's `dd` followed by a 150 ms pause moves to Workman; `aa`
followed by a pause moves to the mouse layer.

Fix: move the switches back to rarely doubled keys (e.g. 3), or use a combo.

### No mouse layer from Workman

Layer 1 defines A as plain `KC_A`, so `DANCE_0` is unreachable from Workman.
And `TO(0)` in the mouse layer always returns to QWERTY, not to the layer you
came from.

### Rolling off Workman's I turns it into Shift

`tools-customize/customize.sh` replaces layer 1's `MT(MOD_RSFT, KC_I)` with
`I_RSFT` (same handler style as `SCLN_RSFT` on layer 0). It has no tapping
term: any other key pressed while I is down makes I a Right Shift and drops
the `i`. I is on the right-pinky home key in Workman, so fast rolls like
"in", "is", "it" and "-ing" come out as `N`, `S`, `T`, `NG`. Stock `MT()`
would treat those quick rolls as taps.

Fix: drop the `MT(MOD_RSFT, KC_I)` line from `customize.sh` to keep Oryx's
behaviour on I (the `;` key on layer 0 is unaffected), or make the handler
only switch to Shift after a hold delay.

### Oryx's modded mouse/media key handling is dropped

`customize.sh` replaces `process_record_user()` wholesale with
`tools-customize/process-record.tail`, which lacks Oryx's
`QK_MODS ... QK_MODS_MAX` block. That block only matters for modifier +
mouse/consumer keycodes, and this keymap has none.
