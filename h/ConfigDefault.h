/*
 * THIS FILE IS AUTO GENERATED!
 * DON'T EDIT, CHANGES WILL BE LOST!
 *
 * Edit cclock.yaml to change the content of this file. By running
 * yaml2config the content of this file is generate.
 */

#ifndef H_CONFIGDEFAULT_H
#define H_CONFIGDEFAULT_H

YAML::Node default_config = YAML::Load(std::string(R"(
# ---------------------------------------------------------------------------
# This is the configuration file for the cclock application. It is written in
# YAML format. The configuration file is used to set the appearance of the
# clock window and the behavior of the application.

farver:
  base: "#000000"
  highlight: "#FF0000"
  text: "#FFFFFF"

# ----
# The section 'hands:' contains the svg drawings for the hands
hands:
  animate_msecs: 100          # Update clock every "animate_msecs" milliseconds

  hour: |
    <svg width="5" height="50" xmlns="http://www.w3.org/2000/svg">
      <rect x="0" y="0" width="5" height="50" fill="${farver.base}" rx="2" ry="2"/>
    </svg>

  minute: |
    <svg width="3" height="70" xmlns="http://www.w3.org/2000/svg">
      <rect x="0" y="0" width="3" height="70" fill="${farver.base}" rx="2" ry="2"/>
    </svg>

  second: |
    <svg width="10" height="90" xmlns="http://www.w3.org/2000/svg">
      <rect x="4" y="0" width="2" height="90" fill="${farver.highlight}" rx="2" ry="2"/>
      <circle cx="5" cy="90" r="5" fill="farver.base"/>
    </svg>

# ----
# The section 'clock:' contains the colors of the clock.
decorate:
  background: none                    # Background color of the clock window

  dial_frame: none                    # Color of the clock dial frame
  dial: "#10FFFFFF"                   # Color of the clock dial

  date_background: "${farver.base}"   # Background color of the date display
  date_position: 3                    # Position of the date display; 1 to 12 o'clock
  date_text: "${farver.text}"         # Color of the date text
  date_font: "Courier New"            # Font used for the date display

  hour_mark: "${farver.base}"         # Color of the hour marks on the clock
  minute_mark: "${farver.base}"       # Color of the minute marks on the clock

# ----
# The section 'window:' contains the window settings of the clock
window:
  frameless: true                     # Whether the window is frameless
  always_on_top: true                 # Whether the window is always on top
  tool: true                          # Whether the window is a tool window
  x: -210                             # X position of the window; positie for left, negative for right
  y: -210                             # Y position of the window; positive for top, negative for bottom
  width: 200                          # Width of the window
  height: 200                         # Height of the window
)"));

#endif /* H_CONFIGDEFAULT_H */
