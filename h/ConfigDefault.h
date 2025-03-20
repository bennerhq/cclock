// -------------------------------------------------------------------------------------
//                           !!! THIS FILE IS AUTO GENERATED !!!
//                       !!! DON'T EDIT, ALL CHANGES WILL BE LOST !!!
//
// Edit cclock.yaml to change the content of this file. By running
// yaml2config the content of this file is generate.
// -------------------------------------------------------------------------------------

#ifndef H_CONFIGDEFAULT_H
#define H_CONFIGDEFAULT_H

YAML::Node default_config = YAML::Load(std::string(R"(
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
# The section 'dial:' contains the svg drawing for the dial background
dial:
  frame_color: none                   # Color of the clock dial frame
  background_color: none              # Color of the clock dial

  hour_mark_color: "${farver.base}"   # Color of the hour marks on the clock
  minute_mark_color: "${farver.base}" # Color of the minute marks on the clock

  decorate: none                      # Decoration of the clock dial; "$:<filename>", bitmap og SVG file

# ----
# The section 'numbers:' contains the settings for the 12 hours around the clock
numbers:
  positions: ""
  backgroud_color: none               # Background color of the number display
  text_color: "${farver.text}"        # Color of the number text
  font: "Courier New"                 # Font used for the number display
  font_size: 11                       # Font size of the number display 

# ----
# The section 'date:' contains the settings for the date display
date:
  position: 3                         # Position of the date display; 1 to 12 o'clock (0=no date)
  backgroud_color: "${farver.base}"   # Background color of the date display
  text_color: "${farver.text}"        # Color of the date text
  font: "Courier New"                 # Font used for the date display
  font_size: 11                       # Font size of the number display 

# ----
# The section 'hands:' contains the svg drawings for the hands
hands:
  animate_msecs: 50                   # Update clock every "animate_msecs" milliseconds

  hour: |                             # image/hour-hand.svg
    <svg width="5" height="50" xmlns="http://www.w3.org/2000/svg">
        <rect x="0" y="0" width="5" height="50" fill="${farver.base}" rx="2" ry="2" />
    </svg>

  minute: |                           # image/minute-hand.svg
    <svg width="3" height="70" xmlns="http://www.w3.org/2000/svg">
        <rect x="0" y="0" width="3" height="70" fill="${farver.base}" rx="2" ry="2" />
    </svg>

  second: |                           # image/second-hand.svg
    <svg width="10" height="90" xmlns="http://www.w3.org/2000/svg">
        <rect x="4" y="0" width="2" height="90" fill="${farver.highlight}" rx="2" ry="2" />
        <circle cx="5" cy="90" r="5" fill="${farver.base}" />
    </svg>
)"));

#endif /* H_CONFIGDEFAULT_H */
