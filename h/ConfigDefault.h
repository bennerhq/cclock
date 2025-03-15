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

# ----
# The section 'clock:' contains the colors of the clock.
colors:
  background: none            # Background color of the clock window

  dial: "#10FFFFFF"           # Color of the clock dial
  dial_frame: none            # Color of the clock dial frame

  date_background: "#000000"  # Background color of the date display
  date_position: 3            # Position of the date display; 1 to 12 o'clock
  date_text: "#FFFFFF"        # Color of the date text
  date_font: "Courier New"    # Font used for the date display

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
)"));

#endif /* H_CONFIGDEFAULT_H */
