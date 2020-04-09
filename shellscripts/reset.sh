#!/bin/bash

. env.sh

data="{ \"value\": 0 }"

curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

