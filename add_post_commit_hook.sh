#!/usr/bin/bash

# Adds the git-hook described below. Appends to the hook file
# if it already exists or creates the file if it does not.
# Note: CWD must be inside target repository

HOOK_DIR=$(git rev-parse --show-toplevel)/.git/hooks
HOOK_FILE="$HOOK_DIR"/post-commit

# Create post-commit scipt
touch "$HOOK_FILE"
# Set hook permission to executable
chmod +x  "$HOOK_FILE"
# Hook code into script (makes a POST request to the url, triggering the notifyCommit action)
tee "$HOOK_FILE" > /dev/null <<EOF
#!/bin/sh
#
curl -X POST "http://localhost:8080/git/notifyCommit?url=/usr/src/app"
EOF