#!/bin/bash
# Check if an argument is provided
if [ "$#" -eq 0 ]; then
  echo "Usage: $0 <run|debug>"
  exit 1
fi

gcc ./server.c -o ./server

case "$1" in
		run)
				./server
				;;
		debug)
				strace ./server
				;;
esac



