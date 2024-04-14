#!/bin/sh

if ! which brew > /dev/null; then
    echo "Must have homebrew installed"
    exit 1
fi

if ! brew leaves | grep -q libusb-compat; then
    echo "libusb not present in homebrew. Please install with 'brew install libusb-compat'"
    exit 1
fi

# Clone source code
mkdir .teensy-cli-source && cd .teensy-cli-source
git clone https://github.com/jonbakke/teensy_loader_cli.git .

# Modify Makefile to compile for OSX
sed -i '' -e 's/OS ?= LINUX/#OS ?= LINUX/g' Makefile
sed -i '' -e 's/#OS ?= MACOSX/OS ?= MACOSX/g' Makefile

# Compile
make

# Move executable to outer directory
mv teensy_loader_cli ..
cd ..
