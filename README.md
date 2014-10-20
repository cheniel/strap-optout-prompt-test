strap-optout-prompt-test
========================

Pebble test app for the opt-out prompt function in the Strap SDK.

Automatically opens the prompt at the opening of the app and when the up and down buttons are pressed. The select button displays the current setting to the logs.

   ![alt text](https://github.com/cheniel/strap-optout-prompt-test/raw/master/screenshots/screenshot.png "Prompt Screenshot")
   ![alt text](https://github.com/cheniel/strap-optout-prompt-test/raw/master/screenshots/instructions.png "Instructions Screenshot")

The prompt function is a simple function which will push a new window asking the user for permission to collect metrics via Strap. Call it at either the end of init() or put it in a click handler using:
   ```
   prompt_opt_out(default_selection);
   ```
   default_selection is a boolean which, when true, automatically highlights "Yes", and, when false, highlights "No". If the user presses the back button on the prompt, Strap metrics are disabled.

To build, install, and watch the logs for this app:
```
pebble build; pebble install --phone IP_ADDRESS_OF_PHONE --logs
```

Info on the new feature
========================
See my fork here: https://github.com/cheniel/strap_sdk_pebble

See the actual PR here: https://github.com/strap/strap_sdk_pebble/pull/3

# What is it?
A function that pushes a light-weight window to ask the user for permission to collect Strap data.

Here is what the window looks like:
   ![alt text](https://github.com/cheniel/strap-optout-prompt-test/raw/master/screenshots/screenshot.png "Prompt Screenshot")

## How do you use it?
Call it at either the end of init() or put it in a click handler using:
   ```
   prompt_opt_out(default_selection);
   ```
   default_selection is a boolean which, when true, automatically highlights "Yes", and, when false, highlights "No". If the user presses the back button on the prompt instead of selecting yes or no, Strap metrics are disabled. 

## Can I test it?
Here is a test app that I made demonstrating that it sets reporting status correctly: https://github.com/cheniel/strap-optout-prompt-test

## How's the memory usage?
I created made two apps that had identical code except for the versions of Strap used, and tried compiling with and without single call to prompt_opt_out(true) at the end of init() on the version with this PR.

Compiling Strap now costs 75 bytes more, and actually calling the function adds another 712 bytes on top of that.

Memory usage for the version with this PR and a single call at the end of init():
```
app memory usage:
=============
Total footprint in RAM:           5885 bytes / ~24kb
Free RAM available (heap):       18691 bytes
```

Memory usage for the version with this PR without any call to prompt_opt_out(true):
```
app memory usage:
=============
Total footprint in RAM:           5173 bytes / ~24kb
Free RAM available (heap):       19403 bytes
```

Memory usage for current (github) version of strap.
```
app memory usage:
=============
Total footprint in RAM:           5098 bytes / ~24kb
Free RAM available (heap):       19478 bytes
```

## What about when you run "pebble analyze-size"?
This PR w/ function call > This PR w/o function call == Current version of Strap SDK on Github

So, it doesn't add anything unless you actually call the function.

New strap w/ call to prompt_opt_out(true)
```
.bss: count 27 size 1760
  src/strap/strap.c: size 1553
  src/strap/accl.c: size 199
  src/new-strap.c: size 8
.data: count 4 size 78
  Unknown: size 69
  src/strap/accl.c: size 5
  src/strap/strap.c: size 4
.text: count 35 size 2996
  src/strap/strap.c: size 1522
  src/strap/accl.c: size 972
  src/new-strap.c: size 372
  build/appinfo.auto.c: size 130
```

New strap w/o call to prompt_opt_out(true)
```
.bss: count 21 size 1742
  src/strap/strap.c: size 1535
  src/strap/accl.c: size 199
  src/new-strap.c: size 8
.data: count 4 size 78
  Unknown: size 69
  src/strap/accl.c: size 5
  src/strap/strap.c: size 4
.text: count 27 size 2380
  src/strap/accl.c: size 972
  src/strap/strap.c: size 910
  src/new-strap.c: size 368
  build/appinfo.auto.c: size 130
```

Old strap:
```
.bss: count 21 size 1742
  src/strap/strap.c: size 1535
  src/strap/accl.c: size 199
  src/old-strap.c: size 8
.data: count 4 size 78
  Unknown: size 69
  src/strap/accl.c: size 5
  src/strap/strap.c: size 4
.text: count 27 size 2380
  src/strap/accl.c: size 972
  src/strap/strap.c: size 910
  src/old-strap.c: size 368
  build/appinfo.auto.c: size 130
```
