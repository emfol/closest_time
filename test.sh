#!/usr/bin/env bash

BIN='./closest_time.bin'

function expect {
  local param="$1"
  local expected="$2"
  local result=$($BIN "$param" 2>/dev/null)
  if [ "$result" != "$expected" ]; then
    echo "[FAIL] Expected \"$expected\"; Actual \"$result\"..."
    return
  fi
  echo '[OK]'
}

expect '00:00' '00:00'
expect '22:22' '22:22'
expect '23:59' '22:22'
expect '12:34' '12:41'
expect '19:34' '19:39'
expect '22:34' '22:42'
expect '00:01' '00:10'
expect '00:10' '00:11'
expect '00:11' '01:00'
