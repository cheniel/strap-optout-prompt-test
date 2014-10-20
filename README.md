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

See the pull request here: https://github.com/cheniel/strap_sdk_pebble
