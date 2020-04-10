#!/bin/bash

while true; do
query="status<solved assignee:${userid}"
RESP=$(curl "https://${subdomain}.zendesk.com/api/v2/search.json" -G --data-urlencode "query=${query}" -u "${username}:${token}" -q -s | jq .count)

echo "You have $RESP tickets assigned to you"

data="{ \"value\": ${RESP} }"

curl -H "Content-Type: application/json" -d "${data}"  -H "X-AIO-Key: ${aio_key}" "https://io.adafruit.com/api/v2/${aio_username}/feeds/${aio_feed}/data"

sleep 30
done
