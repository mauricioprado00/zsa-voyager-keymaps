#!/bin/bash

source="$1"

if [[ -z "$source" ]]; then
    echo "Please provide the path to keymap.c as the first argument."
    exit 1
fi

if [[ "$(basename "$source")" != "keymap.c" ]]; then
    echo "Warning: The provided file is not named 'keymap.c'."
    read -p "Do you want to continue? [y/N]: " confirm
    if [[ "$confirm" != "y" && "$confirm" != "Y" ]]; then
        echo "Aborting."
        exit 1
    fi
fi

base=$(dirname $0)

# defines.patch adds REPEAT_DELAY first, so its presence means the file was
# already customized.
if grep -q '^#define REPEAT_DELAY' "$source"; then
    echo "$source is already customized, skipping."
    exit 0
fi

backup=$(mktemp /tmp/keymap_backup.XXXXXX)
cp "$source" "$backup"
echo "Backup created at: $backup"

# patch $source -l -F0 ${base}/defines.patch
# patch $source -l -F0 ${base}/custom-keycodes.patch

# --forward fails instead of prompting when a patch looks already applied.
for p in defines.patch custom-keycodes.patch; do
    if ! patch --forward --no-backup-if-mismatch -r - "$source" "${base}/$p"; then
        cp "$backup" "$source"
        echo "Error: $p does not apply to $source; restored the original." >&2
        exit 1
    fi
done

# Define replacement patterns as an associative array
declare -A replacements=(
    ["MT(MOD_LSFT, KC_BSPC)"]="BSPC_SHIFT"
    ["MT(MOD_RSFT, KC_SCLN)"]="SCLN_RSFT"
    ["MT(MOD_RSFT, KC_I)"]="I_RSFT"
    ["MT(MOD_RSFT, KC_QUOTE)"]="QUOTE_RSFT"
)

# Loop through the replacements and apply them to $source
for key in "${!replacements[@]}"; do
    sed -i "s/${key}/${replacements[$key]}/g" $source
done

sed -i '/process_record_user/,$d' $source

cat ${base}/process-record.tail >> $source
