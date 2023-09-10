set -e
set -o pipefail
CURRENT_DIR=$(basename "$(pwd)")

arduino-cli compile --fqbn esp32:esp32:wifiduino32s3 $CURRENT_DIR.ino -v --only-compilation-database --build-path "tmp"
mv tmp/compile_commands.json .
rm -rf tmp
