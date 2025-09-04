#!/usr/bin/env bash
echo "hello there"
false | ./errexit -e "not true" 2
echo "never shown"
