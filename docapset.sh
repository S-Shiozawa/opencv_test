#!/bin/sh
v4l2-ctl -d /dev/video1 -c exposure_auto=3
v4l2-ctl -d /dev/video0 -c exposure_auto=3
v4l2-ctl -d /dev/video1 -c exposure_absolute=150
v4l2-ctl -d /dev/video0 -c exposure_absolute=150
v4l2-ctl -d /dev/video0 -c sharpness=7  #newくっきり
v4l2-ctl -d /dev/video1 -c sharpness=7　　#newくっきり
#v4l2-ctl -d /dev/video1 -c backlight_compensation=0

exit 0
