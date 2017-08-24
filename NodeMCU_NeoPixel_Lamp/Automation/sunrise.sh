#!/opt/bin/bash
# Copyright Christux
# Licence LGPL

# Settings
server="http://192.168.0.42"
port="80"

# Starts dawn simulator
curl -H "Content-Type: application/json" -X POST -d '{"animation":10}' $server:$port/api &> /dev/null

# Waits 40 minutes
sleep $((60*40))

# Turns off the ledstrip
curl -H "Content-Type: application/json" -X POST -d '{"animation":11}' $server:$port/api &> /dev/null
