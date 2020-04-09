# Adafruit Feather + Charlie Wing

## Purpose

I cobbled this together with no particular usage in mind and then I realized I could use it for
just about anything!

First I rigged it up to IFTTT so that if my daughter texted me a number it would light up that many rows of lights. That got boring pretty fast.

Then I realized I could query Zendesk to see how many unsolved tickets were assigned to me and display that on the board! I know. Kinda weird.

## Usage

### Arduino Code

To get this working for yourself just rename config-example.h and fill in the missing values for your Adafruit I/O credentials and your Wifi.

```c
#define IO_USERNAME  "YOUR USERNAME"
#define IO_KEY       "YOUR TOKEN"

#define WIFI_SSID "YOUR Wifi SSID"
#define WIFI_PASS "YOUR WiFi Password"

```

### Shell Scripts

Copy env-example.sh to example.sh and replace the configuration values. Then, before you run any of the shell scripts just source it into your environment.

```sh
$ . env.sh
$ ./tickets.sh
```
