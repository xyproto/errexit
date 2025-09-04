#!/usr/bin/env bash
echo "hello there"
false || ./errexit -e "not true"
echo "never shown"
