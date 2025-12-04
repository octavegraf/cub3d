#!/bin/bash

echo "This tester will test all maps included in the maps/ directory."
echo "⚠ When the games run, press ESC or close the window to continue. ⚠"

for map in maps/*; do
	echo "Testing map: $map"
	output=$(valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./cub3d_bonus "$map" 2>&1)

	if echo "$output" | grep -q "Error"; then
		echo "$output" | grep -A 1 "Error"
	fi

	if echo "$output" | grep -q "lost: [1-9]"; then
		echo "$output" | grep -A 20 "LEAK SUMMARY"
	elif echo "$output" | grep -q "still reachable"; then
		echo "$output" | grep -A 5 "still reachable"
	fi
	
	if echo "$output" | grep -q "Open file descriptor"; then
		echo "$output" | grep -A 10 "Open file descriptor"
	fi
done