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
  animate_msecs: 50          # Update clock every "animate_msecs" milliseconds

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
# The section 'date:' contains the settings for the date display
date:
  position: 3                         # Position of the date display; 1 to 12 o'clock
  backgroud_color: "${farver.base}"    # Background color of the date display
  text_color: "${farver.text}"        # Color of the date text
  font: "Courier New"                 # Font used for the date display

# ----
# The section 'dial:' contains the svg drawing for the dial background
dial:
  frame_color: none                   # Color of the clock dial frame
  background_color: none              # Color of the clock dial

  hour_mark_color: none               # Color of the hour marks on the clock
  minute_mark_color: none             # Color of the minute marks on the clock

  decorate: |
    <svg width="200" height="200" xmlns="http://www.w3.org/2000/svg">
        <g fill="none" fill-rule="evenodd" id="svg_1" stroke="black" stroke-linecap="square" stroke-linejoin="bevel"
            transform="translate(0.638683 0.561095) scale(1.00506 1) translate(-0.638683 -0.561095) 
            translate(0.638683 0.556042) matrix(0.424745 0 0 0.427252 -36.6324 -2.66931) ">
            <g fill="none" id="svg_2" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" transform="matrix(2.4,0,0,2.4,319,239) " />
            <g fill="none" id="svg_3" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2" transform="matrix(2.4,0,0,2.4,319,239) ">
                <polyline fill="none" id="svg_4" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_5" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(2.07846,1.2,-1.2,2.07846,319,239) ">
                <polyline fill="none" id="svg_6" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_7" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(1.2,2.07846,-2.07846,1.2,319,239) ">
                <polyline fill="none" id="svg_8" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_9" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(9.3811e-16,2.4,-2.4,5.59467e-16,319,239) ">
                <polyline fill="none" id="svg_10" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_11" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(-1.2,2.07846,-2.07846,-1.2,319,239) ">
                <polyline fill="none" id="svg_12" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_13" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(-2.07846,1.2,-1.2,-2.07846,319,239) ">
                <polyline fill="none" id="svg_14" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_15" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(-2.4,1.35245e-15,-1.66969e-15,-2.4,319,239) ">
                <polyline fill="none" id="svg_16" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_17" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(-2.07846,-1.2,1.2,-2.07846,319,239) ">
                <polyline fill="none" id="svg_18" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_19" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(-1.2,-2.07846,2.07846,-1.2,319,239) ">
                <polyline fill="none" id="svg_20" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_21" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(-9.3811e-16,-2.4,2.4,-5.59467e-16,319,239) ">
                <polyline fill="none" id="svg_22" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_23" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(1.2,-2.07846,2.07846,1.2,319,239) ">
                <polyline fill="none" id="svg_24" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_25" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel" stroke-width="2"
                transform="matrix(2.07846,-1.2,1.2,2.07846,319,239) ">
                <polyline fill="none" id="svg_26" points="88,0 96,0 " />
            </g>
            <g fill="none" id="svg_27" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.4,0,0,2.4,319,239) " />
            <g fill="none" id="svg_28" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.38685,0.250868,-0.250868,2.38685,319,239) ">
                <polyline fill="none" id="svg_29" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_30" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.34755,0.498988,-0.498988,2.34755,319,239) ">
                <polyline fill="none" id="svg_31" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_32" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.28254,0.741641,-0.741641,2.28254,319,239) ">
                <polyline fill="none" id="svg_33" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_34" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.19251,0.976168,-0.976168,2.19251,319,239) ">
                <polyline fill="none" id="svg_35" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_36" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.94164,1.41068,-1.41068,1.94164,319,239) ">
                <polyline fill="none" id="svg_37" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_38" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.78355,1.60591,-1.60591,1.78355,319,239) ">
                <polyline fill="none" id="svg_39" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_40" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.60591,1.78355,-1.78355,1.60591,319,239) ">
                <polyline fill="none" id="svg_41" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_42" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.41068,1.94164,-1.94164,1.41068,319,239) ">
                <polyline fill="none" id="svg_43" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_44" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.976168,2.19251,-2.19251,0.976168,319,239) ">
                <polyline fill="none" id="svg_45" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_46" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.741641,2.28254,-2.28254,0.741641,319,239) ">
                <polyline fill="none" id="svg_47" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_48" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.498988,2.34755,-2.34755,0.498988,319,239) ">
                <polyline fill="none" id="svg_49" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_50" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.250868,2.38685,-2.38685,0.250868,319,239) ">
                <polyline fill="none" id="svg_51" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_52" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.250868,2.38685,-2.38685,-0.250868,319,239) ">
                <polyline fill="none" id="svg_53" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_54" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.498988,2.34755,-2.34755,-0.498988,319,239) ">
                <polyline fill="none" id="svg_55" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_56" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.741641,2.28254,-2.28254,-0.741641,319,239) ">
                <polyline fill="none" id="svg_57" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_58" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.976168,2.19251,-2.19251,-0.976168,319,239) ">
                <polyline fill="none" id="svg_59" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_60" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.41068,1.94164,-1.94164,-1.41068,319,239) ">
                <polyline fill="none" id="svg_61" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_62" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.60591,1.78355,-1.78355,-1.60591,319,239) ">
                <polyline fill="none" id="svg_63" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_64" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.78355,1.60591,-1.60591,-1.78355,319,239) ">
                <polyline fill="none" id="svg_65" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_66" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.94164,1.41068,-1.41068,-1.94164,319,239) ">
                <polyline fill="none" id="svg_67" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_68" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.19251,0.976168,-0.976168,-2.19251,319,239) ">
                <polyline fill="none" id="svg_69" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_70" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.28254,0.741641,-0.741641,-2.28254,319,239) ">
                <polyline fill="none" id="svg_71" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_72" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.34755,0.498988,-0.498988,-2.34755,319,239) ">
                <polyline fill="none" id="svg_73" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_74" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.38685,0.250868,-0.250868,-2.38685,319,239) ">
                <polyline fill="none" id="svg_75" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_76" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.38685,-0.250868,0.250868,-2.38685,319,239) ">
                <polyline fill="none" id="svg_77" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_78" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.34755,-0.498988,0.498988,-2.34755,319,239) ">
                <polyline fill="none" id="svg_79" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_80" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.28254,-0.741641,0.741641,-2.28254,319,239) ">
                <polyline fill="none" id="svg_81" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_82" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-2.19251,-0.976168,0.976168,-2.19251,319,239) ">
                <polyline fill="none" id="svg_83" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_84" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.94164,-1.41068,1.41068,-1.94164,319,239) ">
                <polyline fill="none" id="svg_85" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_86" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.78355,-1.60591,1.60591,-1.78355,319,239) ">
                <polyline fill="none" id="svg_87" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_88" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.60591,-1.78355,1.78355,-1.60591,319,239) ">
                <polyline fill="none" id="svg_89" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_90" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-1.41068,-1.94164,1.94164,-1.41068,319,239) ">
                <polyline fill="none" id="svg_91" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_92" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.976168,-2.19251,2.19251,-0.976168,319,239) ">
                <polyline fill="none" id="svg_93" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_94" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.741641,-2.28254,2.28254,-0.741641,319,239) ">
                <polyline fill="none" id="svg_95" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_96" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.498988,-2.34755,2.34755,-0.498988,319,239) ">
                <polyline fill="none" id="svg_97" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_98" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(-0.250868,-2.38685,2.38685,-0.250868,319,239) ">
                <polyline fill="none" id="svg_99" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_100" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.250868,-2.38685,2.38685,0.250868,319,239) ">
                <polyline fill="none" id="svg_101" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_102" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.498988,-2.34755,2.34755,0.498988,319,239) ">
                <polyline fill="none" id="svg_103" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_104" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.741641,-2.28254,2.28254,0.741641,319,239) ">
                <polyline fill="none" id="svg_105" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_106" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(0.976168,-2.19251,2.19251,0.976168,319,239) ">
                <polyline fill="none" id="svg_107" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_108" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.41068,-1.94164,1.94164,1.41068,319,239) ">
                <polyline fill="none" id="svg_109" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_110" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.60591,-1.78355,1.78355,1.60591,319,239) ">
                <polyline fill="none" id="svg_111" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_112" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.78355,-1.60591,1.60591,1.78355,319,239) ">
                <polyline fill="none" id="svg_113" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_114" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(1.94164,-1.41068,1.41068,1.94164,319,239) ">
                <polyline fill="none" id="svg_115" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_116" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.19251,-0.976168,0.976168,2.19251,319,239) ">
                <polyline fill="none" id="svg_117" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_118" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.28254,-0.741641,0.741641,2.28254,319,239) ">
                <polyline fill="none" id="svg_119" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_120" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.34755,-0.498988,0.498988,2.34755,319,239) ">
                <polyline fill="none" id="svg_121" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_122" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.38685,-0.250868,0.250868,2.38685,319,239) ">
                <polyline fill="none" id="svg_123" points="92,0 96,0 " />
            </g>
            <g fill="none" id="svg_124" stroke="${farver.base}" stroke-linecap="square" stroke-linejoin="bevel"
                transform="matrix(2.4,0,0,2.4,319,239) " />
        </g>
    </svg>
)"));

#endif /* H_CONFIGDEFAULT_H */
