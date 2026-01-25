#!/usr/bin/env bash

INPUT_HW="$1"

tar -cvf "${INPUT_HW}_elimg.tar" --exclude=".cache" "${INPUT_HW}" 
