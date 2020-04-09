#!/bin/bash


data="{ \"value\": 0 }"
curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

sleep 1

data="{ \"value\": 2 }"
curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

sleep 1
data="{ \"value\": 4 }"
curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

sleep 1
data="{ \"value\": 6 }"
curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

sleep 1
data="{ \"value\": 8 }"
curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

sleep 1
