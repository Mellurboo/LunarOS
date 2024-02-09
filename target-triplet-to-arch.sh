#!/bin/sh
if echo "$1" | grep -Eq 'i[0-6]86'; then
  echo i386
else
  echo "$1" | grep -Eo '^[[:alnum:]_]*'
fi
