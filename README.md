
## Compile
aarch64-linux-gnu-gcc main.c -o stdinc

## Run
adk-message-monitor -g audio | awk '/volume:/ {sub("^ *", ""); sub(" *$", ""); print}' | stdinc
