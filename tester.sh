#!/bin/bash

echo "This tester will test all maps included in the maps/ directory."
echo "⚠ When the games run, press ESC or close the window to continue. ⚠"

for map in maps/*; do
	echo "Testing map: $map"
	output=$(valgrind --leak-check=full --show-leak-kinds=all ./cub3d "$map" 2>&1)
	
	if echo "$output" | grep -q "lost: [1-9]"; then
		echo "$output" | grep -A 20 "LEAK SUMMARY"
	elif echo "$output" | grep -q "still reachable"; then
		echo "$output" | grep -A 5 "still reachable"
	fi
done