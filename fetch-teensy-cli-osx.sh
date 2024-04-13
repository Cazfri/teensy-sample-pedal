#!/bin/sh

if ! which brew > /dev/null; then
    echo "Must have homebrew installed"
    exit 1
fi

if ! brew leaves | grep -q libusb-compat; then
    echo "libusb not present in homebrew. Please install with 'brew install libusb-compat'"
    exit 1
fi

mkdir .teensy-cli-source && cd .teensy-cli-source
git clone https://github.com/PaulStoffregen/teensy_loader_cli.git .
make
mv teensy_loader_cli ..
cd ..
