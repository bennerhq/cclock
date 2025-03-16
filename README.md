# Widget Clock written in C++/Qt (clock)

## Overview

`cclock` is a simple command line tool that displays the current time in analog format.
It is being refactored from Python/Qt (<https://github.com/bennerhq/wclock>) to C++/Qt
with Github Co-polit.

The code is compiled, validated and tested on Ubuntu Linux and MacOS / Qt v6.10.0.

Github Co-pilot is the lead programmer!

## Features

- Easy-to-use command-line interface - just a analog clock!
- Clock behavior, design and colors can be customized in .yaml file

## Installation

To install `cclock`, clone the repository and build the project:

```console
# git clone https://github.com/bennerhq/cclock.git
# cd cclock
# make all
# ./cclock
```

## yaml configuration file

The `cclock` tool uses a `.yaml` configuration file to customize the
appearance of the clock. Below is an example configuration file:

```yaml
# ---------------------------------------------------------------------------
# This is the configuration file for the cclock application. It is written in
# YAML format. The configuration file is used to set the appearance of the
# clock window and the behavior of the application.

# ----
# The section 'clock:' contains the colors of the clock.
colors:
  background: none            # Background color of the clock window

  dial: "#10FFFFFF"           # Color of the clock dial
  dial_frame: none            # Color of the clock dial frame

  date_background: "#000000"  # Background color of the date display
  date_position: 3            # Position of the date display; 1 to 12 o'clock
  date_text: "#FFFFFF"        # Color of the date text
  date_font: Courier New      # Font used for the date display

  hour_mark: "#000000"        # Color of the hour marks on the clock
  minute_mark: "#000000"      # Color of the minute marks on the clock

  second_hand: "#FF0000"      # Color of the second hand
  hour_hand: "#000000"        # Color of the hour hand
  minute_hand: "#000000"      # Color of the minute hand
  middle_dot: "#000000"       # Color of the middle dot

# ----
# The section 'window:' contains the window settings of the clock
window:
  animate: float              # Animation type for the second hand; float or tick
  frameless: true             # Whether the window is frameless
  always_on_top: true         # Whether the window is always on top
  tool: true                  # Whether the window is a tool window
  x: -210                     # X position of the window; positie for left, negative for right
  y: -210                     # Y position of the window; positive for top, negative for bottom
  width: 200                  # Width of the window
  height: 200                 # Height of the window

```

## Usage

```console
# ./cclock --help
Usage: ./cclock [options] [config]
Displayes an analog clock. The clock can be configured using a YAML file.

Options:
  -h, --help              Displays help on commandline options.
  --help-all              Displays help, including generic Qt options.
  -c, --config <config>   Path to the configuration file.
  -d, --default <config>  Save default configuration to a file.
  -s, --save <config>     Save config file, If 'config' same as loaded config.
  -v, --verbose           Show config file path.

Arguments:
  config                  Path to the configuration file.
# ./cclock ./cclock.yaml
```

## TO-DO

- Use SVG to decorate clock; hands, backgrund, etc
- MacOS: Clock always onto (bug)

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the "Beerware" software license.

```bash
# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 43):
#
# Github Co-pilot & <jens@bennerhq.com> wrote this file.  As long as you 
# retain this notice you can do whatever you want with this stuff. If we meet 
# some day, and you think this stuff is worth it, you can buy me a beer in 
# return.   
# 
# /benner
# ----------------------------------------------------------------------------
```

## Contact

For any questions or suggestions, please open an issue on GitHub.
