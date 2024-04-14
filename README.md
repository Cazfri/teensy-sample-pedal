# Sample Pedal Teensy Code

## Programming Teensy

The best way is probably to use the official [Teensy Loader Application](https://www.pjrc.com/teensy/loader.html). You can also compile the CLI from source using `fetch-teensy-cli-osx.sh` and upload using `./teensy_loader_cli --mcu=TEENSY40 <file>.hex`, but it requires the use of a forked version of the CLI that includes bug fixes. It works, but is behind the CLI by a few commits.