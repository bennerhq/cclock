# Analog Clock written in C++/Qt

## Overview

`cclock` is a simple command line tool that displays the current time in analog format.
It is being refactored from Python/Qt (<https://github.com/bennerhq/wclock>) to C++/Qt
with Github Co-polit.

The code is compiled, validated and tested on Ubuntu Linux and MacOS / Qt v6.10.0.

Github Co-pilot is the lead programmer!

## Features

- Easy-to-use command-line interface - just a analog clock!
- Clock behavior, design and colors can be customized in .yaml file

## Compile & run

To install `cclock`, clone the repository and build the project:

```console
# git clone https://github.com/bennerhq/cclock.git
# cd cclock
# make all
# ./cclock
```

## yaml configuration file

The `cclock` tool uses a `.yaml` configuration file to customize the
appearance of the clock. Below is the default configuration file:

```yaml
# ---------------------------------------------------------------------------
# This is the configuration file for the cclock application. It is written in
# YAML format. The configuration file is used to set the appearance of the
# clock window and the behavior of the application.

# ---
# The section 'farver:' contains the colors used in the clock
farver:
  base: "#000000"
  highlight: "#FF0000"
  text: "#FFFFFF"
  transparent: "#10FFFFFF"

# ----
# The section 'window:' contains the window settings of the clock
window:
  background_color: none              # Background color of the clock window
  frameless: true                     # Whether the window is frameless
  always_on_top: true                 # Whether the window is always on top
  tool: true                          # Whether the window is a tool window
  x: -210                             # X position of the window; positie for left, negative for right
  y: -210                             # Y position of the window; positive for top, negative for bottom
  width: 200                          # Width of the window
  height: 200                         # Height of the window

# ----
# The section 'hands:' contains the svg drawings for the hands
hands:
  animate_msecs: 50                   # Update clock every "animate_msecs" milliseconds

  hour: |                             #  $_decorate/hour-hand.svg
    <svg width="5" height="50" xmlns="http://www.w3.org/2000/svg">
        <rect x="0" y="0" width="5" height="50" fill="${farver.base}" rx="2" ry="2" />
    </svg>

  minute: |                           # $_decorate/minute-hand.svg
    <svg width="3" height="70" xmlns="http://www.w3.org/2000/svg">
        <rect x="0" y="0" width="3" height="70" fill="${farver.base}" rx="2" ry="2" />
    </svg>

  second: |                           #$_decorate/second-hand.svg
    <svg width="10" height="90" xmlns="http://www.w3.org/2000/svg">
        <rect x="4" y="0" width="2" height="90" fill="${farver.highlight}" rx="2" ry="2" />
        <circle cx="5" cy="90" r="5" fill="${farver.base}" />
    </svg>

# ----
# The section 'date:' contains the settings for the date display
date:
  position: 3                         # Position of the date display; 1 to 12 o'clock
  backgroud_color: "${farver.base}"   # Background color of the date display
  text_color: "${farver.text}"        # Color of the date text
  font: "Courier New"                 # Font used for the date display

# ----
# The section 'dial:' contains the svg drawing for the dial background
dial:
  frame_color: none                   # Color of the clock dial frame
  background_color: none              # Color of the clock dial

  hour_mark_color: none               # Color of the hour marks on the clock
  minute_mark_color: none             # Color of the minute marks on the clock

  decorate: $_decorate/clock-dial.svg
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

- Use SVG to decorate dial
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
