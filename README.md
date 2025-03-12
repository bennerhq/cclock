# Widget Clock (wclock)

## Overview
`cclock` is a simple command line tool that displays the current time in analog format. 
It is being refactored from Python/Qt (https://github.com/bennerhq/wclock) to C++/Qt 
with Github Co-polit and tested on Ubuntu Linux.

Github Co-pilot is the lead programmer!

## Features
- Easy-to-use command-line interface
- Lightweight and fast
- Clock colors can be customized in .yaml file

## Installation
To install `cclock`, clone the repository and build the project:

```bash
git clone https://github.com/bennerhq/cclock.git
cd cclock
make all
```

## yaml configuration file
The `cclock` tool uses a `.yaml` configuration file to customize the appearance of the clock. 
Below is an example configuration file:

```yaml
# cclock.yaml
    colors:
        background: '#00FFFFFF'
        dial: '#00FFFFFF'

        hour_mark: '#000000'
        minute_mark: '#000000'
        second_hand: '#FF0000'
        hour_hand: '#000000'
        minute_hand: '#000000'

        date_background: '#000000'
        date: '#FFFFFF'
        date_font: 'Courier New'

    window:
        frameless: true
        always_on_top: true
        tool: true
        x: -200
        y: -200
        width: 200
        height: 200
```

You can modify the colors and sizes to suit your preferences.

## Usage
Run `cclock` with the desired yaml config file

```bash
./cclock ./cclock.yaml
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## License
This project is licensed under the "Beerware" software license.

```
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
